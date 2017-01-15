//BEGIN Wind
//-----------------------------------------------------------------------------
Wind::Wind(Point xy, int w, int h, const string& title)
	: Window(xy, w, h, title), 
	cm(Point(0, 0), 60, 20),  

	// CONTROL MENU panel
	menu(Point(cm.width(), 105), "CONTROL MENU", 160, 35, 100),
	shoot_in(Point(menu.beg().x + 60, menu.beg().y + 40), 40, 20, "Shoot:"),
	move_in(Point(menu.beg().x + 60, menu.beg().y + 70), 40, 20, "Move:"),
	shoot_but(Point(menu.beg().x + 110, menu.beg().y + 40), 40, 20, "OK", cb_sht_but),
	move_but(Point(menu.beg().x + 110, menu.beg().y + 70), 40, 20, "OK", cb_mv_but),
	cnt_arr(Point(menu.beg().x + 110, menu.beg().y + 100), 40, 20, "Count of arrow: "),

	// NOTES panel
	notes(Point(cm.width() , menu.beg().y+menu.height()), "NOTES", 240, 35, 100),
	nt_pit(Point(notes.beg().x + 90, notes.beg().y + 40), 40, 20, "here pit:"),
	nt_bat(Point(notes.beg().x + 90, notes.beg().y + 70), 40, 20, "here bat:"),
	nt_wump(Point(notes.beg().x + 90, notes.beg().y + 100), 40, 20, "here wump:"),
	pit_in(Point(notes.beg().x + 140, notes.beg().y + 40), 40, 20, "IN", cb_pit),
	bat_in(Point(notes.beg().x + 140, notes.beg().y + 70), 40, 20, "IN", cb_bat),
	wump_in(Point(notes.beg().x + 140, notes.beg().y + 100), 40, 20, "IN", cb_wump),
	pt(Point(notes.beg().x + 190, notes.beg().y + 40), 40, 20),
	bt(Point(notes.beg().x + 190, notes.beg().y + 70), 40, 20),
	wp(Point(notes.beg().x + 190, notes.beg().y + 100), 40, 20),
  
	feel(Point(cm.width()+5, 5), 135, 65),

	restart(Point(cm.width() + 150, 15), 70, 20, "Restart", cb_rest)
{
	pt.set_fill_color(Color::cyan);
	bt.set_fill_color(Color::green);
	wp.set_fill_color(Color::blue);

	attach(cm);
  
	// CONTROL MENU panel
	attach(menu);
	attach(shoot_in);
	attach(move_in);
	attach(shoot_but);
	attach(move_but);
	attach(cnt_arr);

	// NOTES panel
	attach(notes);
	attach(nt_pit);
	attach(nt_bat);
	attach(nt_wump);
	attach(pit_in);
	attach(bat_in);
	attach(wump_in);
	attach(pt);
	attach(bt);
	attach(wp);

	attach(feel);
	attach(restart);
	cnt_arr.put(cv.cnt_dart());

	wait_command();
}
//------------------------------------------------------------------------------
void Wind::cb_pit(Address, Address pw)
{
  reference_to<Wind>(pw).pit();
}
//------------------------------------------------------------------------------
void Wind::cb_bat(Address, Address pw)
{
  reference_to<Wind>(pw).bat();
}
//------------------------------------------------------------------------------
void Wind::cb_wump(Address, Address pw)
{
  reference_to<Wind>(pw).wump();
}

//------------------------------------------------------------------------------
void Wind::cb_sht_but(Address, Address pw)
{
  reference_to<Wind>(pw).sht_but();
}
//------------------------------------------------------------------------------
void Wind::cb_mv_but(Address, Address pw)
{
  reference_to<Wind>(pw).mv_but();
}
//------------------------------------------------------------------------------
void Wind::cb_rest(Address, Address pw)
{
  reference_to<Wind>(pw).rest();
}
//------------------------------------------------------------------------------
void Wind::sht_but()
{
	if(cv.correct_path(shoot_in.get_int()))
	{
		string r = cv.dart_flight(shoot_in.get_int());
	
		if(r != "") mess_rest(r);
		cnt_arr.put(cv.cnt_dart()); // count arrow output
		cv.move_wump(); 
		wait_command();
		cv.print_all();
	}
	else er_mess("incorrect path, try again...");
}
//------------------------------------------------------------------------------
void Wind::mv_but()
{
	feel.clear_str(); // clear talk cloud
	int prev_plr = cv.player_rm(); // remember previous position of player

	if (cv.move_player(move_in.get_int())) // player is move
	{
		cm.dflt_col_room(prev_plr); // default color for previous room
		redraw();
		// if the player comes into the room with an even number, Wumpus moves
		if(cv.player_rm() % 2 == 0) cv.move_wump();
		wait_command();
		cv.print_all();
	}
	else er_mess("incorrect path, try again...");
}
//------------------------------------------------------------------------------
void Wind::wait_command()
{
	feel.clear_str();
	if (cv.room_with_bat()) feel.add_text("The bat moved me!");

	string r = cv.after_step();
	if (r != "") mess_rest(r);

	cm.plr_in_room(cv.player_rm()); // mark room with player

	int sz = cv.feel_near().size();
	for(int i = 0; i < sz; i++)
		feel.add_text(cv.feel_near()[i]); // output feel of player (in talk cloud)
  
	redraw();
}
//------------------------------------------------------------------------------

void Wind::mark_room(In_box& ib, Color c, int& pr)
{
	int nr = ib.get_int();
	if (nr < 1 || nr > 20)
	{ 
		er_mess("No such room, try again!");
		return;
	}
	else if(nr == cv.player_rm()) 
	{
		er_mess("In this room is a player!");
		return;
	}
	else
	{
		if(pr) cm.dflt_col_room(pr);
		cm.room_num_color(nr, c); 
	}

	pr = nr;
	redraw();
}
//------------------------------------------------------------------------------
void Wind::pit()
{ 
	static int prev = 0;
	mark_room(nt_pit, Color::cyan, prev);
}
//------------------------------------------------------------------------------
void Wind::bat()
{
	static int prev = 0;
	mark_room(nt_bat, Color::green, prev);
}
//------------------------------------------------------------------------------
void Wind::wump()
{
	static int prev = 0;
	mark_room(nt_wump, Color::blue, prev);
}
//------------------------------------------------------------------------------
void Wind::rest()
{
	hide();
	main();
}
//------------------------------------------------------------------------------
void Wind::mess_rest(string s)
{
	er_mess(s);
	rest();
}
//------------------------------------------------------------------------------
void Wind::er_mess(string s)
{
	fl_message(s.c_str());
}
//------------------------------------------------------------------------------
//END Wind