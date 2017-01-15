//BEGIN Room_img
//------------------------------------------------------------------------------
Room_img::Room_img(Point p_xy, int sd, int rnum)
  	: Graph_lib::Rectangle(p_xy, sd, sd), xy(p_xy), wh(sd), rn(rnum) 
{
	set_fill_color(Color::black); // default colors
	set_color(Color::red);
}
//------------------------------------------------------------------------------
void Room_img::draw_lines() const
{
	Graph_lib::Rectangle::draw_lines();  

	char buffer[20];
	itoa(rn, buffer, 10);
	string s = buffer;

	int w_cen = s.size() * 4;
	fl_draw(s.c_str(), xy.x + wh/2 - w_cen, xy.y + wh/2 + 5); 
}
//------------------------------------------------------------------------------
void Room_img::set_dflt_col()
{
	set_fill_color(Color::black);
	set_color(Color::red);
}
//------------------------------------------------------------------------------
//END Room_img

//BEGIN Shell_Name
//------------------------------------------------------------------------------
Shell_Name::Shell_Name(Point beg, string str, int wh, int top_ht, int bot_ht)
	: top(beg, wh, top_ht+1), 
	bottom(Point(beg.x, beg.y+top_ht), wh, bot_ht),  
	b(beg), s(str), w(wh), th(top_ht), bh(bot_ht) 
{ 
	top.set_fill_color(Color::black);
	top.set_color(Color::white);
	bottom.set_color(Color::white);
}
//------------------------------------------------------------------------------
void Shell_Name::draw_lines() const
{
	top.draw_lines();
	bottom.draw_lines();	
	// height one title char - 10 px (10/2 == 5 px)
	fl_draw(s.c_str(), b.x+15, b.y + th/2+5);  
}
//------------------------------------------------------------------------------
//END Shell_Name

