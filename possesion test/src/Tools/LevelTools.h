#pragma once

#include <vector>

namespace lt
{
	static std::vector<std::vector<unsigned int>> generateBlockData(unsigned int width, unsigned int height)
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

}