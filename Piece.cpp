#include "Piece.h"
#include "UserInterface.h"
using namespace std;

Piece::Piece(PieceType type)
{
	m_type = type;
	orientation = 0;
	repsOrientation0 = { "n####", "n###n#", "n ###n   #", " # n###", "##n##", "n ##n##", "n##n ##", " ##", "n #", "#  #n ##" };

	switch (type)
	{
	case PIECE_I:
		representation = repsOrientation0[0];
		break;
	case PIECE_L:
		representation = repsOrientation0[1];
		break;
	case PIECE_J:
		representation = repsOrientation0[2];
		break;
	case PIECE_T:
		representation = repsOrientation0[3];
		break;
	case PIECE_O:
		representation = repsOrientation0[4];
		break;
	case PIECE_S:
		representation = repsOrientation0[5];
		break;
	case PIECE_Z:
		representation = repsOrientation0[6];
		break;
	case PIECE_VAPOR:
		representation = repsOrientation0[7];
		break;
	case PIECE_FOAM:
		representation = repsOrientation0[8];
		break;
	case PIECE_CRAZY:
		representation = repsOrientation0[9];
		break;
	}
}

PieceType Piece::getType()
{
	return m_type;
}

int Piece::getOrientation()
{
	return orientation;
}

std::string Piece::getRepresentation()
{
	return representation;
}

void Piece::incrementOrientation()
{
	if (orientation == 3)
	{
		orientation = 0;
	}
	else
	{
		orientation++;
	}
}

