#ifndef ENGINE_3D
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
			tile.isCollider = CheckColliderTileProperty(tile.id, tilesProperties);
			if (tile.isCollider) {
				colliderTiles[row][column] = 1;
				colliderMapTiles.push_back(tile);
			}
			mapTiles.push_back(tile);
		}
		column++;
		if (column % width == 0 && column != 0) {
			column = 0;
			row++;
		}
	}
}

void Tilemap::HandleObjectsGroup(const Value & objects) {
	assert(objects.IsArray());
	for (Value::ConstValueIterator itr = objects.GetArray().Begin(); itr != objects.GetArray().End(); ++itr) {
		const Value& object = *itr;
		TileObject tileObject;
		tileObject.id = object["id"].GetInt();
		tileObject.position = Vector2(object["x"].GetFloat(), object["y"].GetFloat());
		tileObject.attribute = object["properties"].GetArray()[0]["value"].GetInt();
		mapObjects.push_back(tileObject);
	}
}

bool Tilemap::CheckColliderTileProperty(int tileId, const Value & tileSet) {
	assert(tileSet.IsArray());
	for (Value::ConstValueIterator itr = tileSet.GetArray().Begin(); itr != tileSet.GetArray().End(); ++itr) {
		const Value& tileProperty = *itr;
		if (tileId == tileProperty["id"].GetInt()) {
			return true;
		}
	}
	return false;
}

bool Tilemap::IsColliderTile(Vector2 pos) const{
	if (pos.x >= width || pos.y >= height) {
		return false;
	}
	return colliderTiles[pos.y][pos.x] == 1;
}

Tilemap::Tile Tilemap::GetColliderTileAt(Vector2 pos) const{
	Tile tile;
	for (Tile t : colliderMapTiles) {
		if (t.tilemapPosition == pos) {
			tile = t;
		}
	}
	return tile;
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

	vector<vector<int>> colliderTilemap(height, vector<int>(width));
	colliderTiles = colliderTilemap;

	Value& layers = d["layers"];
	Value& tileset = d["tilesets"].GetArray()[0];
	const char *tilesetFilePath = tileset["image"].GetString();
	ProcessLayers(layers, tileset);
	SetTexture(tilesetFilePath, tileset["columns"].GetInt(), tileset["imageheight"].GetInt() / tileset["tileheight"].GetInt());
}

vector<Tilemap::TileObject> Tilemap::GetMapObjects() const {
	return mapObjects;
}

void Tilemap::SetTexture(const char * filePath, int vFrames, int hFrames) {
	material = ResourceManager::LoadMaterial("Shaders/TextureVertexShader.shader", "Shaders/TextureFragmentShader.shader", "sprite");
	texture = ResourceManager::LoadTexture(filePath, "sprite");
	verticalFrames = vFrames;
	horizontalFrames = hFrames;
	totalFrames = verticalFrames * hFrames;
	spriteSize = Vector2(texture->GetWidth() / verticalFrames, texture->GetHeight() / horizontalFrames);
	Scale(spriteSize);
}

void Tilemap::Draw() {
	if (material) {
		material->Use();
		material->SetMat4("mvp", Renderer::GetSingleton()->GetCamera()->GetMVPOf(*transform));
		material->SetTexture("sprite", texture->GetTextureID(), 0);
		material->SetInt("tileRows", horizontalFrames);
		material->SetInt("tileColumns", verticalFrames);
		material->SetVec4("selfModulate", glm::vec4(selfModulate.r, selfModulate.g, selfModulate.b, selfModulate.a));
	}
	for (Tile tile : mapTiles) {
		if (material) {
			material->SetInt("tileId", tile.id);
			material->SetVec2("offset", tile.tilemapPosition);
		}
		Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, 6, true);
	}
}

void Tilemap::Destroy() {
}

Vector2 Tilemap::GetMapSize() const {
	return Vector2(width, height);
}

Vector2 Tilemap::GetTileSize() const {
	return Vector2(tileWidth, tileHeight);
}

Tilemap::Tilemap() {
}

Tilemap::~Tilemap() {
}
#endif