#include "Tilemap.h"

void Tilemap::ProcessLayers(Value& layers, Value& tilesets) {
	assert(layers.IsArray());
	assert(tilesets.IsObject());
	for (Value::ConstValueIterator itr = layers.Begin(); itr != layers.End(); ++itr) {
		const Value& layer = *itr;
		HandleLayer(layer, tilesets);
	}
}

void Tilemap::HandleLayer(const Value & layer, Value& tilesets) {
	assert(layer.IsObject());
	string layerType = layer["type"].GetString();
	if (layerType == "tilelayer") {
		HandleTileLayer(layer["data"], tilesets["tiles"]);
	}
	else if (layerType == "objectgroup") {
		HandleObjectsGroup(layer["objects"]);
	}
}

void Tilemap::HandleTileLayer(const Value & tilesData, const Value& tilesProperties) {
	assert(tilesData.IsArray());
	int column = 0;
	int row = 0;
	for (Value::ConstValueIterator itr = tilesData.GetArray().Begin(); itr != tilesData.GetArray().End(); ++itr) {
		const Value& tileId = *itr;
		Tile tile;
		tile.id = tileId.GetInt() - 1;
		if (tile.id >= 0) {
			tile.size = Vector2(tileWidth, tileHeight);
			tile.tilemapPosition = Vector2(column, row);
			tile.position = Vector2(column * tileWidth, row * tileHeight);
			tile.isCollider = IsColliderTile(tile.id, tilesProperties);
			if (tile.isCollider) {
				colliderTiles.push_back(tile);
			}
			tiles.push_back(tile);
		}
		column++;
		if (column % width == 0 && column != 0) {
			column = 0;
			row++;
		}
	}
}

bool Tilemap::IsColliderTile(int tileId, const Value & tileSet) {
	assert(tileSet.IsArray());
	for (Value::ConstValueIterator itr = tileSet.GetArray().Begin(); itr != tileSet.GetArray().End(); ++itr) {
		const Value& tileProperty = *itr;
		if (tileId == tileProperty["id"].GetInt()) {
			return true;
		}
	}
	return false;
}

void Tilemap::LoadFromFile(const char * filePath) {
	ifstream file(filePath, ios::binary);
	if (!file.is_open()) {
		cerr << "Could not open file for reading!" << endl;
		return;
	}
	IStreamWrapper isw{ file };
	Document d{};
	d.ParseStream(isw);

	width = d["width"].GetInt();
	height = d["height"].GetInt();
	tileWidth = d["tileheight"].GetInt();
	tileHeight = d["tilewidth"].GetInt();

	Value& layers = d["layers"];
	Value& tileset = d["tilesets"].GetArray()[0];
	const char *tilesetFilePath = tileset["image"].GetString();
	ProcessLayers(layers, tileset);
	SetTexture(tilesetFilePath, IMAGETYPE_PNG, tileset["columns"].GetInt(), tileset["imageheight"].GetInt() / tileset["tileheight"].GetInt());
}

void Tilemap::SetTexture(const char * filePath, ImageType imageType, int vFrames, int hFrames) {
	texture = new TextureMaterial();
	texture->LoadShaders("TilemapVertexShader.shader", "TilemapFragmentShader.shader");
	texture->LoadTexture(filePath, imageType);
	textureBuffer = renderer->CreateTextureBuffer(texture->GetData(), texture->GetWidth(), texture->GetHeight(), texture->GetNrChannels());
	verticalFrames = vFrames;
	horizontalFrames = hFrames;
	totalFrames = verticalFrames * hFrames;
	spriteSize = Vector2(texture->GetSize().x / verticalFrames, texture->GetSize().y / horizontalFrames);
	Scale(spriteSize);
}

void Tilemap::Draw() {
	if (texture) {
		texture->Use();
		texture->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
		texture->SetTextureProperty("sprite", textureBuffer);
		texture->SetVec4("selfModulate", glm::vec4(selfModulate.r, selfModulate.g, selfModulate.b, selfModulate.a));
	}
	for (Tile tile : tiles) {
		if (texture) {
			texture->SetInt("tileId", tile.id);
			texture->SetInt("tileRows", horizontalFrames);
			texture->SetInt("tileColumns", verticalFrames);
			texture->SetVec2("offset", tile.tilemapPosition);
		}
		renderer->Draw(GetVertexArrayID(), primitive, 6);
	}
}

void Tilemap::Destroy() {
	if (texture) {
		texture->Destroy();
		delete texture;
	}
}

vector<Tilemap::Tile> Tilemap::GetColliderTiles() const {
	return colliderTiles;
}

Tilemap::Tilemap(Renderer *_renderer) : Sprite(_renderer) {
}

Tilemap::~Tilemap() {
}

AABB Tilemap::Tile::GetAABB() const {
	return AABB(position, position + size);
}
