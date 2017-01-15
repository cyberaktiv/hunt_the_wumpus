struct Wind : Graph_lib::Window{
	Wind(Point xy, int w, int h, const string& title);

private:
	Cave_Map cm; // map of the cave
	Cave cv; // cave

	// CONTROL MENU panel
	Shell_Name menu;
	In_box shoot_in;
	In_box move_in;
	Button shoot_but;
	Button move_but;
	Out_box cnt_arr; // count arrow

	// NOTES panel
	Shell_Name notes;
	In_box nt_pit;
	In_box nt_bat;
	In_box nt_wump;
	Button pit_in;
	Button bat_in;
	Button wump_in;
	Graph_lib::Rectangle pt;
	Graph_lib::Rectangle bt;
	Graph_lib::Rectangle wp;

	// talk cloud
	Cloud_conver feel;

	Button restart;

	void wait_command();
	void mark_room(In_box& ib, Color c, int& pr);

	void sht_but();
	void mv_but();

	void pit();
	void bat();
	void wump();
	
	void rest();

	void mess_rest(string s);
	void er_mess(string s);
  
	static void cb_sht_but(Address, Address);
	static void cb_mv_but(Address, Address);
  
	static void cb_pit(Address, Address);
	static void cb_bat(Address, Address);
	static void cb_wump(Address, Address);

	static void cb_rest(Address, Address);
};

//--------------------------------------------------------------------
#include "Wind_game.cpp"