//-------------------------------------------------------------------------------------
void Striped_Rectangle::draw_lines() const
{
    Rectangle::draw_lines();
    if (number_of_points() > 1)
    for(int i = 1; i < number_of_points(); i++)
    {
        if (i != number_of_points()-1)
            fl_line(point(i).x, point(i).y, point(i+1).x, point(i+1).y);
        i++;
    }
}
//-------------------------------------------------------------------------------------
void Striped_Rectangle::set_fill_lines()
{
    for(int i = 0; i < height(); i+=2)
    {
        Shape::add(Point(point(0).x, point(0).y + i));
        Shape::add(Point(point(0).x + width()-1, point(0).y + i));
    }
}
//-------------------------------------------------------------------------------------
void Striped_Circle::draw_lines() const
{  
  Circle::draw_lines();
  if (number_of_points() > 1)
  {
    const int hlf = number_of_points() / 2;
    const int qrt = hlf / 2;
    const int three_qrt = hlf + qrt;
    for(int i = hlf; i < three_qrt; i++)
      for(int j = 0; j < qrt; j+=2)
        for(int k = 0; k < qrt; k++)
          if (Point(center().x-k,center().y-j) == point(i))
          {
            fl_line(center().x-k+1, center().y-j, center().x, center().y-j);
            fl_line(center().x-k+1, center().y+j, center().x, center().y+j);
            fl_line(center().x+k-1, center().y-j, center().x, center().y-j);
            fl_line(center().x+k-1, center().y+j, center().x, center().y+j);
          }
  }
}
//-------------------------------------------------------------------------------------
void Striped_Circle::set_fill_lines()
{    
  double one_perc = double(radius()) / 100.0;
  double cnt_angles = ( one_perc * 24.0 + radius() ) * 10.0;

    const double pi = 3.14;
    int degree = 0;
    int x, y;
    int cnt = 0;
    for(int i = 0; i < cnt_angles; i+=2)
    {
        x = center().x + radius() * cos(degree + (2 * pi * i) / cnt_angles);
        y = center().y + radius() * sin(degree + (2 * pi * i) / cnt_angles);
      Shape::add(Point(x, y));
    }
}
//-------------------------------------------------------------------------------------
Poly::Poly(const Vector_ref<Point>& vp)
{
    if (vp.size() < 3) error("less than 3 points in a Poly");
    for(int i = 0; i < vp.size(); i++)
        Polygon::add(vp[i]);
}
//-------------------------------------------------------------------------------------
void Smiley::draw_lines() const
{
    if (color().visibility())
    {
        const int half_r = r / 2;
        const int third_r = r / 3;
        fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
        fl_arc(point(0).x+third_r, point(0).y+third_r, half_r, half_r, 0, 360); //left eye
        fl_arc(point(0).x+r+half_r-third_r, point(0).y+third_r, half_r, half_r, 0, 360); //right eye
        fl_arc(point(0).x+half_r, point(0).y+half_r, r, r, 200, 340); //smile
    }
}
//-------------------------------------------------------------------------------------
void Frowny::draw_lines() const
{
    if (color().visibility())
    {
        const int half_r = r / 2;
        const int third_r = r / 3;
        fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
        fl_arc(point(0).x+third_r, point(0).y+third_r, half_r, half_r, 0, 360); //left eye
        fl_arc(point(0).x+r+half_r-third_r, point(0).y+third_r, half_r, half_r, 0, 360); //right eye
        fl_arc(point(0).x+half_r, point(0).y+r, r, r, 20, 160); //frown
    }
}
//-------------------------------------------------------------------------------------
void Round_hat::draw_lines() const
{
    Smiley::draw_lines();
    fl_line(point(0).x, point(0).y, point(0).x + r*2, point(0).y);
    fl_arc(point(0).x+r/2,point(0).y-r/2,r,r,0,180);
}
//-------------------------------------------------------------------------------------
void Triangle_hat::draw_lines() const
{
    Smiley::draw_lines();
    fl_line(point(0).x, point(0).y, point(0).x + r*2, point(0).y);
    fl_line(point(0).x+r/2, point(0).y, point(0).x+r, point(0).y-r/2);
    fl_line(point(0).x+r/2+r, point(0).y, point(0).x+r, point(0).y-r/2);
}
//-------------------------------------------------------------------------------------
Arc::Arc(Point p, int w, int h, int b, int e) : w(w), h(h), b(b), e(e)
{
  	if (b > 360 || e > 360 || b < 0 || e < 0) error ("Bad Arc: incorrect value of a degree");
  	add(Point(p.x-w,p.y-h));
}
//-------------------------------------------------------------------------------------
void Arc::draw_lines() const
{
    if (color().visibility())
        fl_arc(point(0).x, point(0).y, w+w, h+h, b, e);
}
//-------------------------------------------------------------------------------------
Box::Box(Point p, int wb, int hb, int we, int he, string t) : wb(wb), hb(hb), we(we), he(he), t(t)
{
  	if (wb < 0 || hb < 0 || we < 0 || he < 0) error("Bad Box: negative value of degrees");
  	if (we+he > wb || we+he > hb) error("Bad Box: going beyond the framework");
  	add(Point(p.x, p.y));
  	add(Point(p.x + wb - (we+we), p.y));
  	add(Point(p.x, p.y + hb - (he+he)));
  	add(Point(p.x + wb - (we+we),p.y + hb - (he+he)));
}
//-------------------------------------------------------------------------------------
void Box::draw_lines() const
{
    if (color().visibility())
    {
        fl_arc(point(0).x, point(0).y, we+we, he+he, 90, 180);
        fl_arc(point(1).x, point(1).y, we+we, he+he, 0, 90);
        fl_arc(point(2).x, point(2).y, we+we, he+he, 180, 270);
        fl_arc(point(3).x, point(3).y, we+we, he+he, 270, 360);
        
        fl_line(point(0).x + we, point(0).y, point(1).x + we, point(1).y);
        fl_line(point(2).x + we, point(2).y + (he+he-1), point(3).x + we, point(3).y + (he+he-1));
        fl_line(point(0).x, point(0).y + he, point(2).x, point(2).y + he);
        fl_line(point(1).x + (we+we-1), point(1).y + he, point(3).x + (we+we-1), point(3).y + he);
    }

    Text tx(Point(point(0).x + 10, point(0).y + hb / 2 + 6), t);
    tx.set_font_size(20);
    tx.set_font(Font::times_bold);
    tx.draw_lines();
}
//-------------------------------------------------------------------------------------
Hexagon::Hexagon(Point cen, int rad) : r(r)
{
    if (rad <= 0) error("Bad Hexagon: negative value of radius");
    int x, y;
    const double pi = 3.1415926;
    const int cnt_ang = 6;
    const int deg = 0;
    for (int i = 0; i < cnt_ang; i++)
    {
        x = cen.x + rad * cos(deg + (2 * pi * i) / cnt_ang);
        y = cen.y + rad * sin(deg + (2 * pi * i) / cnt_ang);
        add(Point(x, y));
    }
}
//-------------------------------------------------------------------------------------
Regular_polygon::Regular_polygon(Point cen, int rad, int cnt_ang) : cen(cen), r(rad)
{
    if (cnt_ang <= 2) error("Bad Regular_polygon: less than 3 points in a Regular_polygon");
    if (rad <= 0) error("Bad Regular_polygon: negative value of radius");
    int x, y;
    const double pi = 3.1415926;
    const int deg = 0;
    for (int i = 0; i < cnt_ang; i++)
    {
        x = cen.x + rad * cos(deg + (2 * pi * i) / cnt_ang);
        y = cen.y + rad * sin(deg + (2 * pi * i) / cnt_ang);
        add(Point(x, y));
    }
}
//-------------------------------------------------------------------------------------
Star::Star(Point cen, int rad, int cnt_ang) : cen(cen), r(rad)
{
    if (cnt_ang <= 4) error("Bad Star: less than 4 points in a Star");
    if (rad <= 0) error("Bad Star: negative value of radius");
    int x, y;
    const double pi = 3.1415926;
    for (int i = 0; i < cnt_ang; i++)
    {
        x = cen.x + rad * cos(0 + (2 * pi * i) / cnt_ang);
        y = cen.y + rad * sin(0 + (2 * pi * i) / cnt_ang);
        add(Point(x, y));
    }
}
//-------------------------------------------------------------------------------------
void Star::draw_lines() const
{
    int half_p = number_of_points() / 2;
    if (number_of_points() % 2 > 0)
    {
        for(int i = 0; i < (half_p + 1); i++)
        {
            fl_line(point(i).x, point(i).y, point(i + half_p).x, point(i + half_p).y);
            if (i < half_p)
                fl_line(point(i).x, point(i).y, point(i + half_p + 1).x, point(i + half_p + 1).y);
        }
    }
    else
    {
        for(int i = 0; i < (half_p + 1); i++)
        {
            fl_line(point(i).x, point(i).y, point(i + half_p-1).x, point(i + half_p-1).y);
            if (i < half_p-1)
                fl_line(point(i).x, point(i).y, point(i + half_p + 1).x, point(i + half_p + 1).y);
        }
    }
}
//-------------------------------------------------------------------------------------
Right_triangle::Right_triangle(Point cen, int x, int y) : x(x), y(y)
{
    if (x == 0 || y == 0) error("Bad Right_triangle: incorrect x or y");
    add(cen);
    add(Point(cen.x + x, cen.y));
    add(Point(cen.x, cen.y - y));
}
//-------------------------------------------------------------------------------------
void Right_triangle::draw_lines() const
{
  fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
  fl_line(point(1).x, point(1).y, point(2).x, point(2).y);
  fl_line(point(0).x, point(0).y, point(2).x, point(2).y);

  if (number_of_points() > 3)
  for(int i = 3; i < number_of_points(); i++)
  {
    fl_line(point(i).x, point(i).y, point(i+1).x, point(i+1).y);
    i++;
  }
}
//-------------------------------------------------------------------------------------
Octagon::Octagon(Point cen, int rad) : cen(cen), r(rad)
{
  if (rad <= 0) error("Bad Octagon: negative value of radius");
  int x, y;
  const double pi = 3.1415926;
  const int cnt_ang = 8;
  const int deg = 0;
  for (int i = 0; i < cnt_ang; i++)
  {
      x = cen.x + rad * cos(deg + (2 * pi * i) / cnt_ang);
      y = cen.y + rad * sin(deg + (2 * pi * i) / cnt_ang);
      add(Point(x, y));
  }
}
//-------------------------------------------------------------------------------------
Pseudo_window::Pseudo_window(Point xy, int ww, int hh, const string& title)
  :Fl_Window(xy.x,xy.y,ww,hh,title.c_str()),w(ww),h(hh)
{
  init();
}
//-------------------------------------------------------------------------------------
void Pseudo_window::init()
{
  resizable(this);
  show();
}
//-------------------------------------------------------------------------------------
void Pseudo_window::draw()
{
  Fl_Window::draw();
  for (unsigned int i=0; i<shapes.size(); ++i) shapes[i]->draw();
}
//-------------------------------------------------------------------------------------
int Binary_tree::distance() const
{
  if (step_dis < 2) return 2*rad;
  else if (step_dis % 2 != 0) return (step_dis+1) * rad;
  return step_dis * rad;
}
//-------------------------------------------------------------------------------------
void Binary_tree::add_text(const string& text, const string& path)
{
  if (path.size() >= levels()) error("Bad Binary_tree: path below the last level");
  for (int i = 0; i < path.size(); i++)
    if (path[i] != 'l' && path[i] != 'r')
      error("Bad Binary_tree: path must contain the characters 'l' or 'r'");

  Point p;
  if (path[0] == 'l') p = Point(point(0).x, point(0).y+distance()+radius());
  else if(path[0] == 'r') p = Point(point(0).x+radius()*2, point(0).y+distance()+radius());

  Point ptmp = p;
  int step_lr = radius() * 2;
  int prev_sl = step_lr;
  int step_down = distance();
  for (int i = 1; i < path.size(); i++)
  {
      if (path[0] == 'l')
      {
          if (path[i] == 'l') p = Point(p.x-step_lr, p.y+distance());
          else
          {
            step_lr -= radius()*2;
            p = Point(p.x-step_lr, p.y+distance());
          }
      }
      else
      {
          if (path[i] == 'r') p = Point(p.x+step_lr, p.y+distance());
          else
          {
            step_lr -= radius()*2;
            p = Point(p.x+step_lr, p.y+distance());
          }
      }
      step_lr = step_lr + prev_sl;
      prev_sl = step_lr;
  }
  add(p);
  t = text;
}
//-------------------------------------------------------------------------------------
void Binary_tree::draw_shape() const
{
  int diam = radius() * 2;
  int step_x = radius();
  int step_y = distance();
  int nodes = 1;
  fl_arc(point(0).x,point(0).y,diam,diam,0,360);
  for(int i = 1; i < levels(); i++)
  {
    for(int j = 0; j < nodes; j++)
    {
      fl_arc(point(0).x+step_x,point(0).y+step_y,diam,diam,0,360);
      fl_arc(point(0).x-step_x,point(0).y+step_y,diam,diam,0,360);
      step_x += diam;
    }
    step_x = radius();
    step_y += distance();
    nodes *= 2;
  }
}
//-------------------------------------------------------------------------------------
void Binary_tree::draw_arrow() const
{
  fl_color(ln_color().as_int());
  fl_line_style(ln_style().style());
  const int diam = radius() * 2;
  int nodes = 1;
  const int twain_steps = distance() / diam;
  int step_xy = twain_steps;
  int left = 0;
  for(int i = 1; i < lev; i++)
  {
    if (i == 1)
    {
      fl_line(point(0).x+radius(), point(0).y+radius(), point(0).x, point(0).y+distance()+radius());
      fl_line(point(0).x+radius(), point(0).y+radius(), point(0).x+diam, point(0).y+distance()+radius());
    }
    for(int j = 0; j < nodes; j++)
    {
      if (i != lev-1)
      {
        fl_line(point(0).x-left, point(0).y+radius()+diam*step_xy, point(0).x-(left*2), point(0).y +radius()+diam*(step_xy+twain_steps));
        fl_line(point(0).x-left, point(0).y+radius()+diam*step_xy, point(0).x-(left*2+diam), point(0).y +radius()+diam*(step_xy+twain_steps));
        
        fl_line(point(0).x+left+diam, point(0).y+radius()+diam*step_xy, point(0).x+(left*2+diam), point(0).y +radius()+diam*(step_xy+twain_steps));
        fl_line(point(0).x+left+diam, point(0).y+radius()+diam*step_xy, point(0).x+(left*2+diam*2), point(0).y +radius()+diam*(step_xy+twain_steps));
        left += diam;
      }
    }
    nodes *= 2;
    step_xy += twain_steps;
    left = 0;
  }
}
void Binary_tree::draw_lines() const
{
  draw_shape();
  draw_arrow();
  if(number_of_points() > 1)
  {
    fl_font(FL_HELVETICA,12);
    fl_draw(t.c_str(),point(1).x,point(1).y);
  }
}
//-------------------------------------------------------------------------------------
void Rectangle_Bin_tree::draw_shape() const
{
  int diam = radius() * 2;
  int step_x = radius();
  int step_y = distance();
  int nodes = 1;
  fl_rect(point(0).x,point(0).y,diam,diam);
  for(int i = 1; i < levels(); i++)
  {
    for(int j = 0; j < nodes; j++)
    {
      fl_rect(point(0).x+step_x,point(0).y+step_y,diam,diam);
      fl_rect(point(0).x-step_x,point(0).y+step_y,diam,diam);
      step_x += diam;
    }
    step_x = radius();
    step_y += distance();
    nodes *= 2;
  }
}
//-------------------------------------------------------------------------------------
void Rectangle_Bin_tree::draw_lines() const
{
  draw_shape();
  Binary_tree::draw_arrow();
}
//-------------------------------------------------------------------------------------
Func::Func(Fct f, double r1, double r2, Point xy,
                   int count, double xscale, double yscale)
  : f(f), r1(r1), r2(r2), xy(xy), c(count), xsc(xscale), ysc(yscale),
  Function(f, r1, r2, xy, count, xscale, yscale){}
