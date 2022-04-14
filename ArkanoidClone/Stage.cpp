#include "Stage.h"
#include "Bricks.h"
#include "Utility.h"
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <filesystem>

bool Stage::CalculateBricksPositions() 
{
	sf::Vector2f startingPosition = playgroundPosition;
	sf::Vector2f offset = PixelSizes::GetInstance().brickSize;

	for (int i = 0; i < BRICK_COLUMNS; i++)
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{
			if (bricks[i][j] != nullptr)
				bricks[i][j]->SetPosition({startingPosition.x + offset.x * i,
										   startingPosition.y + offset.y * j });
		}
	}

	return true;
}

void GenerateDefaultMapFile(std::string filename)
{
	std::filesystem::path path = std::filesystem::current_path().append("Stages");
	std::filesystem::create_directory(path);
	path.append(filename).concat(".txt");

	std::ofstream file(path);

	if(file) 
	{
		for (int i = 0; i < BRICK_ROWS; i++)
		{
			for (int j = 0; j < BRICK_COLUMNS; j++)
			{
				file << "* ";
			}
			file << std::endl;
		}
	}
	file.close();
}

Stage::~Stage()
{
	for (int i = 0; i < BRICK_COLUMNS; i++)
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{
			delete bricks[i][j];
		}
	}

}

Stage::Stage(int _stageNumber, sf::Vector2f _playgroundPosition): stageNumber(_stageNumber), playgroundPosition(_playgroundPosition)
{
	GenerateDefaultMapFile("default");
	if (!LoadMapFromFileToArray())
	{
		playable = false;
		return;
	}

	SetUpBlocks();
	CalculateBricksPositions();

	playable = true;
}

inline std::string GetFilename(int _stageNumber)
{
	if (_stageNumber > 0 && _stageNumber <= 32)
	{
		std::string filename = "Stage_" + std::to_string(_stageNumber);
		return filename;
	}
	return "Stage_1";
}

inline void Stage::FillStageArray(std::vector<char> stageVector)
{
	int vectorIndex = 0;

	for (int j = 0; j < BRICK_ROWS; j++)
	{
		for (int i = 0; i < BRICK_COLUMNS; i++)
		{
			char letter = tolower( stageVector[vectorIndex] );
			stageArray[i][j] = stageVector[vectorIndex];
			vectorIndex++;
		}
	}
}

IBrick* Stage::ChooseBrick(char letter)
{
	switch (letter)
	{
	case '*':
		return nullptr;
		break;
	case 's':
		return new SilverBrick(stageNumber);
		break;
	case 'x':
		return new GoldBrick();
		break;
	case 'w':
		return new ColorBrick(ColorsEnum::white);
		break;
	case 'o':
		return new ColorBrick(ColorsEnum::orange);
		break;
	case 't':
		return new ColorBrick(ColorsEnum::turquoise);
		break;
	case 'g':
		return new ColorBrick(ColorsEnum::green);
		break;
	case 'r':
		return new ColorBrick(ColorsEnum::red);
		break;
	case 'b':
		return new ColorBrick(ColorsEnum::blue);
		break;
	case 'p':
		return new ColorBrick(ColorsEnum::pink);
		break;
	case 'y':
		return new ColorBrick(ColorsEnum::yelow);
		break;

	default:
		std::cout << "ERROR, CHECK SYNTAX IN FILE Stage_"<< stageNumber << std::endl;
		return nullptr;
		break;
	}
}

void FillWithVoid(std::vector<char>& tempVector)
{
	if (tempVector.size() > BRICK_COLUMNS * BRICK_ROWS)
	{
		std::cout << "Error: Loaded stage was too large." << std::endl;
		while (tempVector.size() != BRICK_COLUMNS * BRICK_ROWS)
		{
			tempVector.pop_back();
		}
	}
	else if(tempVector.size() < BRICK_COLUMNS * BRICK_ROWS)
	{
		std::cout << "Error: Loaded stage was too small." << std::endl;
		while (tempVector.size() != BRICK_COLUMNS * BRICK_ROWS)
		{
			tempVector.push_back('*');
		}
	}
}

std::vector<char> ReadFile(int _stageNumber)
{
	std::vector<char> tempVector; 
	std::filesystem::path path = std::filesystem::current_path().append("Stages");
	path.append(GetFilename(_stageNumber)).concat(".txt");

	if (!std::filesystem::exists(path))
	{
		std::cout << "Error: Couldnt find folder Stage" << std::endl;
		return tempVector;
	}

	std::ifstream file(path);
	if (file)
	{
		char brickID;
		while (file >> brickID)
		{
			tempVector.push_back(brickID);
		}
	}
	file.close();

	FillWithVoid(tempVector);

	return tempVector;
}

bool ValidateStageArray(char _stageArray[BRICK_COLUMNS][BRICK_ROWS])
{
	std::regex validate("[sxwotgrbpy\\*]");
	std::vector<char> validSymbols{ '*','s','x','w','o','t','g','r','b','p','y' };
	for (int i = 0; i < BRICK_COLUMNS; i++)
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{
			std::string s(1, _stageArray[i][j]);
			if (!std::regex_match( s , validate))
			{
				std::cerr << "Blad w pliku stage, znaleziono \"" << s << "\"" << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool Stage::LoadMapFromFileToArray()
{
	FillStageArray(ReadFile(stageNumber));
	return ValidateStageArray(stageArray);
}

bool Stage::SetUpBlocks()
{
	for (int i = 0; i < BRICK_COLUMNS; i++)
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{
			bricks[i][j] = ChooseBrick(stageArray[i][j]);
		}
	}
	return true;
}

void Stage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!playable)
		return;
	for (int j = 0; j < BRICK_ROWS; j++)
	{
		for (int i = 0; i < BRICK_COLUMNS; i++)
		{
			if (bricks[i][j] != nullptr)
			{
				target.draw(*bricks[i][j]);
			}
				
		}
	}

}

void Stage::UpdatePlayableBricks()
{
	playableBricks.clear();
	for (int i = 0; i < BRICK_COLUMNS; i++)
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{
			if (bricks[i][j] != nullptr)
				playableBricks.push_back(bricks[i][j]);
		}
	}
}