#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>
#include "Piece.h"
#include <algorithm>
#include <stack>
#include <queue>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), grid(12, vector<char>(19, ' '))
{
	rowsFilled = 0;
	levelScore = 0;
	totScore = 0;
}

void Game::play()
{
	m_screen.clear();
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
		// clear grid
		for (int i = 1; i < 11; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				grid[i][j] = ' ';
			}
		}
		// refresh screen
		for (int i = 1; i < 11; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				m_screen.gotoXY(i, j);
				m_screen.printChar(grid[i][j]);
			}
		}
		m_screen.refresh();
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
	// display score
	// clear the status area
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	string stringScore = to_string(totScore);
	m_screen.printString("Score:     ");
	m_screen.gotoXY(SCORE_X + 18 - stringScore.length(), SCORE_Y);
	m_screen.printString(stringScore);

	// display rows left
	// clear the status area
	for (int i = ROWS_LEFT_X + 11; i < ROWS_LEFT_X + 18; i++)
	{
		m_screen.gotoXY(i, ROWS_LEFT_Y);
		m_screen.printChar(' ');
	}
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	int rowsLeft = (5 * m_level) - rowsFilled;
	string stringRowsLeft = to_string(rowsLeft);
	m_screen.printString("Rows left: ");
	m_screen.gotoXY(ROWS_LEFT_X + 18 - stringRowsLeft.length(), ROWS_LEFT_Y);
	m_screen.printStringClearLine(stringRowsLeft);

	// display level
	// clear the status area
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	string stringLevel = to_string(m_level);
	m_screen.printString("Level:     ");
	m_screen.gotoXY(LEVEL_X + 18 - stringLevel.length(), LEVEL_Y);
	m_screen.printStringClearLine(stringLevel);

	// display next piece title
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next piece:");

	m_screen.refresh();

}

