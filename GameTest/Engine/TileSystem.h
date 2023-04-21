#ifndef TILESYSTEM_H
#define TILESYSTEM_H

#include <vector>
#include "../Math/Vec3.h"

enum class TILE_TYPE 
{
	FLOOR = 0,
	WALL,
	OBSTRUCTION,
	EXPLOSION,
	EXIT,
};

struct Tile
{
	TILE_TYPE tileType;
	MATH::Vec3 pos;
};

class TileSystem
{
private:
	static TileSystem* TileSystemInstance;

public:
	static TileSystem* getInstance() 
	{
		if (!TileSystemInstance) 
		{
			TileSystemInstance = new TileSystem();
		}
		return TileSystemInstance;
	}

public:
	std::vector<Tile> tiles;
	float tileSize;
	int rows;
	int columns;
	bool isExitRevealed;
	bool isExitLocked;

	TileSystem();
	~TileSystem();
	void GenerateTiles();
	void GenerateObstructions(int numObstructions_);
	void Render();
	void Reset();
};
#endif