#pragma once

#include <vector>
#include <fstream>
#include <sstream>

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

	static std::vector<std::vector<unsigned int>> generateBlockMatrix(unsigned int width, unsigned int height)
	{
		std::vector<std::vector<unsigned int>> data;

		unsigned int datum;
		for (int y = 0; y < height; y++)
		{
			data.emplace_back();
			for (int x = 0; x < width; x++)
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
}