void Piece::rotate(Screen& theScreen, std::vector<std::vector<char>>& theGrid)
{
	bool pieceFound = false;
	bool canRotate = true;
	int xFoundPos = 0;
	int yFoundPos = 0;

	// find the position of the right-most, bottom-most '#' block of the piece
	for (int j = 17; j >= 0; j--)
	{
		for (int i = 10; i >= 1; i--)
		{
			if (theGrid[i][j] == '#')
			{
				xFoundPos = i;
				yFoundPos = j;
				pieceFound = true;
				break;
			}
		}
		if (pieceFound)
		{
			break;
		}
	}

	// check the orientation
	switch (orientation)
	{
	case 0:
		// check the piece type
		switch (m_type)
		{
		case PIECE_I:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0 || (xFoundPos - 2) >= 11 || (yFoundPos + 2) >= 18 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 2][yFoundPos - 1] != ' ' || 
				theGrid[xFoundPos - 2][yFoundPos + 1] != ' ' ||
				theGrid[xFoundPos - 2][yFoundPos + 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				theGrid[xFoundPos - 3][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 2][yFoundPos - 1] = '#';
				theGrid[xFoundPos - 2][yFoundPos + 1] = '#';
				theGrid[xFoundPos - 2][yFoundPos + 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_L:
			// check if you can legally rotate the piece
			if ((xFoundPos + 2) >= 11 || (yFoundPos - 2) <= -1 || (xFoundPos + 1) <= 0 || (yFoundPos) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos + 1][yFoundPos - 2] != ' ' ||
				theGrid[xFoundPos + 2][yFoundPos - 2] != ' ' ||
				theGrid[xFoundPos + 2][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos][yFoundPos - 1] = ' ';
				theGrid[xFoundPos + 1][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos + 1][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 2][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 2][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_J:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0 || (xFoundPos - 1) >= 11 || (yFoundPos + 1) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos + 1] != ' ' ||
					theGrid[xFoundPos - 2][yFoundPos + 1] != ' ' ||
					theGrid[xFoundPos - 1][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos][yFoundPos - 1] = ' ';
				theGrid[xFoundPos - 2][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos + 1] = '#';
				theGrid[xFoundPos - 2][yFoundPos + 1] = '#';
				theGrid[xFoundPos - 1][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_T:
			// check if you can legally rotate the piece
			if ((xFoundPos - 1) <= 0 || (yFoundPos + 1) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos + 1] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos - 2][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos + 1] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_O:
			break;
		case PIECE_S:
			// check if you can legally rotate the piece
			if ((yFoundPos - 2) <= -1 || (xFoundPos + 1) >= 11)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos + 1][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 1][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_Z:
			// check if you can legally rotate the piece
			if ((yFoundPos - 2) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 2][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos][yFoundPos - 1] = '#';
				theGrid[xFoundPos][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_VAPOR:
			break;
		case PIECE_FOAM:
			break;
		case PIECE_CRAZY:
			// check if you can legally rotate the piece
			if ((yFoundPos + 2) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos][yFoundPos + 1] != ' ' ||
					 theGrid[xFoundPos + 1][yFoundPos + 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				theGrid[xFoundPos - 2][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos][yFoundPos + 1] = '#';
				theGrid[xFoundPos + 1][yFoundPos + 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		}
		break;
	case 1:
		// check the piece type
		switch (m_type)
		{
		case PIECE_I:
			// check if you can legally rotate the piece
			if ((xFoundPos - 1) <= 0 || (xFoundPos + 2) >= 11 || (yFoundPos - 2) <= -1 || (yFoundPos - 2) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos + 1][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos + 2][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos][yFoundPos - 1] = ' ';
				theGrid[xFoundPos][yFoundPos - 3] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 1][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 2][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_L:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0 || (xFoundPos - 1) >= 11)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos] != ' ' ||
					 theGrid[xFoundPos - 2][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos - 2] = ' ';
				theGrid[xFoundPos - 1][yFoundPos - 2] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos] = '#';
				theGrid[xFoundPos - 2][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_J:
			// check if you can legally rotate the piece
			if ((xFoundPos - 1) <= 0 || (xFoundPos + 1) >= 11 || (yFoundPos - 2) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos + 1][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos - 1][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				theGrid[xFoundPos][yFoundPos - 2] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos - 1] = '#';
				theGrid[xFoundPos + 1][yFoundPos - 1] = '#';
				theGrid[xFoundPos - 1][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_T:
			// check if you can legally rotate the piece
			if ((xFoundPos - 1) <= 0 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos - 1] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos - 2] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos - 1] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_O:
			break;
		case PIECE_S:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos] != ' ' ||
					 theGrid[xFoundPos - 2][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos - 1][yFoundPos - 2] = ' ';
				theGrid[xFoundPos][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos] = '#';
				theGrid[xFoundPos - 2][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_Z:
			// check if you can legally rotate the piece
			if ((xFoundPos + 1) >= 11 || (xFoundPos - 1) <= 0 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos + 1][yFoundPos] != ' ' ||
					 theGrid[xFoundPos - 1][yFoundPos - 1] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos + 1][yFoundPos - 1] = ' ';
				theGrid[xFoundPos + 1][yFoundPos - 2] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos + 1][yFoundPos] = '#';
				theGrid[xFoundPos - 1][yFoundPos - 1] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_VAPOR:
			break;
		case PIECE_FOAM:
			break;
		case PIECE_CRAZY:
			// check if you can legally rotate the piece
			if ((xFoundPos - 3) <= 0 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 3][yFoundPos] != ' ' ||
					 theGrid[xFoundPos - 2][yFoundPos - 1] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos - 1][yFoundPos - 2] = ' ';
				theGrid[xFoundPos][yFoundPos - 3] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 3][yFoundPos] = '#';
				theGrid[xFoundPos - 2][yFoundPos - 1] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		}
		break;
	case 2:
		// check the piece type
		switch (m_type)
		{
		case PIECE_I:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0 || (xFoundPos - 2) >= 11 || (yFoundPos + 2) >= 18 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 2][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos - 2][yFoundPos + 1] != ' ' ||
					 theGrid[xFoundPos - 2][yFoundPos + 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				theGrid[xFoundPos - 3][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 2][yFoundPos - 1] = '#';
				theGrid[xFoundPos - 2][yFoundPos + 1] = '#';
				theGrid[xFoundPos - 2][yFoundPos + 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_L:
			// check if you can legally rotate the piece
			if (xFoundPos >= 11 || (xFoundPos - 1) <= 0 || (yFoundPos - 1) <= -1 || (yFoundPos + 1) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos][yFoundPos + 1] != ' ' ||
					 theGrid[xFoundPos - 1][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos - 1][yFoundPos + 1] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos][yFoundPos - 1] = ' ';
				theGrid[xFoundPos - 2][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos][yFoundPos + 1] = '#';
				theGrid[xFoundPos - 1][yFoundPos - 1] = '#';
				theGrid[xFoundPos - 1][yFoundPos + 1] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_J:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0 || (yFoundPos - 2) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 2][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos - 1][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 2][yFoundPos - 2] = '#';
				theGrid[xFoundPos - 1][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_T:
			// check if you can legally rotate the piece
			if ((yFoundPos - 2) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos + 1][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_O:
			break;
		case PIECE_S:
			// check if you can legally rotate the piece
			if ((yFoundPos - 2) <= -1 || (xFoundPos + 1) >= 11)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos + 1][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 1][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_Z:
			// check if you can legally rotate the piece
			if ((yFoundPos - 2) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos][yFoundPos - 1] != ' ' ||
				theGrid[xFoundPos][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 2][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos][yFoundPos - 1] = '#';
				theGrid[xFoundPos][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_VAPOR:
			break;
		case PIECE_FOAM:
			break;
		case PIECE_CRAZY:
			// check if you can legally rotate the piece
			if ((xFoundPos - 3) <= 0 || (yFoundPos - 3) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 2][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos - 3][yFoundPos - 3] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 2][yFoundPos - 2] = '#';
				theGrid[xFoundPos - 3][yFoundPos - 3] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		}
		break;
	case 3:
		// check the piece type
		switch (m_type)
		{
		case PIECE_I:
			// check if you can legally rotate the piece
			if ((xFoundPos - 1) <= 0 || (xFoundPos + 2) >= 11 || (yFoundPos - 2) <= -1 || (yFoundPos - 2) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos + 1][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos + 2][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos][yFoundPos - 1] = ' ';
				theGrid[xFoundPos][yFoundPos - 3] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 1][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 2][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_L:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0 || (yFoundPos - 2) <= -1 || (yFoundPos - 1) >= 18)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 2][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos - 2][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos][yFoundPos - 2] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos - 1] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 2][yFoundPos - 1] = '#';
				theGrid[xFoundPos - 2][yFoundPos - 2] = '#';
				theGrid[xFoundPos][yFoundPos - 2] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_J:
			// check if you can legally rotate the piece
			if ((xFoundPos + 2) >= 11 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos + 1][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos + 2][yFoundPos - 1] != ' ' ||
					 theGrid[xFoundPos + 2][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos][yFoundPos - 2] = ' ';
				theGrid[xFoundPos + 1][yFoundPos - 2] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos + 1][yFoundPos - 1] = '#';
				theGrid[xFoundPos + 2][yFoundPos - 1] = '#';
				theGrid[xFoundPos + 2][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_T:
			// check if you can legally rotate the piece
			if ((xFoundPos + 1) >= 11 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos + 1][yFoundPos - 1] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos + 1][yFoundPos - 1] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_O:
			break;
		case PIECE_S:
			// check if you can legally rotate the piece
			if ((xFoundPos - 2) <= 0)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos - 1][yFoundPos] != ' ' ||
					 theGrid[xFoundPos - 2][yFoundPos] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos][yFoundPos] = ' ';
				theGrid[xFoundPos - 1][yFoundPos - 2] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos - 1][yFoundPos] = '#';
				theGrid[xFoundPos - 2][yFoundPos] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_Z:
			// check if you can legally rotate the piece
			if ((xFoundPos + 1) >= 11 || (xFoundPos - 1) <= 0 || (yFoundPos - 1) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos + 1][yFoundPos] != ' ' ||
				theGrid[xFoundPos - 1][yFoundPos - 1] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos + 1][yFoundPos - 1] = ' ';
				theGrid[xFoundPos + 1][yFoundPos - 2] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos + 1][yFoundPos] = '#';
				theGrid[xFoundPos - 1][yFoundPos - 1] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		case PIECE_VAPOR:
			break;
		case PIECE_FOAM:
			break;
		case PIECE_CRAZY:
			// check if you can legally rotate the piece
			if ((xFoundPos + 3) >= 11 || (yFoundPos - 3) <= -1)
			{
				canRotate = false;
			}
			else if (theGrid[xFoundPos + 2][yFoundPos - 2] != ' ' ||
					 theGrid[xFoundPos + 3][yFoundPos - 3] != ' ')
			{
				canRotate = false;
			}
			// if you can rotate the piece, go ahead and do it
			if (canRotate)
			{
				// change the stored orientation value of the piece
				incrementOrientation();
				// clear the grid of the piece
				theGrid[xFoundPos + 1][yFoundPos - 1] = ' ';
				theGrid[xFoundPos][yFoundPos] = ' ';
				// replace the piece on the grid with the new orientation
				theGrid[xFoundPos + 2][yFoundPos - 2] = '#';
				theGrid[xFoundPos + 3][yFoundPos - 3] = '#';
				// refresh position of piece on the screen
				for (int i = 1; i < 11; i++)
				{
					for (int j = 0; j < 18; j++)
					{
						theScreen.gotoXY(i, j);
						theScreen.printChar(theGrid[i][j]);
					}
				}
				theScreen.refresh();
			}
			break;
		}
		break;
	}
}

