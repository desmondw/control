#include "Canvas.h"

Canvas::Canvas(void)
{
}

Canvas::~Canvas(void)
{
}

Canvas::Canvas(int winWidth, int winHeight, int boardSize, int boardOriginX, int boardOriginY, int tileSize)
{
	WIN_WIDTH = winWidth;
	WIN_HEIGHT = winHeight;
	BOARD_SIZE = boardSize;
	BOARD_ORIGIN_X = boardOriginX;
	BOARD_ORIGIN_Y = boardOriginY;
	TILE_SIZE = tileSize;
}

void Canvas::drawGame(sf::RenderWindow& mainWindow, vector<vector<Tile>>& board, int moveAmount, int totalUnitsP1, int totalUnitsP2)
{
	drawBoard(mainWindow, board);
	drawGrid(mainWindow);
	drawUnits(mainWindow, board);
	drawInformation(mainWindow, moveAmount, totalUnitsP1, totalUnitsP2);
}

void Canvas::drawBoard(sf::RenderWindow& mainWindow, vector<vector<Tile>> board)
{
	int xPos, yPos;

	for (int i=0; i<board.size(); i++)
	{
		for (int j=0; j<board.size(); j++)
		{
			sf::Color color;

			if (board[i][j].player == 1)
				color = sf::Color::Red;
			else if (board[i][j].player == 2)
				color = sf::Color::Blue;
			else
				color = sf::Color::Color(127, 127, 127, 255); //Gray

			xPos = i * TILE_SIZE + BOARD_ORIGIN_X;
			yPos = j * TILE_SIZE + BOARD_ORIGIN_Y;
			mainWindow.Draw(sf::Shape::Rectangle(xPos, yPos, xPos+TILE_SIZE, yPos+TILE_SIZE, color));
		}
	}
}

void Canvas::drawGrid(sf::RenderWindow& mainWindow)
{
	const int HALF_GRID_WIDTH = (TILE_SIZE * .05) / 2;
	int xPos, yPos;

	for (int i=0; i<BOARD_SIZE+1; i++)
	{
		xPos = i * TILE_SIZE + BOARD_ORIGIN_X;
		mainWindow.Draw(sf::Shape::Rectangle(xPos-HALF_GRID_WIDTH, BOARD_ORIGIN_Y-HALF_GRID_WIDTH, xPos+HALF_GRID_WIDTH, BOARD_ORIGIN_Y+TILE_SIZE*BOARD_SIZE+HALF_GRID_WIDTH, sf::Color::Black));
	}

	for (int j=0; j<BOARD_SIZE+1; j++)
	{
		yPos = j * TILE_SIZE + BOARD_ORIGIN_Y;
		mainWindow.Draw(sf::Shape::Rectangle(BOARD_ORIGIN_X-HALF_GRID_WIDTH, yPos-HALF_GRID_WIDTH, BOARD_ORIGIN_X+TILE_SIZE*BOARD_SIZE+HALF_GRID_WIDTH, yPos+HALF_GRID_WIDTH, sf::Color::Black));
	}
}

void Canvas::drawUnits(sf::RenderWindow& mainWindow, vector<vector<Tile>> board)
{
	const float FONT_SIZE = TILE_SIZE*.5;
	const float FONT_BORDER = TILE_SIZE*.2;

	sf::Font font;
	font.LoadFromFile("bin/arial.ttf", 30);
	sf::String units("", font, 30);
	ostringstream sstream;
	int xPos, yPos;

	for (int i=0; i<board.size(); i++)
	{
		for (int j=0; j<board.size(); j++)
		{
			sstream << board[i][j].units;
			units.SetText(sstream.str());
			sstream.str("");

			units.SetX(i * TILE_SIZE + BOARD_ORIGIN_X + TILE_SIZE/10);
			units.SetY(j * TILE_SIZE + BOARD_ORIGIN_Y + TILE_SIZE/10);
			units.SetColor(sf::Color::White);

			if (board[i][j].units > 0)
				mainWindow.Draw(units);
		}
	}
	sstream.end;
}

void Canvas::drawInformation(sf::RenderWindow& mainWindow, int moveAmount, int totalUnitsP1, int totalUnitsP2)
{
	sf::Font font;
	font.LoadFromFile("bin/arial.ttf", 30);
	sf::String units("", font, 30);
	ostringstream sstream;

	sstream << "Move amount: ";
	sstream << moveAmount;
	sstream << "\nPlayer 1: ";
	sstream << totalUnitsP1;
	sstream << "\nPlayer 2: ";
	sstream << totalUnitsP2;
	units.SetText(sstream.str());
	sstream.end;
	
	units.SetColor(sf::Color::Black);
	units.SetX(BOARD_ORIGIN_X + BOARD_SIZE * TILE_SIZE + TILE_SIZE * .25);
	units.SetY(BOARD_ORIGIN_X);
	mainWindow.Draw(units);
}

void Canvas::highlightSelectedTile(sf::RenderWindow& mainWindow, Tile selectedTile)
{
	const int HALF_GRID_WIDTH = (TILE_SIZE / 20) / 2;
	int xPos = selectedTile.getColumn() * TILE_SIZE + BOARD_ORIGIN_X;
	int yPos = selectedTile.getRow() * TILE_SIZE + BOARD_ORIGIN_Y;

	mainWindow.Draw(sf::Shape::Rectangle(xPos-HALF_GRID_WIDTH, yPos-HALF_GRID_WIDTH, xPos+HALF_GRID_WIDTH+TILE_SIZE, yPos+HALF_GRID_WIDTH, sf::Color::Green));
	mainWindow.Draw(sf::Shape::Rectangle(xPos-HALF_GRID_WIDTH, yPos-HALF_GRID_WIDTH, xPos+HALF_GRID_WIDTH, yPos+HALF_GRID_WIDTH+TILE_SIZE, sf::Color::Green));
	mainWindow.Draw(sf::Shape::Rectangle(xPos+TILE_SIZE-HALF_GRID_WIDTH-+TILE_SIZE, yPos+TILE_SIZE-HALF_GRID_WIDTH, xPos+TILE_SIZE+HALF_GRID_WIDTH, yPos+TILE_SIZE+HALF_GRID_WIDTH, sf::Color::Green));
	mainWindow.Draw(sf::Shape::Rectangle(xPos+TILE_SIZE-HALF_GRID_WIDTH, yPos+TILE_SIZE-HALF_GRID_WIDTH-+TILE_SIZE, xPos+TILE_SIZE+HALF_GRID_WIDTH, yPos+TILE_SIZE+HALF_GRID_WIDTH, sf::Color::Green));
}