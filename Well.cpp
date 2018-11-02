#include "Well.h"
#include "UserInterface.h"
using namespace std;

void Well::display(Screen& screen, int x, int y)
{
	// Represent left wall of the well with '@' characters
	// (0,0) to (0, 18)
	for (int i = 0; i < 19; i++)
	{
		screen.gotoXY(0, i);
		screen.printChar('@');
	}
	// Represent bottom of well with '@' characters
	// (1,18) to (10, 18)
	for (int j = 1; j < 11; j++)
	{
		screen.gotoXY(j, 18);
		screen.printChar('@');
	}
	// Represent right wall of the well with '@' characters
	// (11,0) to (11,18)
	for (int k = 0; k < 19; k++)
	{
		screen.gotoXY(11, k);
		screen.printChar('@');
	}
	screen.refresh();
}