//-------------------------------------------------------------------------------------
void Func::reset_Func(Fct fn, double r1, double r2, Point orig, int count,
                 double xscale, double yscale)
{
  if (r2-r1<=0) error("bad graphing range");
  if (count <=0) error("non-positive graphing count");
  double dist = (r2-r1)/count;
  double r = r1;
  for (int i = 0; i<count; ++i)
  {
    set_point(i, Point(orig.x+int(r*xscale),orig.y-int(fn(r)*yscale)));
    r += dist;
  }
}
//-------------------------------------------------------------------------------------
void Func::reset_scale(double x, double y)
{
  xsc = x;
  ysc = y;
  reset_Func(f, r1, r2, xy, c, xsc, ysc);
}
//-------------------------------------------------------------------------------------
void Func::reset_range(double ran1, double ran2)
{
  r1 = ran1;
  r2 = ran2;
  reset_Func(f, r1, r2, xy, c, xsc, ysc);
}
//-------------------------------------------------------------------------------------
void Func::reset_num_pts(int cnt)
{
  if (cnt > c) cnt = c;
  for(int i = cnt; i < c; i++)
    erase_point(i); //убираем лишние точки
  c = cnt;
  reset_Func(f, r1, r2, xy, c, xsc, ysc);
}
//-------------------------------------------------------------------------------------
void Func::reset_Fct(Fct fn)
{
  f = fn;
  reset_Func(f, r1, r2, xy, c, xsc, ysc);
}
//-------------------------------------------------------------------------------------
Bar_graph::Bar_graph(Point xy, int len_y, int ny, int width_bar, double beg_step, string lab)
 : xy(xy), lx(width_bar*2), ly(len_y), ny(ny) , wb(width_bar), bs(beg_step),
  label(Point(0,0), lab)
{
  if (1<ny)
  {
    int dist2 = len_y/ny;
    int y = xy.y-dist2;
    for (int i = 0; i<ny; ++i)
    {
      notches_y.add(Point(xy.x,y),Point(xy.x+5,y));
      y -= dist2;
    }
  }
  label.move(xy.x-10,xy.y-ly-10);

  int place_tx = int(bs);
  for(int i = 0; i < notches_y.number_of_points()/2; i++)
  {
    char s_2[255];
    itoa(place_tx, s_2, 10);
    tx_left.push_back(new Text(Point(notches_y.point(i*2).x-30,
                      notches_y.point(i*2).y+5), s_2));
    tx_left[i].set_font_size(14);
    place_tx += bs;
  }
}
//-------------------------------------------------------------------------------------
void Bar_graph::draw_lines() const
{
  if (bars.size() > 0)
  {
    fl_line(xy.x, xy.y, xy.x+lx, xy.y);
    fl_line(xy.x, xy.y, xy.x, xy.y-ly);
    notches_y.draw();
    label.draw();
    for(int i = 0; i < bars.size(); i++)
      bars[i].draw();
    for(int i = 0; i < tx_bottom.size(); i++)
      tx_bottom[i].draw();
    for(int i = 0; i < tx_left.size(); i++)
      tx_left[i].draw();
  }
}
//-------------------------------------------------------------------------------------
void Bar_graph::add_bar(double height, string s, Color c)
{
  if(height/bs > ny) error("Bad Bar_graph in void add(): value out of range");
  lx+=wb;

  height /= bs;
  int hght_bar = ly/ny*height;
  bars.push_back(new Rectangle(Point(xy.x+lx-wb*2, xy.y-hght_bar),
                     wb+1, hght_bar+1));
  add_text_bar(s);
  bars[bars.size()-1].set_fill_color(c);
}
//-------------------------------------------------------------------------------------
void Bar_graph::add_text_bar(string t)
{
  static int i = 0;
  tx_bottom.push_back(new Text(Point(bars[i].point(0).x, xy.y+14), t));
  tx_bottom[i].set_font_size(14);
  i++;
}
//-------------------------------------------------------------------------------------
void Bar_graph::left_mark_sz(int size)
{
  for(int i = 0; i < tx_left.size(); i++)
    tx_left[i].set_font_size(size);
}
//-------------------------------------------------------------------------------------
void Bar_graph::bottom_mark_sz(int size)
{
  for(int i = 0; i < tx_bottom.size(); i++)
    tx_bottom[i].set_font_size(size);
}
//-------------------------------------------------------------------------------------
Lines_window::Lines_window(Point xy, int w, int h, const string& title)
  :Window(xy, w, h, title), 
  color_menu(Point(x_max()- 70, 30), 70, 20, Menu::vertical, "color"),
  color_menu_button(Point(x_max()- 80, 30), 80, 20, "color menu", cb_color_menu),

  lnstyle_menu(Point(x_max()- 70, 130), 70, 20, Menu::vertical, "lnstyle"),
  lnstyle_menu_button(Point(x_max() - 80, 130), 80, 20, "lnstyle menu", cb_lnstyle_menu),

  next_button(Point(x_max()- 150, 0), 70, 20, "Next point", cb_next),
  quit_button(Point(x_max()- 70, 0), 70, 20, "Quit", cb_quit),
  next_x(Point(x_max()- 310, 0), 50, 20, "next x:"), 
  next_y(Point(x_max()- 210, 0), 50, 20, "next_y:"),
  xy_out(Point(100, 0), 100, 20, "current (x, y):")
{
  attach(next_button);
  attach(quit_button);
  attach(next_x);
  attach(next_y);
  attach(xy_out);
  xy_out.put("no point");
  color_menu.attach(new Button(Point(0, 0), 0, 0, "red", cb_color_red));
  color_menu.attach(new Button(Point(0, 0), 0, 0, "blue", cb_color_blue));
  color_menu.attach(new Button(Point(0, 0), 0, 0, "black", cb_color_black));
  attach(color_menu);
  color_menu.hide();
  attach(color_menu_button);

  lnstyle_menu.attach(new Button(Point(0, 0), 0, 0, "dash", cb_lnstyle_dash));
  lnstyle_menu.attach(new Button(Point(0, 0), 0, 0, "dot", cb_lnstyle_dot));
  lnstyle_menu.attach(new Button(Point(0, 0), 0, 0, "solid", cb_lnstyle_solid));
  attach(lnstyle_menu);
  lnstyle_menu.hide();
  attach(lnstyle_menu_button);

  attach(lines);
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_quit(Address, Address pw)
{
  reference_to<Lines_window>(pw).quit();
}
//-------------------------------------------------------------------------------------
void Lines_window::quit()
{
  hide();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_next(Address, Address pw)
{
  reference_to<Lines_window>(pw).next();
}
//-------------------------------------------------------------------------------------
void Lines_window::next()
{
  int x = next_x.get_int();
  int y = next_y.get_int();
  lines.add(Point(x, y));

  stringstream ss;
  ss << '(' << x << ',' << y << ')';
  xy_out.put(ss.str());
  redraw();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_color_red(Address, Address pw)
{
  reference_to<Lines_window>(pw).red_pressed();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_color_blue(Address, Address pw)
{
  reference_to<Lines_window>(pw).blue_pressed();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_color_black(Address, Address pw)
{
  reference_to<Lines_window>(pw).black_pressed();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_color_menu(Address, Address pw)
{
  reference_to<Lines_window>(pw).menu_color_pressed();
}

//-------------------------------------------------------------------------------------
void Lines_window::cb_lnstyle_dash(Address, Address pw)
{
  reference_to<Lines_window>(pw).dash_pressed();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_lnstyle_dot(Address, Address pw)
{
  reference_to<Lines_window>(pw).dot_pressed();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_lnstyle_solid(Address, Address pw)
{
  reference_to<Lines_window>(pw).solid_pressed();
}
//-------------------------------------------------------------------------------------
void Lines_window::cb_lnstyle_menu(Address, Address pw)
{
  reference_to<Lines_window>(pw).menu_lnstyle_pressed();
}
//-------------------------------------------------------------------------------------