void Piece::vaporExplode(Screen& theScreen, std::vector<std::vector<char>>& theGrid)
{
	int vaporX1;
	int vaporX2;
	int vaporY;
	// find the coordinates of the foam bomb
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j <= 17; j++)
		{
			if (theGrid[i][j] == '#')
			{
				vaporX1 = i;
				vaporX2 = i + 1;
				vaporY = j;
				break;
			}
		}
	}
	
	int yBound1;
	int yBound2;
	// determine top y-coordinate bound of the explosion
	if ((vaporY - 2) <= -1)
	{
		if ((vaporY - 1) <= -1)
		{
			yBound1 = vaporY;
		}
		else
		{
			yBound1 = vaporY - 1;
		}
	}
	else
	{
		yBound1 = vaporY - 2;
	}
	// determine bottom y-coordinate bound of the explosion
	if ((vaporY + 2) >= 18)
	{
		if ((vaporY + 1) >= 18)
		{
			yBound2 = vaporY;
		}
		else
		{
			yBound2 = vaporY + 1;
		}
	}
	else
	{
		yBound2 = vaporY + 2;
	}

	// remove items from the grid
	for (int i = vaporX1 - 1; i <= vaporX2 - 1; i++)
	{
		for (int j = yBound1; j <= yBound2; j++)
		{
			theGrid[i][j] = ' ';
		}
	}

	// refresh position of piece on the screen
	for (int i = 1; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			theScreen.gotoXY(i, j);
			theScreen.printChar(theGrid[i][j]);
		}
	}
	theScreen.refresh();
}

