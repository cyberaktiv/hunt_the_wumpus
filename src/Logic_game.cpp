//BEGIN Cave
//-----------------------------------------------------------------------------
Cave::Cave() 
	: wmp(0), bt(0), pt(0), plr(0), cnt_d(3) 
{
	build();
	locate_all();
	print_all(); // for debug	
}
//-----------------------------------------------------------------------------
void Cave::locate_all()
{
	srand(time(0));
	wmp = rand()%20;
	while(bt == 0 || bt == wmp)
		bt = rand()%20;
	while(pt == 0 || pt == bt || pt == wmp)
		pt = rand()%20;
	while(plr == 0 || plr == bt || plr == pt || plr == wmp)
		plr = rand()%20;
}
//-----------------------------------------------------------------------------
void Cave::build()
{
	rooms.push_back(Room(1, 2, 6, 16));
	rooms.push_back(Room(2, 3, 7, 1));
	rooms.push_back(Room(3, 2, 4, 8));
	rooms.push_back(Room(4, 3, 5, 9));
	rooms.push_back(Room(5, 4, 10, 20));
	rooms.push_back(Room(6, 1, 7, 11));
	rooms.push_back(Room(7, 2, 6, 8));
	rooms.push_back(Room(8, 3, 7, 9));
	rooms.push_back(Room(9, 4, 8, 10));
	rooms.push_back(Room(10, 5, 9, 15));
	rooms.push_back(Room(11, 6, 12, 16));
	rooms.push_back(Room(12, 11, 13, 17));
	rooms.push_back(Room(13, 12, 14, 18));
	rooms.push_back(Room(14, 13, 15, 19));
	rooms.push_back(Room(15, 10, 14, 20));
	rooms.push_back(Room(16, 1, 11, 17));
	rooms.push_back(Room(17, 12, 16, 18));
	rooms.push_back(Room(18, 13, 17, 19));
	rooms.push_back(Room(19, 14, 18, 20));
	rooms.push_back(Room(20, 5, 15, 19));
}
//----------------------------------------------------------------------------
void Cave::print_all()
{
	system("cls"); // clear console
	cout
		<< "----------------------\n"
		<< "  player == " << rooms[plr].number() << "\n"
		<< "  pit == " << rooms[pt].number() << "\n"
		<< "  bat == " << rooms[bt].number() << "\n"
		<< "  wump == " << rooms[wmp].number() << "\n"
		<< "----------------------\n";
}
//----------------------------------------------------------------------------
vector<string> Cave::feel_near() // all feelings put in vector
{
	vector<string> vs;
	if(rooms[plr].tunnel_1() == rooms[wmp].number() ||
		rooms[plr].tunnel_2() == rooms[wmp].number() ||
		rooms[plr].tunnel_3() == rooms[wmp].number())
		vs.push_back("I smell the wumpus");
	
	if(rooms[plr].tunnel_1() == rooms[bt].number() ||
		rooms[plr].tunnel_2() == rooms[bt].number() ||
		rooms[plr].tunnel_3() == rooms[bt].number())
		vs.push_back("I hear a bat");
	
	if(rooms[plr].tunnel_1() == rooms[pt].number() ||
		rooms[plr].tunnel_2() == rooms[pt].number() ||
		rooms[plr].tunnel_3() == rooms[pt].number())
		vs.push_back("I feel a breeze");

	return vs;
}
//----------------------------------------------------------------------------
void Cave::move_wump()
{	
	// if Wumpus comes into the room with the pit or bat, 
	// then he goes into the next random room
	do
	{
		int r = rand() % 3;
		int wm = wmp;
		if (r == 0) wmp = rooms[wm].tunnel_1()-1;
		if (r == 1)	wmp = rooms[wm].tunnel_2()-1;
		if (r == 2) wmp = rooms[wm].tunnel_3()-1;	
	}
	while (wmp == bt || wmp == pt); 
}
//-----------------------------------------------------------------------------
bool Cave::move_player(int nt)
{	
	if(correct_path(nt))
	{
		plr = nt-1;
		return true;
	}
	else return false;
}
//-----------------------------------------------------------------------------
bool Cave::room_with_bat()
{
	if(rooms[plr].number() == rooms[bt].number()) 
	{
		int r = rand()%3;
		int pl = plr;
		if(r == 0) plr = rooms[pl].tunnel_1()-1;
		if(r == 1) plr = rooms[pl].tunnel_2()-1;
		if(r == 2) plr = rooms[pl].tunnel_3()-1;

		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
string Cave::after_step()
{
	// room with Wumpus
	if(rooms[plr].number() == rooms[wmp].number())
		return "You lose! You ate Wumpus. Press \"Close\" to restart.";

	// room with pit
	if(rooms[plr].number() == rooms[pt].number())
		return "You lose! You fall into a pit. Press \"Close\" to restart.";

	return "";
}
//-----------------------------------------------------------------------------
string Cave::dart_flight(int path) // arrow flight
{
	cnt_d--; // decrementing the number of arrows

	// if run out of arrows
	if(cnt_d == 0) 
		return "You lose! You run out of dart. Press \"Close\" to restart.";

	// getting into Wumpus
	if(wmp == path-1) 
		return "You win! Wumpus died. Press \"Close\" to restart.";	

	// arrow passes through three rooms, starting at a specified
	int room2 = plr+1;
	while(room2 == plr+1)
	{ 
		int r = rand() % 3; 
		if (r == 0) room2 = rooms[path-1].tunnel_1(); 
		if (r == 1) room2 = rooms[path-1].tunnel_2();
		if (r == 2) room2 = rooms[path-1].tunnel_3(); 
	}
	
	if(wmp == room2-1)
		return "You win! Wumpus died. Press \"Close\" to restart.";			

	int room3 = path;
	while(room3 == path)
	{
		int r = rand() % 3;
		if (r == 0) room3 = rooms[room2-1].tunnel_1(); 
		if (r == 1) room3 = rooms[room2-1].tunnel_2();
		if (r == 2) room3 = rooms[room2-1].tunnel_3(); 
	}

	if(wmp == room3-1)
		return "You win! Wumpus died. Press \"Close\" to restart.";	

	return "";
}
//-----------------------------------------------------------------------------
// check the entered path (number of next room)
bool Cave::correct_path(int path)
{
	if(path != rooms[plr].tunnel_1() && 
		path != rooms[plr].tunnel_2() && 
		path != rooms[plr].tunnel_3()) 
	{
		path = 0;
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------------
//END Cave