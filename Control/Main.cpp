#include <SFML/Graphics.hpp>
#include <math.h>
#include <sstream>
#include "Tile.h"
#include "Canvas.h"

using namespace std;

//constants
const int WIN_WIDTH = 1024, WIN_HEIGHT = 768;
const int BOARD_SIZE = 6;
const int BOARD_ORIGIN_X = 100, BOARD_ORIGIN_Y = 100;
const int TILE_SIZE = 100;
const int UNIT_START_SIZE = 20;

//variables
Tile selectedTile;
int playerTurn = 1;
int turn;
int totalUnitsP1, totalUnitsP2;
int moveAmount;
vector<Tile> subArray(BOARD_SIZE);
vector<vector<Tile>> board(BOARD_SIZE, subArray);

//core init
sf::RenderWindow mainWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Control");

//states
bool tileSelected = false;

void newGame()
{
	turn = 1;
	totalUnitsP1 = 0, totalUnitsP2 = 0;
	moveAmount = 0;
	for (int i=0; i<board.size(); i++)
	{
		for (int j=0; j<board.size(); j++)
		{
			if (j == 0) //player 2
			{
				board[i][j] = Tile(2, UNIT_START_SIZE, i, j);
				totalUnitsP2 += UNIT_START_SIZE;
			}
			else if (j == board.size()-1) //player 1
			{
				board[i][j] = Tile(1, UNIT_START_SIZE, i, j);
				totalUnitsP1 += UNIT_START_SIZE;
			}
			else //neutral
				board[i][j] = Tile(0, 0, i, j);
		}
	}
}

	bool testTileClicked(float x, float y)
	{
		bool inXRange = false, inYRange = false;
		if (x >= BOARD_ORIGIN_X && x < BOARD_SIZE * TILE_SIZE + BOARD_ORIGIN_X)
			inXRange = true;
		if (y >= BOARD_ORIGIN_Y && y < BOARD_SIZE * TILE_SIZE + BOARD_ORIGIN_Y)
			inYRange = true;

		if (inXRange && inYRange)
			return true;
		return false;
	}

	Tile getClickedTile(float x, float y)
	{
		int column, row; //starts at 0

		column = (x - BOARD_ORIGIN_X) / TILE_SIZE;
		row = (y - BOARD_ORIGIN_Y) / TILE_SIZE;

		return board[column][row];
	}

	bool testTilesAdjacent(Tile selectedTile, Tile clickedTile)
	{
		bool columnAdj = false, rowAdj = false;

		if (clickedTile.getColumn() >= selectedTile.getColumn() -1 && clickedTile.getColumn() <= selectedTile.getColumn() + 1)
			columnAdj = true;
		if (clickedTile.getRow() >= selectedTile.getRow() -1 && clickedTile.getRow() <= selectedTile.getRow() + 1)
			rowAdj = true;

		if (columnAdj && rowAdj)
			return true;
		return false;
	}

		void endTurn()
		{
			if (totalUnitsP1 <= 0) //player 1 lost
			{
				playerTurn = 1;
				newGame();
			}
			else if (totalUnitsP2 <= 0) //player 2 lost
			{
				playerTurn = 2;
				newGame();
			}
			else //normal turn change
			{
				moveAmount = 0;

				if (playerTurn == 1)
					playerTurn = 2;
				else
					playerTurn = 1;

				//add units to all controlled tiles
				if (turn % 2 == 0)
				{
					float growthRate;
					for (int i=0; i<board.size(); i++)
					{
						for (int j=0; j<board.size(); j++)
						{
							if (board[i][j].player != 0) //if player controlled
							{
								//growthRate = (board[i][j].units / (UNIT_START_SIZE * 10.f)) + 1;

								if (board[i][j].player == 1)
									totalUnitsP1 += 1; //(board[i][j].units * growthRate) - board[i][j].units;
								else
									totalUnitsP2 += 1; //(board[i][j].units * growthRate) - board[i][j].units;
								
								board[i][j].units += 1; //*= growthRate;
							}
						}
					}
				}
				turn++;
			}
		}

	void tileMove(Tile selectedTile, Tile clickedTile)
	{
		if (clickedTile.player == selectedTile.player)
			clickedTile.units += moveAmount;
		else
		{
			if (moveAmount > clickedTile.units)
			{
				totalUnitsP1 -= clickedTile.units;
				totalUnitsP2 -= clickedTile.units;

				clickedTile.units = moveAmount - clickedTile.units;
				clickedTile.player = selectedTile.player;
			}
			else if (moveAmount == clickedTile.units)
			{
				totalUnitsP1 -= moveAmount;
				totalUnitsP2 -= moveAmount;

				clickedTile.setToNeutral();
			}
			else
			{
				totalUnitsP1 -= moveAmount;
				totalUnitsP2 -= moveAmount;

				clickedTile.units -= moveAmount;
			}
		}

		selectedTile.units -= moveAmount;
		if (selectedTile.units <= 0)
		{
			selectedTile.setToNeutral();
		}

		board[selectedTile.getColumn()][selectedTile.getRow()] = selectedTile;
		board[clickedTile.getColumn()][clickedTile.getRow()] = clickedTile;
		tileSelected = false;

		endTurn();
	}

