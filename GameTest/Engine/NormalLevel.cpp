#include "stdafx.h"
#include <random>
#include "GameManager.h"
#include "NormalLevel.h"

NormalLevel::NormalLevel()
{
}

NormalLevel::~NormalLevel()
{
}

bool NormalLevel::Init()
{
	TileSystem* tileSystem = TileSystem::getInstance();

	tileSystem->GenerateTiles();
	tileSystem->GenerateObstructions(45);
	player.pos = tileSystem->tiles[tileSystem->columns + 1].pos;
	SpawnEnemies(7);
	tileSystem->isExitRevealed = false;
	tileSystem->isExitLocked = true;

	return true;
}

void NormalLevel::Update(float deltaTime_)
{
	TileSystem* tileSystem = TileSystem::getInstance();

	player.Update(deltaTime_);

	std::vector<int>directions{ 0,1,2,3 };		//Corresponds to enemy MOVEMENT_DIRECTION enum class

	//Check if exit is uncovered and no enemies remain
	if (enemies.size() == 0 && tileSystem->isExitRevealed == true) { tileSystem->isExitLocked = false; }

	//Handle enemy movement
	for (int i = 0; i < enemies.size(); i++)
	{
		//Randomize the enemies next direction of travel
		std::random_shuffle(directions.begin(), directions.end());

		if (enemies[i].currentTileIndex == enemies[i].targetTileIndex) 
		{ 
			bool isValidDirection = false;

			//Try to continue in current direction first
			int randomDirection = static_cast<int>(enemies[i].movementDirection);

			for (int j = 0; j < directions.size(); j++)
			{
				switch (randomDirection)
				{
				case 0:
					if (tileSystem->tiles[enemies[i].currentTileIndex - tileSystem->columns].tileType == TILE_TYPE::FLOOR)
					{
						enemies[i].targetTileIndex = enemies[i].currentTileIndex - tileSystem->columns;
						enemies[i].movementDirection = MOVEMENT_DIRECTION::UP;
						isValidDirection = true;
					}
					break;
				case 1:
					if (tileSystem->tiles[enemies[i].currentTileIndex + tileSystem->columns].tileType == TILE_TYPE::FLOOR)
					{
						enemies[i].targetTileIndex = enemies[i].currentTileIndex + tileSystem->columns;
						enemies[i].movementDirection = MOVEMENT_DIRECTION::DOWN;
						isValidDirection = true;
					}
					break;
				case 2:
					if (tileSystem->tiles[enemies[i].currentTileIndex - 1].tileType == TILE_TYPE::FLOOR)
					{
						enemies[i].targetTileIndex = enemies[i].currentTileIndex - 1;
						enemies[i].movementDirection = MOVEMENT_DIRECTION::LEFT;
						isValidDirection = true;
					}
					break;
				case 3:
					if (tileSystem->tiles[enemies[i].currentTileIndex + 1].tileType == TILE_TYPE::FLOOR)
					{
						enemies[i].targetTileIndex = enemies[i].currentTileIndex + 1;
						enemies[i].movementDirection = MOVEMENT_DIRECTION::RIGHT;
						isValidDirection = true;
					}
					break;
				default:
					break;
				}
				//Try next of the shuffled directions
				randomDirection = directions[j];
			}
		}
		enemies[i].Update(deltaTime_);

		//Enemy is very close to target tile so move it to exact position and set currentTile to targetTile
		if (MATH::Vec3::distance(enemies[i].pos, tileSystem->tiles[enemies[i].targetTileIndex].pos) < 2)
		{
			enemies[i].pos = tileSystem->tiles[enemies[i].targetTileIndex].pos;
			enemies[i].currentTileIndex = enemies[i].targetTileIndex;
		}
		//Enemy has collided with player
		if (MATH::Vec3::distance(enemies[i].pos, player.pos) < (enemies[i].objectSize / 2 + player.objectSize / 2))
		{
			GameManager::getInstance()->playerStats.livesRemaining -= 1;
			enemies.erase(enemies.begin() + i);

			//Player loses, return to menu
			if (GameManager::getInstance()->playerStats.livesRemaining == 0)
			{
				GameManager::getInstance()->BuildLevel(LEVEL_TYPE::MENU);
			}
		}
	}

	//Handle bombs
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i].Update(deltaTime_);

		//Check if enemy has contacted a landmine
		if (bombs[i].bombType == BOMB_TYPE::LANDMINE)
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				if (MATH::Vec3::distance(enemies[j].pos, bombs[i].pos) < (enemies[j].objectSize / 2))
				{
					bombs[i].timeUntilDetonation = 0;
				}
			}
		}

		//Explosion has ended, adjust tiles and destroy the bomb
		if (bombs[i].timeUntilExplosionEnds <= 0)
		{
			for (int j = 0; j < bombs[i].affectedTileIndices.size(); j++)
			{
				if (tileSystem->tiles[bombs[i].affectedTileIndices[j]].tileType == TILE_TYPE::EXIT)
				{
					tileSystem->isExitRevealed = true;
				}
				else
				{
					tileSystem->tiles[bombs[i].affectedTileIndices[j]].tileType = TILE_TYPE::FLOOR;
				}
			}
			bombs.erase(bombs.begin() + i);
			continue;
		}

		//Explosion timer hits 0, blow up the bomb
		if (bombs[i].timeUntilDetonation <= 0)
		{
			bombs[i].isDetonated = true;
			CreateExplosion(i);
		}
	}

	//Handle enemies contacting explosions and player movement obstructions
	for (int i = 0; i < tileSystem->tiles.size(); i++)
	{
		if (tileSystem->tiles[i].tileType == TILE_TYPE::FLOOR) { continue; }
		//Destroy enemies in contact with explosions
		if (tileSystem->tiles[i].tileType == TILE_TYPE::EXPLOSION) 
		{ 
			for (int j = 0; j < enemies.size(); j++)
			{
				if (MATH::Vec3::distance(enemies[j].pos, tileSystem->tiles[i].pos) < (tileSystem->tileSize / 2))
				{
					enemies.erase(enemies.begin() + j);
				}
			}
			continue;
		}
		//Block player movement into obstructions
		Vec3 tilePos = tileSystem->tiles[i].pos;
		if (MATH::Vec3::distance(player.pos, tilePos) < (tileSystem->tileSize / 2 + player.objectSize / 2))
		{
			if (tileSystem->tiles[i].tileType == TILE_TYPE::EXIT && tileSystem->isExitLocked == false)
			{
				GameManager::getInstance()->playerStats.levelsCleared += 1;
				GameManager::getInstance()->BuildLevel(LEVEL_TYPE::NORMAL);
			}
			player.pos = player.prevPos;
		}
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))		//"SPACE"
	{
		SpawnBomb();
	}
}

