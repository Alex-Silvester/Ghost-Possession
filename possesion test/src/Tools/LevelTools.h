#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "../GameObject.h"
#include "../Objects/Objects.h"

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

	static GameObject* getNewGameObject(int type)
	{
		switch (type)
		{
			case 0:return new Box();
			case 1: return new PObject();
			default:break;
		}
		return new GameObject();
	}

	static std::vector<GameObject*> createBlockArray(const std::vector<BlockData>& block_data, sf::Texture* texture)
	{
		std::vector<GameObject*> object_type = { new Box(), new PObject() };

		std::vector<GameObject*> objects;

		for (auto& datum : block_data)
		{
			objects.emplace_back(getNewGameObject(datum.block_type));

			DataMatrix data_matrix = generateBlockMatrix(datum.width, datum.height);

			objects.back()->generateTexture(data_matrix, { 32,32 }, texture);
			objects.back()->setPosition((float)datum.position_x, (float)datum.position_y);
		}

		return objects;
	}
}