void mouseClick(float x, float y)
{
	if (testTileClicked(x, y)) //if tile clicked
	{
		Tile clickedTile = getClickedTile(x, y);

		if (!tileSelected) //select tile
		{
			if (clickedTile.player == playerTurn) //if a player
				tileSelected = true;
				selectedTile = clickedTile;
				//highlight clicked tile's border
		}
		else if (selectedTile.compare(clickedTile))
			tileSelected = false;
		else //move tile
			if (testTilesAdjacent(selectedTile, clickedTile) && moveAmount > 0 && moveAmount <= selectedTile.units)
				tileMove(selectedTile, clickedTile);
	}
}

	void addMoveAmount(int number)
	{
		moveAmount = moveAmount * 10 + number;
	}

void keyPress(sf::Event Event)
{
	switch (Event.Key.Code)
	{
		case sf::Key::Num1:
			addMoveAmount(1);
			break;

		case sf::Key::Num2:
			addMoveAmount(2);
			break;

		case sf::Key::Num3:
			addMoveAmount(3);
			break;
			
		case sf::Key::Num4:
			addMoveAmount(4);
			break;

		case sf::Key::Num5:
			addMoveAmount(5);
			break;
			
		case sf::Key::Num6:
			addMoveAmount(6);
			break;

		case sf::Key::Num7:
			addMoveAmount(7);
			break;

		case sf::Key::Num8:
			addMoveAmount(8);
			break;
			
		case sf::Key::Num9:
			addMoveAmount(9);
			break;

		case sf::Key::Num0:
			addMoveAmount(0);
			break;
			
		case sf::Key::Numpad1:
			addMoveAmount(1);
			break;

		case sf::Key::Numpad2:
			addMoveAmount(2);
			break;

		case sf::Key::Numpad3:
			addMoveAmount(3);
			break;
			
		case sf::Key::Numpad4:
			addMoveAmount(4);
			break;

		case sf::Key::Numpad5:
			addMoveAmount(5);
			break;
			
		case sf::Key::Numpad6:
			addMoveAmount(6);
			break;

		case sf::Key::Numpad7:
			addMoveAmount(7);
			break;

		case sf::Key::Numpad8:
			addMoveAmount(8);
			break;
			
		case sf::Key::Numpad9:
			addMoveAmount(9);
			break;

		case sf::Key::Numpad0:
			addMoveAmount(0);
			break;

		case sf::Key::Back:
			moveAmount = moveAmount / 10;
			break;
	}
}

void main()
{
	newGame(); //board initilization
	Canvas canvas(WIN_WIDTH, WIN_HEIGHT, BOARD_SIZE, BOARD_ORIGIN_X, BOARD_ORIGIN_Y, TILE_SIZE);

	//main loop
    while (mainWindow.IsOpened())
    {
        sf::Event Event;
        while (mainWindow.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                mainWindow.Close();
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				mainWindow.Close();
			if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.Button == sf::Mouse::Left))
				mouseClick(Event.MouseButton.X, Event.MouseButton.Y);
			if ((Event.Type == sf::Event::KeyPressed))
				keyPress(Event);
        }

        mainWindow.Clear(sf::Color::White);
		
		//draw scenes
		canvas.drawGame(mainWindow, board, moveAmount, totalUnitsP1, totalUnitsP2);
		if (tileSelected)
			canvas.highlightSelectedTile(mainWindow, selectedTile);

        mainWindow.Display();
    }
}