bool Piece::foamExplode(Screen& theScreen, std::vector<std::vector<char>>& theGrid, int xPos, int yPos, int xBoundLeft, int xBoundRight, int yBoundUp, int yBoundLow)
{
	theGrid[xPos][yPos] = '*';
	// check if the left is open
	// if so, mark it with a '*'
	if (xPos - 1 >= xBoundLeft)
	{
		if (theGrid[xPos - 1][yPos] == ' ')
		{
			if (foamExplode(theScreen, theGrid, xPos - 1, yPos, xBoundLeft, xBoundRight, yBoundUp, yBoundLow))
			{
				return true;
			}
		}
	}
	// check if the upper is open
	// if so, mark it with a '*'
	if (yPos - 1 >= yBoundUp)
	{
		if (theGrid[xPos][yPos - 1] == ' ')
		{
			if (foamExplode(theScreen, theGrid, xPos, yPos - 1, xBoundLeft, xBoundRight, yBoundUp, yBoundLow))
			{
				return true;
			}
		}
	}
	// check if the right is open
	// if so, mark it with a '*'
	if (xPos + 1 <= xBoundRight)
	{
		if (theGrid[xPos + 1][yPos] == ' ')
		{
			if (foamExplode(theScreen, theGrid, xPos + 1, yPos, xBoundLeft, xBoundRight, yBoundUp, yBoundLow))
			{
				return true;
			}
		}
	}
	// check if the bottom is open
	// if so, mark it with a '*'
	if (yPos + 1 <= yBoundLow)
	{
		if (theGrid[xPos][yPos + 1] == ' ')
		{
			if (foamExplode(theScreen, theGrid, xPos, yPos + 1, xBoundLeft, xBoundRight, yBoundUp, yBoundLow))
			{
				return true;
			}
		}
	}
	return false;
}