bool Game::playOneLevel()
{
	displayStatus();
	// create a random queue of pieces for this level
	queue<Piece> pieceList;
	// string representation of the piece to drop down the well
	string gridPiece;

	// add two random pieces to the queue
	pieceList.push(Piece(chooseRandomPieceType()));
	pieceList.push(Piece(chooseRandomPieceType()));

	// repeat while you haven't moved onto the next level yet
	while (rowsFilled < 5 * m_level)
	{
		
		// pick/pop the first piece in the queue to drop down the well
		// and add another random piece to the end of the queue
		Piece currPiece = pieceList.front();
		Piece nextPiece = pieceList.back();
		pieceList.pop();
		pieceList.push(Piece(chooseRandomPieceType()));
		// choose the right string representation of the current piece
		// and assign it to gridPiece
		gridPiece = currPiece.getRepresentation();

		//display the next piece's string representation
		// but clear that area of the screen first
		for (int i = NEXT_PIECE_X; i < NEXT_PIECE_X + 4; i++)
		{
			for (int j = NEXT_PIECE_Y; j < NEXT_PIECE_Y + 4; j++)
			{
				m_screen.gotoXY(i, j);
				m_screen.printChar(' ');
			}
		}
		int xx = NEXT_PIECE_X;
		int yy = NEXT_PIECE_Y;
		for (size_t i = 0; i < (nextPiece.getRepresentation()).length(); i++)
		{
			if ((nextPiece.getRepresentation()).at(i) == '#')
			{
				m_screen.gotoXY(xx, yy);
				m_screen.printChar('#');
				xx++;
			}
			else if ((nextPiece.getRepresentation()).at(i) == ' ')
			{
				xx++;
			}
			else if ((nextPiece.getRepresentation()).at(i) == 'n')
			{
				yy++;
				xx = NEXT_PIECE_X;
			}
		}
		m_screen.refresh();

		// place the piece at the top of the well in the grid if possible
		// if not, return false and end game
		int yPos = 0;
		int xPos = 4;
		bool shouldEnd = false;
		for (size_t i = 0; i < gridPiece.length(); i++)
		{
			if (gridPiece.at(i) == '#')
			{
				if (grid[xPos][yPos] != ' ')
				{
					shouldEnd = true;
				}
				grid[xPos][yPos] = '#';
				xPos++;
			}
			else if (gridPiece.at(i) == ' ')
			{
				xPos++;				
			}
			else if (gridPiece.at(i) == 'n')
			{
				yPos++;
				xPos = 4;
			}
		}

		// calculate time alotted per tick
		double timeAlotted = 100;
		if (100 < 1000 - (100 * (m_level - 1)))
		{
			timeAlotted = 1000 - (100 * (m_level - 1));
		}

		// start the timer
		Timer t;

		bool movable = true;
		bool dropped = false;
		bool movedByPlayer = false;
		char ch;
		// keep dropping/moving the piece down while it's movable.
		while (movable)
		{
			// drop the piece down by one unit if it hasn't already dropped during this tick
			if (t.elapsed() <= timeAlotted)
			{
				bool pieceMovableRight = true;
				bool pieceMovableLeft = true;
				// player controls defined here
				if (getCharIfAny(ch))
				{
					int x = 0;
					int y = 0;
					// There was a character typed; it's now in ch
					switch (ch)
					{
						// quit game if player presses 'q' or 'Q'
					case 'q':
					case 'Q':
						return false;
						break;
					//drop piece to bottom if player presses spacebar
					case ' ':
						while(movable)
						{
							// make sure all parts of the piece have nothing obstructing it below
							// if so, the piece is movable
							for (int j = 17; j >= 0; j--)
							{
								for (int i = 10; i >= 1; i--)
								{
									if (grid[i][j] == '#' && ((grid[i][j + 1] != ' ' && grid[i][j + 1] != '#') || j == 17))
									{
										movable = false;
										break;
									}
								}
								if (!movable)
								{
									break;
								}
							}
							// drop piece one unit lower on grid if it's movable.
							if (movable)
							{
								dropped = true;
								for (int i = 10; i >= 1; i--)
								{
									for (int j = 17; j >= 0; j--)
									{
										if (grid[i][j] == '#')
										{
											grid[i][j] = ' '; // erase current block from grid
											grid[i][j + 1] = '#'; // place the block one unit lower on grid
										}
									}
								}
							}
						}
						// refresh position of piece on the screen
						for (int i = 1; i < 11; i++)
						{
							for (int j = 0; j < 18; j++)
							{
								m_screen.gotoXY(i, j);
								m_screen.printChar(grid[i][j]);
							}
						}
						m_screen.refresh();
						break;
					// move piece one unit to the left if the left arrow key, 'a', or '4' are pressed
					case ARROW_LEFT:
						// if the piece is a crazyshape, execute the lines for ARROW_RIGHT
						if (currPiece.getType() == PIECE_CRAZY)
						{
							// make sure all parts of the piece have nothing obstructing it to the right
							// if so, the piece is movable
							for (int j = 17; j >= 0; j--)
							{
								for (int i = 10; i >= 1; i--)
								{
									if (grid[i][j] == '#' && ((grid[i + 1][j] != ' ' && grid[i + 1][j] != '#') || i == 10))
									{
										pieceMovableRight = false;
										break;
									}
								}
								if (!pieceMovableRight)
								{
									break;
								}
							}
							//move piece one unit to the right if it's movable
							if (pieceMovableRight)
							{
								for (int j = 17; j >= 0; j--)
								{
									for (int i = 10; i >= 1; i--)
									{
										if (grid[i][j] == '#')
										{
											grid[i][j] = ' ';
											grid[i + 1][j] = '#';
										}
									}
								}
							}
							// refresh position of piece on the screen
							for (int i = 1; i < 11; i++)
							{
								for (int j = 0; j < 18; j++)
								{
									m_screen.gotoXY(i, j);
									m_screen.printChar(grid[i][j]);
								}
							}
							m_screen.refresh();
							pieceMovableRight = true;
						}
						else
						{
							// make sure all parts of the piece have nothing obstructing it to the left
							// if so, the piece is movable
							for (int j = 17; j >= 0; j--)
							{
								for (int i = 10; i >= 1; i--)
								{
									if (grid[i][j] == '#' && ((grid[i - 1][j] != ' ' && grid[i - 1][j] != '#') || i == 1))
									{
										pieceMovableLeft = false;
										break;
									}
								}
								if (!pieceMovableLeft)
								{
									break;
								}
							}
							//move piece one unit to the left if it's movable
							if (pieceMovableLeft)
							{
								for (int j = 17; j >= 0; j--)
								{
									for (int i = 1; i <= 10; i++)
									{
										if (grid[i][j] == '#')
										{
											grid[i][j] = ' ';
											grid[i - 1][j] = '#';
										}
									}
								}
							}
							// refresh position of piece on the screen
							for (int i = 1; i < 11; i++)
							{
								for (int j = 0; j < 18; j++)
								{
									m_screen.gotoXY(i, j);
									m_screen.printChar(grid[i][j]);
								}
							}
							m_screen.refresh();
							pieceMovableLeft = true;
						}
						break;
					// move piece one unit to the right if the right arrow key, 'd', or '6' are pressed
					case ARROW_RIGHT:
						// if the piece is a crazyshape, execute the lines for ARROW_LEFT
						if (currPiece.getType() == PIECE_CRAZY)
						{
							// make sure all parts of the piece have nothing obstructing it to the left
							// if so, the piece is movable
							for (int j = 17; j >= 0; j--)
							{
								for (int i = 10; i >= 1; i--)
								{
									if (grid[i][j] == '#' && ((grid[i - 1][j] != ' ' && grid[i - 1][j] != '#') || i == 1))
									{
										pieceMovableLeft = false;
										break;
									}
								}
								if (!pieceMovableLeft)
								{
									break;
								}
							}
							//move piece one unit to the left if it's movable
							if (pieceMovableLeft)
							{
								for (int j = 17; j >= 0; j--)
								{
									for (int i = 1; i <= 10; i++)
									{
										if (grid[i][j] == '#')
										{
											grid[i][j] = ' ';
											grid[i - 1][j] = '#';
										}
									}
								}
							}
							// refresh position of piece on the screen
							for (int i = 1; i < 11; i++)
							{
								for (int j = 0; j < 18; j++)
								{
									m_screen.gotoXY(i, j);
									m_screen.printChar(grid[i][j]);
								}
							}
							m_screen.refresh();
							pieceMovableLeft = true;
						}
						else
						{
							// make sure all parts of the piece have nothing obstructing it to the right
							// if so, the piece is movable
							for (int j = 17; j >= 0; j--)
							{
								for (int i = 10; i >= 1; i--)
								{
									if (grid[i][j] == '#' && ((grid[i + 1][j] != ' ' && grid[i + 1][j] != '#') || i == 10))
									{
										pieceMovableRight = false;
										break;
									}
								}
								if (!pieceMovableRight)
								{
									break;
								}
							}
							//move piece one unit to the right if it's movable
							if (pieceMovableRight)
							{
								for (int j = 17; j >= 0; j--)
								{
									for (int i = 10; i >= 1; i--)
									{
										if (grid[i][j] == '#')
										{
											grid[i][j] = ' ';
											grid[i + 1][j] = '#';
										}
									}
								}
							}
							// refresh position of piece on the screen
							for (int i = 1; i < 11; i++)
							{
								for (int j = 0; j < 18; j++)
								{
									m_screen.gotoXY(i, j);
									m_screen.printChar(grid[i][j]);
								}
							}
							m_screen.refresh();
							pieceMovableRight = true;
						}
						break;
					// rotate the piece
					case ARROW_UP:
						currPiece.rotate(m_screen, grid);
						break;
					// move the piece one unit down if the down arrow key, 's', or '2' are pressed
					case ARROW_DOWN:
						// make sure all parts of the piece have nothing obstructing it below
						// if so, the piece is movable
						for (int j = 17; j >= 0; j--)
						{
							for (int i = 10; i >= 1; i--)
							{
								if (grid[i][j] == '#' && ((grid[i][j + 1] != ' ' && grid[i][j + 1] != '#') || j == 17))
								{
									movable = false;
									break;
								}
							}
							if (!movable)
							{
								break;
							}
						}
						// drop piece one unit lower on grid if it's movable.
						if (movable)
						{
							dropped = true;
							for (int i = 10; i >= 1; i--)
							{
								for (int j = 17; j >= 0; j--)
								{
									if (grid[i][j] == '#')
									{
										grid[i][j] = ' '; // erase current block from grid
										grid[i][j + 1] = '#'; // place the block one unit lower on grid
									}
								}
							}
						}
						// refresh position of piece on the screen
						for (int i = 1; i < 11; i++)
						{
							for (int j = 0; j < 18; j++)
							{
								m_screen.gotoXY(i, j);
								m_screen.printChar(grid[i][j]);
							}
						}
						m_screen.refresh();
						t.start();
						dropped = true;
						break;
					}
				}
				if (!dropped)
				{
					// refresh position of piece on the screen
					for (int i = 1; i < 11; i++)
					{
						for (int j = 0; j < 18; j++)
						{
							m_screen.gotoXY(i, j);
							m_screen.printChar(grid[i][j]);
						}
					}
					m_screen.refresh();
					// end game after showing the piece on the screen if there is an overlap
					if (shouldEnd)
					{
						return false;
					}
					// make sure all parts of the piece have nothing obstructing it below
					// if so, the piece is movable
					for (int j = 17; j >= 0; j--)
					{
						for (int i = 10; i >= 1; i--)
						{
							if (grid[i][j] == '#' && ((grid[i][j + 1] != ' ' && grid[i][j + 1] != '#') || j == 17))
							{
								movable = false;
								break;
							}
						}
						if (!movable)
						{
							break;
						}
					}
					// drop piece one unit lower on grid if it's movable.
					if (movable)
					{
						dropped = true;
						for (int i = 10; i >= 1; i--)
						{
							for (int j = 17; j >= 0; j--)
							{
								if (grid[i][j] == '#')
								{
									grid[i][j] = ' '; // erase current block from grid
									grid[i][j + 1] = '#'; // place the block one unit lower on grid
								}
							}
						}
					}
				}
			}
			else
			{
				t.start();
				dropped = false;
			}
		}

		// if the foam bomb has come to rest, explode it.
		if (currPiece.getType() == PIECE_FOAM)
		{
			int xPos;
			int yPos;
			// find resting position of bomb and assign coordinates to xPos and yPos
			for (int i = 10; i >= 1; i--)
			{
				for (int j = 17; j >= 0; j--)
				{
					if (grid[i][j] == '#')
					{
						xPos = i;
						yPos = j;
					}
				}
			}
			int xBound1, xBound2, yBound1, yBound2;
			// determine left bound of foam explosion
			if ((xPos - 2) <= 0)
			{
				if ((xPos - 1) <= 0)
				{
					xBound1 = xPos;
				}
				else
				{
					xBound1 = xPos - 1;
				}
			}
			else
			{
				xBound1 = xPos - 2;
			}
			// determine right bound of foam explosion
			if ((xPos + 2) >= 11)
			{
				if ((xPos + 1) >= 11)
				{
					xBound2 = xPos;
				}
				else
				{
					xBound2 = xPos + 1;
				}
			}
			else
			{
				xBound2 = xPos + 2;
			}
			// determine upper bound of foam explosion
			if ((yPos - 2) <= -1)
			{
				if ((yPos - 1) <= -1)
				{
					yBound1 = yPos;
				}
				else
				{
					yBound1 = yPos - 1;
				}
			}
			else
			{
				yBound1 = yPos - 2;
			}
			// determine lower bound of foam explosion
			if ((yPos + 2) >= 18)
			{
				if ((yPos + 1) >= 18)
				{
					yBound2 = yPos;
				}
				else
				{
					yBound2 = yPos + 1;
				}
			}
			else
			{
				yBound2 = yPos + 2;
			}
			currPiece.foamExplode(m_screen, grid, xPos, yPos, xBound1, xBound2, yBound1, yBound2);
		}

		// if the vapor bomb has come to rest, explode it.
		if (currPiece.getType() == PIECE_VAPOR)
		{
			currPiece.vaporExplode(m_screen, grid);
		}

				/*
				// return false if there are any blocks at the top row
				for (int i = 1; i < 11; i++)
				{
					if (grid[i][0] == '$' || grid[i][0] == '*')
					{
						// refresh screen
						for (int i = 1; i < 11; i++)
						{
							for (int j = 0; j < 18; j++)
							{
								m_screen.gotoXY(i, j);
								m_screen.printChar(grid[i][j]);
								m_screen.refresh();
							}
						}
						return false;
					}
				}*/

		// change the dropped block to be made out of '$'
		for (int i = 1; i < 11; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				if (grid[i][j] == '#')
				{
					grid[i][j] = '$';
				}
			}
		}

		//check for filled rows and store the y-coordinates of filled rows
		bool filled = false;
		stack<int> yCoordFilled;
		for (int j = 0; j < 18; j++)
		{
			if (grid[1][j] == '$' || grid[1][j] == '*')
			{
				filled = true;
				for (int i = 2; i < 11; i++)
				{
					if (grid[i][j] != '$' && grid[i][j] != '*')
					{
						filled = false;
						break;
					}
				}
				if (filled)
				{
					yCoordFilled.push(j);
					rowsFilled++;
				}
			}
		}
		switch (yCoordFilled.size())
		{
		case 1:
			totScore += 100;
			break;
		case 2:
			totScore += 200;
			break;
		case 3:
			totScore += 400;
			break;
		case 4:
			totScore += 800;
			break;
		case 5:
			totScore += 1600;
			break;
		}
		displayStatus();

		int numDisplaced = yCoordFilled.size();
		int bottomDisplacedCoord = -1;
		if (yCoordFilled.size() != 0)
		{
			bottomDisplacedCoord = yCoordFilled.top();
		}
		while (!yCoordFilled.empty())
		{
			// remove filled row from grid
			for (int i = 1; i <= 10; i++)
			{
				grid[i][yCoordFilled.top()] = ' ';
			}
			// remove filled row coordinate from stack
			yCoordFilled.pop();
		}
		// move everything above the filled rows down
		for (int i = bottomDisplacedCoord; i >= numDisplaced; i--)
		{
			for (int j = 10; j >= 1; j--)
			{
				grid[j][i] = grid[j][i - numDisplaced];
			}
		}
		for (int y = 0; y < numDisplaced; y++)
		{
			for (int x = 1; x <= 10; x++)
			{
				grid[x][y] = ' ';
			}
		}
		// refresh screen
		for (int i = 1; i < 11; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				m_screen.gotoXY(i, j);
				m_screen.printChar(grid[i][j]);
			}
		}

	}
	rowsFilled = 0;
	return true;
	// [Replace this with the code to play a level.]
}
