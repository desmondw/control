#ifndef _TILE_H
#define _TILE_H

using namespace std;

class Tile
{
	private:
		int column;
		int row;
	public:
		int player;
		int units;

		Tile(void);
		~Tile(void);
		Tile(int player, int units, int column, int row);
		void setToNeutral();
		int getRow();
		int getColumn();
		bool compare(Tile otherTile);
};

#endif