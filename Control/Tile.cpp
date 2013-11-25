#include "Tile.h"

Tile::Tile(void)
{
	player = 0;
	units = 0;
}

Tile::~Tile(void)
{
}

Tile::Tile(int player, int units, int column, int row)
{
	this->player = player;
	this->units = units;
	this->column = column;
	this->row = row;
}

void Tile::setToNeutral()
{
	player = 0;
	units = 0;
}

int Tile::getColumn()
{
	return column;
}

int Tile::getRow()
{
	return row;
}

bool Tile::compare(Tile otherTile)
{
	if (otherTile.getColumn() == column && otherTile.getRow() == row)
		return true;
	return false;
}