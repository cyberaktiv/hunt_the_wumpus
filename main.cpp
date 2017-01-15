#include "lib/Graph_lib/Window.cpp"
#include "lib/Graph_lib/Graph.cpp"
#include "lib/Graph_lib/GUI.cpp"
#include <time.h>
#include <windows.h>
#include <FL/fl_ask.H>

using namespace Graph_lib;
//------------------------------------------------------------------------------
int main();

#include "src/Logic_game.h"
#include "src/Graph_game.h"
#include "src/Wind_game.h"
//------------------------------------------------------------------------------
int main()
try{
	Wind win(Point(200, 200), 740, 375, "Hunt the Wumpus");
	Fl::run();
}
catch (runtime_error& e)
{
	Point tl(300, 200);
	Graph_lib::Window win(tl,400,100,"Error");
	Text t(Point(15, 50), e.what());
	t.set_color(Color::red);
	t.set_font_size(20);
	t.set_font(Font::times_bold);
	win.attach(t);
	Fl::run();
	return 1;
}
catch (...)
{
	cerr << "Oops: unknown exception!\n";
	return 2;
}
