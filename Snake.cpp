#include <iostream>
#include <conio.h>
#include <Windows.h>
bool gameOver;
const int width = 21, height = 21;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
eDirection prevDir;
int tailX[100], tailY[100];
int nTail;
bool print;
int sleep = 100;
bool game = true;
void dificultyLevel();
void Game();
void MainMenu()
{
	gameOver = false;
	system("cls");
	std::cout << "/t/t/t SNAKE!" << std::endl << std::endl;
	std::cout << "/t MAIN MENU" << std::endl;
	std::cout << "New Game - 1" << std::endl;
	std::cout << "Dificulty Level - 2" << std::endl;
	std::cout << "Exit - 0" << std::endl;
	switch (_getch())
	{
	case '1':
		Game();
		break;
	case '2':
		dificultyLevel();
		break;
	case '0':
		game = false;
		break;
	default:
		break;
	}
}
void dificultyLevel()
{
	system("cls");
	std::cout << "Easy - 1" << std::endl;
	std::cout << "Medium - 2" << std::endl;
	std::cout << "Hard - 3" << std::endl;
	switch (_getch())
	{
	case '1':
		sleep = 500;
		MainMenu();
		break;
	case '2':
		sleep = 100;
		MainMenu();
		break;
	case '3':
		sleep = 20;
		MainMenu();
		break;
	};
}
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width+2; i++)
		std::cout << "#";
	std::cout << std::endl;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width+2; i++)
		{
			if (i == 0 || i == width)
				std::cout << "#";
			if (x == i && y == j)
			{
				std::cout << "O";
			}
			else if (i == fruitX && j == fruitY)
			{
				std::cout << "*";
			}
			else
			{
				for (int k = 0; k < nTail; k++)
				{
					print = false;
					if (tailX[k] == i && tailY[k] == j)
					{
						std::cout << "o";
						print = true;
					}
				}
				if(!print)
					std::cout << " ";
			}	
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < width+2; i++)
		std::cout << "#";
	std::cout << std::endl << std::endl << "SCORE: " << score << std::endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		if(prevDir != RIGHT)
			x--;
		break;
	case RIGHT:
		if (prevDir != LEFT)
			x++;
		break;
	case UP:
		if (prevDir != DOWN)
			y--;
		break;
	case DOWN:
		if (prevDir != UP)
			y++;
		break;
	default:
		break;
	}
	prevDir = dir;
	/*if (x >= width || x < 0 || y < 0 || y >= height)
		gameOver = true;*/
	if (x > width) x = 0; if (x < 0) x = width - 1; if (y > height) y = 0; if (y < 0) y = height - 1;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		nTail++;
		fruitX = rand() % width + 1;
		fruitY = rand() % height + 1;
	}
}
void Game()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(sleep);
	}
	MainMenu();
}
int main()
{
	while(game)
		MainMenu();
	return 0;
}