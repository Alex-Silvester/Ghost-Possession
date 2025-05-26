#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "../../Objects/GameObject.h"
#include "../../Objects/Objects.h"

#define BLOCK_DATA_POINTS 5

namespace lt
{
	union BlockData
	{
		struct
		{
			int width;
			int height;
			int position_x;
			int position_y;
			int block_type;
		};

		int data[BLOCK_DATA_POINTS] = {};
	};

	typedef std::vector<std::vector<unsigned int>> DataMatrix;
	static DataMatrix generateBlockMatrix(unsigned int width, unsigned int height)
	{
		DataMatrix data;

		unsigned int datum;
		for (unsigned int y = 0; y < height; y++)
		{
			data.emplace_back();
			for (unsigned int x = 0; x < width; x++)
			{
				datum = 0;
				if (y == height - 1)
				{
					datum = 6;
				}
				else if (y != 0)
				{
					datum = 3;
				}

				if (x == width - 1)
				{
					datum += 2;
				}
				else if (x != 0)
				{
					datum += 1;
				}

				data[y].emplace_back(datum);
			}
		}

		return data;
	}

	static std::vector<BlockData> readBlockData(std::string path)
	{
		std::ifstream file(path);
		std::istringstream data;
		std::string line;

		std::vector<BlockData> data_vector;

		while (std::getline(file, line))
		{
			data = std::istringstream(line);

			data_vector.emplace_back();

			for (int i = 0; i < BLOCK_DATA_POINTS; i++)
			{
				std::getline(data, line, ',');
				data_vector.back().data[i] = std::stoi(line);
			}
		}

		return data_vector;
	}

	static GameObject* getNewGameObject(char type)
	{
		switch (type)
		{
			case 0:return new Box();
			case 1: return new PObject();
			default:break;
		}
		return new Box();
	}

	//I know this isn't necessarily the best way to parse the level files
	// but it works
#define START_FLAG 0
#define END_FLAG 1
#define START_ID -1
#define END_ID -2
	static std::vector<GameObject*> createBlockArray(
		const std::vector<BlockData>& block_data,
		std::shared_ptr<sf::Texture>& block_texture,
		std::array<Visual*, 2> flags)
	{
		std::vector<GameObject*> objects;

		flags[START_FLAG]->setPosition(0,flags[END_FLAG]->getFloatRect().size.y);

		for (auto& datum : block_data)
		{
			if (datum.block_type == START_ID)
			{
				flags[START_FLAG]->setPosition( datum.position_x, datum.position_y );
				continue;
			}
			if (datum.block_type == END_ID)
			{
				flags[END_FLAG]->setPosition( datum.position_x, datum.position_y );
				continue;
			}

			objects.emplace_back(getNewGameObject(datum.block_type));

			DataMatrix data_matrix = generateBlockMatrix(datum.width, datum.height);

			objects.back()->generateTexture(data_matrix, { 32,32 }, block_texture);
			objects.back()->setPosition((float)datum.position_x, (float)datum.position_y);
		}

		return objects;
	}
}