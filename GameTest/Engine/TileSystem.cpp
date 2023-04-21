#include "stdafx.h"
#include "../App/app.h"
#include "TileSystem.h"
#include "GameManager.h"

TileSystem::TileSystem()
{
	tileSize = 48.8f;
	rows = 13;
	columns = 21;
	isExitRevealed = false;
	isExitLocked = true;
}

TileSystem::~TileSystem()
{
}

void TileSystem::GenerateTiles()
{
	Tile tile;
	MATH::Vec3 tilePos;

	//Starting Tile
	tilePos = MATH::Vec3(tileSize / 2, APP_VIRTUAL_HEIGHT - 90, 0.0f);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			//Default tile to be floor
			tile.tileType = TILE_TYPE::FLOOR;	

			//Set border tiles and checker pattern walls
			if (i == 0) { tile.tileType = TILE_TYPE::WALL; }
			if (i == rows - 1) { tile.tileType = TILE_TYPE::WALL; }
			if (j == 0) { tile.tileType = TILE_TYPE::WALL; }
			if (j == columns - 1) { tile.tileType = TILE_TYPE::WALL; }
			if (i % 2 == 0 && j % 2 == 0) { tile.tileType = TILE_TYPE::WALL; }

			tile.pos = tilePos;
			tiles.push_back(tile);

			tilePos.x += tileSize;
		}
		tilePos.x = tileSize / 2;
		tilePos.y -= tileSize;
	}
}

void TileSystem::GenerateObstructions(int numObstructions_)
{
	std::uniform_int_distribution<int> distribution(0, tiles.size() - 1);

	for (int i = 0; i < numObstructions_; i++)
	{
		bool isValidTile = false;

		while (!isValidTile)
		{
			int randomTile = distribution(GameManager::getInstance()->generator);

			//Keep starting area clear of obstructions 
			if (randomTile == columns + 1 || randomTile == columns + 2 || randomTile == 2 * columns + 1) { continue; }
			//Invalid placements
			if (tiles[randomTile].tileType == TILE_TYPE::WALL) { continue; }
			if (tiles[randomTile].tileType == TILE_TYPE::OBSTRUCTION) { continue; }
			if (tiles[randomTile].tileType == TILE_TYPE::EXIT) { continue; }
			//Add a special exit tile once, otherwise place obstruction
			if (i == 0) { tiles[randomTile].tileType = TILE_TYPE::EXIT; }
			else { tiles[randomTile].tileType = TILE_TYPE::OBSTRUCTION;}

			isValidTile = true;
		}
	}
}

