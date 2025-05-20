
#include <iostream>
#include <fstream>
#include <filesystem>

inline void wait() { while (getchar() != 'e') {} }

int main()
{
	std::string input;
	while (input != "1" && input != "2")
	{
		printf("1. create new level\n2. edit existing file\n");
		std::cin >> input;
	}

	std::string name;

	//crate/check the file
	if (input == "1")
	{
		printf("Enter file name: ");
		std::cin >> name;

		int index = 0;
		while (std::filesystem::exists("Data/" + name +".txt"))
		{
			index++;
			name += "_" + std::to_string(index);
		}
		std::ofstream new_file("Data/" + name + ".txt");
		new_file.close();
	}
	else
	{
		if (!std::filesystem::exists("Data/" + name + ".txt"))
		{
			std::cout << "[ERROR] file path doesn't exist : Data/" + name + ".txt\n";
			wait();
			return 0;
		}
	}

	wait();
	return 0;
}