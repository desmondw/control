#ifndef _CANVAS_H
#define _CANVAS_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <sstream>
#include "Tile.h"

using namespace std;

class Canvas
{
	private:
		int WIN_WIDTH, WIN_HEIGHT;
		int BOARD_SIZE;
		int BOARD_ORIGIN_X, BOARD_ORIGIN_Y;
		int TILE_SIZE;
		
		void drawBoard(sf::RenderWindow& mainWindow, vector<vector<Tile>> board);
		void drawGrid(sf::RenderWindow& mainWindow);
		void drawUnits(sf::RenderWindow& mainWindow, vector<vector<Tile>> board);
	public:
		Canvas(void);
		~Canvas(void);
		Canvas(int winWidth, int winHeight, int boardSize, int boardOriginX, int boardOriginY, int tileSize);
		void drawGame(sf::RenderWindow& mainWindow, vector<vector<Tile>>& board, int moveAmount, int totalUnitsP1, int totalUnitsP2);
		void drawInformation(sf::RenderWindow& mainWindow, int moveAmount, int totalUnitsP1, int totalUnitsP2);
		void highlightSelectedTile(sf::RenderWindow& mainWindow, Tile selectedTile);
};

#endif