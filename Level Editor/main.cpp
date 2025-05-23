
#include <iostream>
#include <fstream>
#include <filesystem>

#include "src/Editor.h"

inline void wait() { while (getchar() != 'e') {} }

int main()
{
	std::string input;
	while (input != "1" && input != "2" && input != "skip")
	{
		printf("1. create new level\n2. edit existing file\nskip: skip file\n");
		std::cin >> input;
	}

	std::string name;

	//create/check the file
	if (input == "skip") { printf("Skipped\n"); }
	else if (input == "1")
	{
		printf("Enter file name: ");
		std::cin >> name;

		int index = 0;
		while (std::filesystem::exists("Data/" + name +".txt"))
		{
			index++;
			name += "_" + std::to_string(index);
		}
	}
	else
	{
		printf("Enter file name: ");
		std::cin >> name;

		if (!std::filesystem::exists("Data/" + name + ".txt"))
		{
			std::cout << "[ERROR] file path doesn't exist : Data/" + name + ".txt\n";
			wait();
			return 0;
		}
	}

	Editor editor;

	if (!editor.init(name.length() == 0 ? "" : "Data/"+name+".txt"))
	{
		printf("failed init\n");
		editor.end();
		wait();
		return 0;
	}

	editor.run();

	printf("Ending task...\n");
	editor.end();

	wait();
	return 0;
}