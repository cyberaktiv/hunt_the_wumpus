//BEGIN Room_img
//------------------------------------------------------------------------------
// room - rectangle with number in the middle
// color of number and room can change
struct Room_img : Graph_lib::Rectangle{
	Room_img(Point p_xy, int sd, int rnum);

	void draw_lines() const;
	void set_dflt_col();
private:
	Point xy;
	int wh; // side of room
	int rn; // number or room
};
//------------------------------------------------------------------------------
//END Room_img

//BEGIN Shell_Name
//------------------------------------------------------------------------------
struct Shell_Name : Shape{
	Shell_Name(Point beg, string str, int wh, int top_ht, int bot_ht);

	void fill_color_top(Color c) { top.set_fill_color(c); }
	void fill_color_bot(Color c) { bottom.set_fill_color(c); }
	void set_color_top(Color c) { top.set_color(c); }
	void set_color_bot(Color c) { bottom.set_color(c); }
	void draw_lines() const;

	int width() const { return w; }
	int height() const { return th+bh; }
	Point beg() const { return b; }

private:
	Point b;
	string s;
	int w;  // width shell
	int th; // height top rectangle (with text)
	int bh; // height bottom rectangle
	Graph_lib::Rectangle top;
	Graph_lib::Rectangle bottom;
};
//------------------------------------------------------------------------------
//END Shell_Name

//BEGIN Cave_Map
//------------------------------------------------------------------------------
struct Cave_Map : Shape{
	Cave_Map(Point p_xy, int side, int ln_spc);
	void fill_room_color(int n, Color c);
	void room_num_color(int n, Color c); //color frame and number of room	
  
	void dflt_col_room(int n);
	void plr_in_room(int n); // player in room (color mark)

	int width() const { return sh_map.width(); }
	int height() const { return sh_map.height(); }

	void draw_lines() const;

private:
	void set_pos_rooms(); // locate rooms
	void set_pos_tunn(); // establish tunnels between rooms
	Vector_ref<Graph_lib::Rectangle> tn; // tunnels
	Vector_ref<Room_img> rooms; // rooms
	
	int w;  // width of tunnel
	int h_head; // height rectangle-title
	int sd; // side of room
	int ln_s; // size between rooms
	Point xy; // position which set user
	Point p_beg; // left-top angle of first room
	Shell_Name sh_map; // title
};
//------------------------------------------------------------------------------
//END Cave_Map

//BEGIN Cloud_conver
//------------------------------------------------------------------------------
struct Cloud_conver : Closed_polyline{ 
	Cloud_conver(Point beg, int width, int height);

	void clear_str();
	void add_text(string s) { vs.push_back(s); }
	void draw_lines() const;

private:
	int w;
	int h;
	Point p;
	vector<string> vs;
};
//------------------------------------------------------------------------------
//END Cloud_conver

#include "Graph_game.cpp"