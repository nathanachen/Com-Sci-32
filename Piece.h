#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include <string>
#include <vector>
class Screen;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

class Piece
{
public:
	Piece(PieceType type);
	PieceType getType();
	int getOrientation();
	void incrementOrientation();
	std::string getRepresentation();
	void rotate(Screen& theScreen, std::vector<std::vector<char>>& theGrid);
	void vaporExplode(Screen& theScreen, std::vector<std::vector<char>>& theGrid);
	bool foamExplode(Screen& theScreen, std::vector<std::vector<char>>& theGrid, int xPos, int yPos, int xBoundLeft, int xBoundRight, int yBoundUp, int yBoundLow);
private:
	std::vector<std::string> repsOrientation0;
	PieceType m_type;
	int orientation;
	std::string representation;
};

PieceType chooseRandomPieceType();

#endif // PIECE_INCLUDED
