#include "Rat.h"
#include "Player.h"
#include "globals.h"
#include "Arena.h"
#include "Game.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 5, 2);
	Game g(10, 12, 40);

	// Play the game
	g.play();
}

/* #include "Game.h"
#include "Game.h"
#include "Arena.h"
#include "Arena.h"
#include "History.h"
#include "History.h"
#include "Player.h"
#include "Player.h"
#include "Rat.h"
#include "Rat.h"
#include "globals.h"
#include "globals.h"
int main()
{} */

/* #include "History.h"
int main()
{
	History h(2, 2);
	h.record(1, 1);
	h.display();
} */

/* #include "Rat.h"
int main()
{
	Rat r(nullptr, 1, 1);
} */

/* #include "Player.h"
int main()
{
	Player p(nullptr, 1, 1);
} */

/* #include "Arena.h"
int main()
{
	Arena a(10, 18);
	a.addPlayer(2, 2);
} */

/* #include "globals.h"
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
} */

/* #include "Arena.h"
#include "Player.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
} */

/* #include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
} */

/* #include "Arena.h"
#include "History.h"
#include "globals.h"
int main()
{
	Arena a(1, 4);
	a.addPlayer(1, 4);
	for (int t = 1; t <= 2; t++)
	{
		a.addRat(1, 1);
		a.setCellStatus(1, 2, HAS_POISON);
		a.setCellStatus(1, 3, HAS_POISON);
		while (a.ratCount() > 0)
			a.moveRats();
	}
	a.history().display();
} */

/* #include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
	Rat r(&a, 1, 1);
} */

/* #include "globals.h"
#include "Rat.h"
#include "Player.h"
int main()
{
	Arena a(10, 10);
} */

/* #include "History.h"
int main()
{
	History h;
} */