//BEGIN Cave_Map
//------------------------------------------------------------------------------
Cave_Map::Cave_Map(Point p_xy, int side, int ln_spc)
	: xy(p_xy), sd(side), ln_s(ln_spc), w(side/3), h_head(35),
	p_beg(Point(xy.x+w+ln_s+w, xy.y+w+h_head)), 
	sh_map(xy, "MAP OF THE CAVE", side*5+ln_s*6+w*4, h_head, side*4+ln_s*3+w*2)
{
	set_pos_tunn();
	set_pos_rooms();
	sh_map.fill_color_bot(Color::black);
}
//------------------------------------------------------------------------------
void Cave_Map::set_pos_rooms()
{
	const int cnt_room = 20; // cave with 20 rooms
	Point step = p_beg;

	for(unsigned int i = 0; i < cnt_room; i++)
	{		
		// 4 horizontal sections on 5 rooms
		if((i % 5 == 0) && (i != 0))  
		{
			step.x = p_beg.x;
			step.y += sd + ln_s;
		}

		rooms.push_back(new Room_img(step, sd, i+1));
		step.x += sd + ln_s; 
	}
}
//------------------------------------------------------------------------------
void Cave_Map::set_pos_tunn()
{
	tn.push_back( // 1 horizontal
		new Graph_lib::Rectangle(Point(p_beg.x-(w+ln_s), p_beg.y+w), sd*5+ln_s*4+2*w+ln_s*2, w)
	);
	tn.push_back( // 2 horizontal 
		new Graph_lib::Rectangle(Point(p_beg.x+w*2, p_beg.y+ln_s+sd+w), sd*3+ln_s*4+w*2, w)
	);
	tn.push_back( // 3 horizontal
		new Graph_lib::Rectangle(Point(p_beg.x+w*2, p_beg.y+ln_s*2+sd*2+w), sd*3+ln_s*4+w*2, w)
	);
	tn.push_back( // 4 horizontal
		new Graph_lib::Rectangle(Point(p_beg.x-(w+ln_s), p_beg.y+sd*2+ln_s*3+w*4), sd*5+ln_s*4+ 2*w+ln_s*2, w)
	);


	tn.push_back( // 1 vertical (long)
		new Graph_lib::Rectangle(Point(p_beg.x-(w+ln_s), p_beg.y+w*2), w, sd*2+ln_s*3+w*2)
	);
	tn.push_back( // 2 vertical (long)
		new Graph_lib::Rectangle(Point(p_beg.x+w, p_beg.y+w*2), w, sd*2+ln_s*3+w*2)
	);
	tn.push_back( // 3 vertical (top)
		new Graph_lib::Rectangle(Point(p_beg.x+sd+ln_s+w, p_beg.y+w*2), w, ln_s+w*2)
	);
	tn.push_back( // 3 vertical (bottom)
		new Graph_lib::Rectangle(Point(p_beg.x+sd+ln_s+w, p_beg.y+sd*2+ln_s*2+w*2), w, ln_s+w*2)
	);
	tn.push_back( // 4 vertical (top)
		new Graph_lib::Rectangle(Point(p_beg.x+sd*2+ln_s*2+w, p_beg.y+w*2), w, ln_s+w*2)
	);
	tn.push_back( // 4 vertical (bottom)
		new Graph_lib::Rectangle(Point(p_beg.x+sd*2+ln_s*2+w, p_beg.y+sd*2+ln_s*2+w*2), w, ln_s+w*2)
	);
	tn.push_back( // 5 vertical (top)
		new Graph_lib::Rectangle(Point(p_beg.x+sd*3+ln_s*3+w, p_beg.y+w*2), w, ln_s+w*2)
	);
	tn.push_back( // 5 vertical (bottom)
		new Graph_lib::Rectangle(Point(p_beg.x+sd*3+ln_s*3+w, p_beg.y+sd*2+ln_s*2+w*2), w, ln_s+w*2)
	);
	tn.push_back( // 6 vertical (long)
		new Graph_lib::Rectangle(Point(p_beg.x+sd*4+ln_s*4+w, p_beg.y+w*2), w, sd*2+ln_s*3+w*2)
	);
	tn.push_back( // 7 vertical (long)
		new Graph_lib::Rectangle(Point(p_beg.x+sd*5+ln_s*5, p_beg.y+w*2), w, sd*2+ln_s*3+w*2)
	);

	for(unsigned int i = 0; i < tn.size(); i++)
	{
		tn[i].set_color(Color::dark_red);
		tn[i].set_fill_color(Color::dark_red); // default color of tunnels
	}
}
//------------------------------------------------------------------------------
void Cave_Map::draw_lines() const
{
	sh_map.draw_lines();
	for(unsigned int i = 0; i < tn.size(); i++)
		tn[i].draw_lines();

	for(unsigned int i = 0; i < rooms.size(); i++)
		rooms[i].draw_lines();   
}
//------------------------------------------------------------------------------
void Cave_Map::fill_room_color(int n, Color c)
{
	if(n <= 0 || n > 20) return;
	rooms[n-1].set_fill_color(c);
}
//------------------------------------------------------------------------------
void Cave_Map::room_num_color(int n, Color c)
{
	if(n <= 0 || n > 20) return;
	rooms[n-1].set_color(c);
}
//------------------------------------------------------------------------------
void Cave_Map::dflt_col_room(int n)
{
	if(n <= 0 || n > 20) return;
	rooms[n-1].set_dflt_col();
}
//------------------------------------------------------------------------------
void Cave_Map::plr_in_room(int n)
{
	if(n <= 0 || n > 20) return;
	fill_room_color(n, Color::yellow);
	room_num_color(n, Color::black);
}
//------------------------------------------------------------------------------
//END Cave_Map

//BEGIN Cloud_conver
//------------------------------------------------------------------------------
Cloud_conver::Cloud_conver(Point beg, int width, int height)
	: p(beg), w(width), h(height)
{
	add(p);
	add(Point(p.x+w, p.y));
	add(Point(point(1).x, point(1).y+h));
  
	add(Point(p.x+28, p.y+h));
	add(Point(p.x, p.y+h+20));
	add(Point(p.x+10, p.y+h));
  
	add(Point(p.x, p.y+h));

	set_fill_color(Color::yellow);
	set_color(Color::dark_red);
}
//------------------------------------------------------------------------------
void Cloud_conver::clear_str()
{
	while(vs.size() != 0)
		vs.pop_back();
}
//------------------------------------------------------------------------------
void Cloud_conver::draw_lines() const
{
	if(vs.size() == 0) return;
	else
	{
		Closed_polyline::draw_lines();
		int y_step = 15;
		for(unsigned int i = 0; i < vs.size(); i++)
		{
			fl_draw(vs[i].c_str(), p.x+5, p.y+y_step);  
			y_step += 15;
		}
	}
}
//------------------------------------------------------------------------------
//END Cloud_conver