void TileSystem::Render()
{
	float a = 1.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;

	float sx, sy, ex, ey;

	for (int i = 0; i < tiles.size(); i++)
	{
		a = 1.0f;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;

		Tile tile = tiles[i];
		switch (tile.tileType)
		{
		case TILE_TYPE::WALL:
			//Draw wall square
			
			//Top
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y + tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Right
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Bottom
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y - tileSize / 2;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Left
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y - tileSize / 2;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y + tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			break;

		case TILE_TYPE::OBSTRUCTION:
			//Draw obstruction bricks

			//Top
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y + tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Right
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Bottom
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y - tileSize / 2;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Left
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y - tileSize / 2;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y + tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Horizontal Slice Top Third
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y + tileSize / 2 - tileSize / 3;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y + tileSize / 2 - tileSize / 3;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Horizontal Slice Bottom Third
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y - tileSize / 2 + tileSize / 3;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y - tileSize / 2 + tileSize / 3;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Left Vertical Slice
			sx = tile.pos.x - tileSize / 2 + tileSize / 4;
			sy = tile.pos.y + tileSize / 2 - tileSize / 3;
			ex = tile.pos.x - tileSize / 2 + tileSize / 4;
			ey = tile.pos.y - tileSize / 2 + tileSize / 3;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Right Vertical Slice
			sx = tile.pos.x + tileSize / 2 - tileSize / 3;
			sy = tile.pos.y - tileSize / 2 + tileSize / 3;
			ex = tile.pos.x + tileSize / 2 - tileSize / 3;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			break;

		case TILE_TYPE::EXPLOSION:
			//Draw explosion burst

			r = 1.0;
			g = 0.8;
			b = 0.0;

			sx = tile.pos.x;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y - tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y + tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			break;

		case TILE_TYPE::EXIT:
			//Draw special exit tile

			if (isExitRevealed)
			{
				//Draw door instead of obstruction bricks
				a = 1.0f;
				r = 0.8f;
				g = 0.4f;
				b = 0.2f;

				if (!isExitLocked)
				{
					r = 0.0f;
					g = 1.0f;
					b = 0.6f;
				}

				sx = tile.pos.x;
				sy = tile.pos.y + tileSize / 3;
				ex = tile.pos.x + tileSize / 3;
				ey = tile.pos.y - tileSize / 3;
				App::DrawLine(sx, sy, ex, ey, r, g, b);
				sx = tile.pos.x + tileSize / 3;
				sy = tile.pos.y - tileSize / 3;
				ex = tile.pos.x - tileSize / 3;
				ey = tile.pos.y - tileSize / 3;
				App::DrawLine(sx, sy, ex, ey, r, g, b);
				sx = tile.pos.x - tileSize / 3;
				sy = tile.pos.y - tileSize / 3;
				ex = tile.pos.x;
				ey = tile.pos.y + tileSize / 3;
				App::DrawLine(sx, sy, ex, ey, r, g, b);
				sx = tile.pos.x;
				sy = tile.pos.y - tileSize / 3;
				ex = tile.pos.x + tileSize / 3;
				ey = tile.pos.y + tileSize / 3;
				App::DrawLine(sx, sy, ex, ey, r, g, b);
				sx = tile.pos.x + tileSize / 3;
				sy = tile.pos.y + tileSize / 3;
				ex = tile.pos.x - tileSize / 3;
				ey = tile.pos.y + tileSize / 3;
				App::DrawLine(sx, sy, ex, ey, r, g, b);
				sx = tile.pos.x - tileSize / 3;
				sy = tile.pos.y + tileSize / 3;
				ex = tile.pos.x;
				ey = tile.pos.y - tileSize / 3;
				App::DrawLine(sx, sy, ex, ey, r, g, b);

				continue;
			}
			//Draw obstruction bricks

			//Top
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y + tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Right
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y + tileSize / 2;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Bottom
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y - tileSize / 2;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Left
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y - tileSize / 2;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y + tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Horizontal Slice Top Third
			sx = tile.pos.x - tileSize / 2;
			sy = tile.pos.y + tileSize / 2 - tileSize / 3;
			ex = tile.pos.x + tileSize / 2;
			ey = tile.pos.y + tileSize / 2 - tileSize / 3;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Horizontal Slice Bottom Third
			sx = tile.pos.x + tileSize / 2;
			sy = tile.pos.y - tileSize / 2 + tileSize / 3;
			ex = tile.pos.x - tileSize / 2;
			ey = tile.pos.y - tileSize / 2 + tileSize / 3;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Left Vertical Slice
			sx = tile.pos.x - tileSize / 2 + tileSize / 4;
			sy = tile.pos.y + tileSize / 2 - tileSize / 3;
			ex = tile.pos.x - tileSize / 2 + tileSize / 4;
			ey = tile.pos.y - tileSize / 2 + tileSize / 3;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			//Right Vertical Slice
			sx = tile.pos.x + tileSize / 2 - tileSize / 3;
			sy = tile.pos.y - tileSize / 2 + tileSize / 3;
			ex = tile.pos.x + tileSize / 2 - tileSize / 3;
			ey = tile.pos.y - tileSize / 2;
			App::DrawLine(sx, sy, ex, ey, r, g, b);
			break;
		default:
			break;
		}
	}
}

void TileSystem::Reset()
{
	tiles.clear();
}
