#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <vector>
#include "Piece.h"
using namespace std;
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();

    // [Add other members as necessary.]

  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
	vector<vector<char>> grid;
	int rowsFilled;
	int levelScore;
	int totScore;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
