#ifndef ENGINE_3D
#pragma once
#include "Exports.h"
#include "Utils.h"
#include "Sprite.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"

using namespace rapidjson;
using namespace std;

class ENGINEDLL_API Tilemap : public Sprite {
protected:
	struct Tile {
		int id = -1;
		Vector2 position;
		Vector2 tilemapPosition;
		Vector2 size;
		bool isCollider;

		AABB GetAABB() const { return AABB(position, size); };
		bool IsValid() { return id >= 0; };
	};
	struct TileObject {
		int id;
		int attribute;
		Vector2 position;
	};
private:
	enum LayerType {
		TILE_LAYER,
		OBJECT_GROUP,
		LAST
	};
	vector<vector<int>> colliderTiles; // Matriz de los tiles que colisionan
	vector<Tile> colliderMapTiles; // Tiles que son colisionables
	vector<Tile> mapTiles; // Todos los tiles
	vector<TileObject> mapObjects; // Todos los objetos
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	void ProcessLayers(Value& layers, Value& tilesets);
	void HandleLayer(const Value& layer, Value& tilesets);
	void HandleTileLayer(const Value& tilesData, const Value& tilesProperties);
	void HandleObjectsGroup(const Value& objects);
	bool CheckColliderTileProperty(int tileId, const Value& tileSet);
	void SetTexture(const char* filePath, int vFrames, int hFrames);
public:
	void LoadFromFile(const char* filePath);
	vector<TileObject> GetMapObjects() const;
	void Draw() override;
	void Destroy() override;
	Vector2 GetMapSize() const;
	Vector2 GetTileSize() const;
	bool IsColliderTile(Vector2 pos) const;
	Tile GetColliderTileAt(Vector2 pos) const;
	Tilemap();
	~Tilemap();
};
#endif

