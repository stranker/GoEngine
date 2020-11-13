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
		int id;
		Vector2 position;
		Vector2 tilemapPosition;
		Vector2 size;
		bool isCollider;

		AABB GetAABB() const;
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
	vector<Tile> colliderTiles;
	vector<Tile> mapTiles;
	vector<TileObject> mapObjects;
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	void ProcessLayers(Value& layers, Value& tilesets);
	void HandleLayer(const Value& layer, Value& tilesets);
	void HandleTileLayer(const Value& tilesData, const Value& tilesProperties);
	void HandleObjectsGroup(const Value& objects);
	bool IsColliderTile(int tileId, const Value& tileSet);
	void SetTexture(const char* filePath, ImageType imageType, int vFrames, int hFrames);
public:
	void LoadFromFile(const char* filePath);
	vector<TileObject> GetMapObjects() const;
	void Draw() override;
	void Destroy() override;
	vector<Tile> GetColliderTiles() const;
	Tilemap(Renderer *_renderer);
	~Tilemap();
};