void NormalLevel::Render()
{
	TileSystem::getInstance()->Render();
	player.Render();
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Render();
	}
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i].Render();
	}
}

void NormalLevel::Shutdown()
{
	TileSystem::getInstance()->~TileSystem();
}

void NormalLevel::SpawnBomb()
{
	TileSystem* tileSystem = TileSystem::getInstance();

	Bomb bomb;
	bomb.bombType = player.selectedBombType;

	for (int i = 0; i < tileSystem->tiles.size(); i++)
	{
		//Get tile the player is on, place the bomb on the tile
		if (MATH::Vec3::distance(player.pos, tileSystem->tiles[i].pos) < (tileSystem->tileSize / 2))
		{
			bomb.pos = tileSystem->tiles[i].pos;
			bombs.push_back(bomb);
		}
	}
	//Set boolean for pausing game until player sets direction
	if (bomb.bombType == BOMB_TYPE::DIRECTIONAL) { directionalBombRequiresDirection = true; }
}

void NormalLevel::CreateExplosion(int bombIndex_)
{
	TileSystem* tileSystem = TileSystem::getInstance();

	//Indices of next adjacent tile in each direction
	int upAdjacentIndex, rightAdjacentIndex, leftAdjacentIndex, downAdjacentIndex;

	for (int i = 0; i < tileSystem->tiles.size(); i++)
	{
		//Find the tile the bomb sits on
		if (MATH::Vec3::distance(bombs[bombIndex_].pos, tileSystem->tiles[i].pos) < (tileSystem->tileSize / 2))
		{
			tileSystem->tiles[i].tileType = TILE_TYPE::EXPLOSION;
			bombs[bombIndex_].affectedTileIndices.push_back(i);

			//Landmine only affects the tile it is on
			if (bombs[bombIndex_].bombType == BOMB_TYPE::LANDMINE) { return; }

			//Handle tiles affected by a directional bomb
			if (bombs[bombIndex_].bombType == BOMB_TYPE::DIRECTIONAL)
			{
				int adjacentIndex;
				for (int j = 1; j < 4; j++)
				{
					//Calculate relevant tile adjacency
					if (bombs[bombIndex_].directionalBombDirection == DIRECTIONAL_BOMB_DIRECTION::UP) 
					{ 
						adjacentIndex = upAdjacentIndex = i - tileSystem->columns * j;
					}
					if (bombs[bombIndex_].directionalBombDirection == DIRECTIONAL_BOMB_DIRECTION::DOWN)
					{
						adjacentIndex = upAdjacentIndex = i + tileSystem->columns * j;
					}
					if (bombs[bombIndex_].directionalBombDirection == DIRECTIONAL_BOMB_DIRECTION::LEFT)
					{
						adjacentIndex = upAdjacentIndex = i - 1 * j;
					}
					if (bombs[bombIndex_].directionalBombDirection == DIRECTIONAL_BOMB_DIRECTION::RIGHT)
					{
						adjacentIndex = upAdjacentIndex = i + 1 * j;
					}

					//Adjacent tile is not a wall
					if (tileSystem->tiles[adjacentIndex].tileType != TILE_TYPE::WALL)
					{
						bombs[bombIndex_].affectedTileIndices.push_back(adjacentIndex);
						//Change tile to explosion if it is not the exit tile
						if (tileSystem->tiles[adjacentIndex].tileType != TILE_TYPE::EXIT)
						{
							tileSystem->tiles[adjacentIndex].tileType = TILE_TYPE::EXPLOSION;
						}
					}

					//Break if no valid adjacent tiles
					else
					{
						break;
					}
				}
			}

			//Handle tiles affected by a normal bomb
			if (bombs[bombIndex_].bombType == BOMB_TYPE::NORMAL)
			{
				//Check upwards adjacency
				for (int j = 1; j < 2; j++)
				{
					upAdjacentIndex = i - tileSystem->columns * j;
					if (tileSystem->tiles[upAdjacentIndex].tileType != TILE_TYPE::WALL)
					{
						bombs[bombIndex_].affectedTileIndices.push_back(upAdjacentIndex);
						//Change tile to explosion if it is not the exit tile
						if (tileSystem->tiles[upAdjacentIndex].tileType != TILE_TYPE::EXIT)
						{
							tileSystem->tiles[upAdjacentIndex].tileType = TILE_TYPE::EXPLOSION;
						}
					}
					else
					{
						break;
					}
				}
				//Check rightwards adjacency
				for (int j = 1; j < 2; j++)
				{
					rightAdjacentIndex = i + 1 * j;
					if (tileSystem->tiles[rightAdjacentIndex].tileType != TILE_TYPE::WALL)
					{
						bombs[bombIndex_].affectedTileIndices.push_back(rightAdjacentIndex);
						//Change tile to explosion if it is not the exit tile
						if (tileSystem->tiles[rightAdjacentIndex].tileType != TILE_TYPE::EXIT)
						{
							tileSystem->tiles[rightAdjacentIndex].tileType = TILE_TYPE::EXPLOSION;
						}
					}
					else
					{
						break;
					}
				}
				//Check leftwards adjacency
				for (int j = 1; j < 2; j++)
				{
					leftAdjacentIndex = i - 1 * j;
					if (tileSystem->tiles[leftAdjacentIndex].tileType != TILE_TYPE::WALL)
					{
						bombs[bombIndex_].affectedTileIndices.push_back(leftAdjacentIndex);
						//Change tile to explosion if it is not the exit tile
						if (tileSystem->tiles[leftAdjacentIndex].tileType != TILE_TYPE::EXIT)
						{
							tileSystem->tiles[leftAdjacentIndex].tileType = TILE_TYPE::EXPLOSION;
						}
					}
					else
					{
						break;
					}
				}
				//Check downwards adjacency
				for (int j = 1; j < 2; j++)
				{
					downAdjacentIndex = i + tileSystem->columns * j;
					if (tileSystem->tiles[downAdjacentIndex].tileType != TILE_TYPE::WALL)
					{
						bombs[bombIndex_].affectedTileIndices.push_back(downAdjacentIndex);
						//Change tile to explosion if it is not the exit tile
						if (tileSystem->tiles[downAdjacentIndex].tileType != TILE_TYPE::EXIT)
						{
							tileSystem->tiles[downAdjacentIndex].tileType = TILE_TYPE::EXPLOSION;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}

void NormalLevel::SpawnEnemies(int numberOfEnemies_)
{
	TileSystem* tileSystem = TileSystem::getInstance();

	Enemy enemy;

	std::random_device generator;
	std::uniform_int_distribution<int> distribution(0, tileSystem->tiles.size() - 1);

	for (int i = 0; i < numberOfEnemies_; i++)
	{
		bool isValidTile = false;

		while (!isValidTile)
		{
			int randomTile = distribution(generator);

			//Prevent enemy spawn near player start and on obstacles
			if (randomTile == tileSystem->columns + 1 || randomTile == tileSystem->columns + 2 
				|| randomTile == 2 * tileSystem->columns + 1) { continue; }
			if (tileSystem->tiles[randomTile].tileType == TILE_TYPE::WALL) { continue; }
			if (tileSystem->tiles[randomTile].tileType == TILE_TYPE::OBSTRUCTION) { continue; }
			if (tileSystem->tiles[randomTile].tileType == TILE_TYPE::EXIT) { continue; }

			enemy.pos = tileSystem->tiles[randomTile].pos;
			enemy.currentTileIndex = randomTile;
			enemy.targetTileIndex = randomTile;
			enemies.push_back(enemy);
			isValidTile = true;
		}
	}
}