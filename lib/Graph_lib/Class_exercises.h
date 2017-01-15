//-------------------------------------------------------------------------------------
struct Striped_Rectangle : Rectangle{
    Striped_Rectangle(Point xy, int w, int h) : Rectangle(xy, w, h){}
    void set_fill_lines();
    void draw_lines() const;
};
//-------------------------------------------------------------------------------------
struct Striped_Circle : Circle{
	Striped_Circle(Point p, int r) : Circle(p, r){}
	void set_fill_lines();
  void draw_lines() const;
};
//-------------------------------------------------------------------------------------
struct Poly : Polygon{
    Poly(const Vector_ref<Point>& vp);
};
//-------------------------------------------------------------------------------------
struct Immobile_Circle : Circle{
public:
    Immobile_Circle(Point p, int r) : Circle(p, r){}
private:
    void move() const;
    int r;
};
//-------------------------------------------------------------------------------------
struct Smiley : Circle{
    Smiley(Point p, int r) : Circle (p, r), r(r){}
    void draw_lines() const;
private:
    int r;
};
//-------------------------------------------------------------------------------------
struct Frowny : Circle{
    Frowny(Point p, int r) : Circle (p, r), r(r){}
    void draw_lines() const;
private:
    int r;
};
//-------------------------------------------------------------------------------------
struct Round_hat : Smiley{
    Round_hat(Point p, int r) : Smiley(p, r), r(r){}
    void draw_lines() const;
private:
    int r;
};
//-------------------------------------------------------------------------------------
struct Triangle_hat : Smiley{
    Triangle_hat(Point p, int r) : Smiley(p, r), r(r){}
    void draw_lines() const;
private:
    int r;
};
//-------------------------------------------------------------------------------------
struct Arc : Shape{
  Arc(Point p, int w, int h, int b, int e);
  void draw_lines() const;
private:
  int w;
  int h;
  int b;
  int e;
};
//-------------------------------------------------------------------------------------
struct Box : Shape{
public:
  Box(Point p, int wb, int hb, int we, int he, string t);
  void draw_lines() const;
private:
  int wb;
  int hb;
  int we;
  int he;
  string t;
};
//-------------------------------------------------------------------------------------
struct Hexagon : Closed_polyline{
    Hexagon(Point cen, int rad);
private:
    int r;
};
//-------------------------------------------------------------------------------------
struct Regular_polygon : Closed_polyline{
    Regular_polygon(Point cen, int rad, int cnt_ang);
    Point center() const {return cen;}
    int radius() const {return r;}
private:
    Point cen;
    int r;
};
//-------------------------------------------------------------------------------------
struct Star : Shape{
    Star(Point cen, int rad, int cnt_ang);
    void draw_lines() const;
private:
    Point cen;
    int r;
};
//-------------------------------------------------------------------------------------
struct Right_triangle : Shape{
    Right_triangle(Point cen, int x, int y);
    void set_fill_lines();
    void draw_lines() const;
    int len_x() const {return x;}
    int len_y() const {return y;}
private:
  int x;
  int y;
};
//-------------------------------------------------------------------------------------
struct Octagon : Closed_polyline{
  Octagon(Point cen, int rad);
private:
  Point cen;
  int r;
};
//-------------------------------------------------------------------------------------
class Pseudo_window : public Fl_Window{
public:
  Pseudo_window(Point xy, int w, int h, const string& title);
  void attach(Shape& s) { shapes.push_back(&s); }
protected:
  void draw();
private:
  vector<Shape*> shapes;
  int w,h;
  void init();
};
//-------------------------------------------------------------------------------------
struct Binary_tree : Shape{
  Binary_tree(Point p, int lev, Color c, Line_style ls, int rad = 5, int step_dis = 6)
    : lev(lev), c(c), ls(ls), rad(rad), step_dis(step_dis)
  {
    if (lev < 0) error("Bad Binary_tree: negative value of levels");
    if (lev == 0) error("Bad Binary_tree: value of levels must be greater than zero");
    add(p);
  }
  void draw_shape() const;
  void draw_arrow() const;
  void draw_lines() const;
  void add_text(const string& text, const string& path);
  int distance() const;
  int radius() const {return rad;}
  int levels() const {return lev;}
  Color ln_color() const {return c;}
  Line_style ln_style() const {return ls;}
  string t;
private:
  int rad;
  int step_dis;
  int lev;
  Color c;
  Line_style ls;
};
//-------------------------------------------------------------------------------------
struct Rectangle_Bin_tree : Binary_tree{
  Rectangle_Bin_tree(Point p, int lev, Color c, Line_style ls, int rad = 5, int step_dis = 8)
    : Binary_tree(p, lev, c, ls, rad, step_dis) {}
  void draw_shape() const;
  void draw_lines() const;
};
//-------------------------------------------------------------------------------------
struct Func : Function {
public:
  Func(Fct f, double r1, double r2, Point orig,
      int count = 100, double xscale = 25, double yscale = 25);
  
  void reset_Func(Fct fn, double r1, double r2, Point orig, int count,
                 double xscale, double yscale);
  void reset_scale(double x , double y);
  void reset_range(double ran1, double ran2);
  void reset_num_pts(int cnt);
  void reset_Fct(Fct fn);
private:
  Point xy;
  Fct* f;
  int c;
  double r1, r2, xsc, ysc;
};
//-------------------------------------------------------------------------------------
struct Bar_graph : Shape{
  Bar_graph(Point xy, int len_y, int ny, int width_bar, double beg_step, string lab);
  void draw_lines() const;
  void add_bar(double height, string s, Color c = Color::invisible);
  void left_mark_sz(int size);
  void bottom_mark_sz(int size);
protected:
  void add_text_bar(string t);
private: 
  Point xy;
  int lx;
  int ly;
  int ny;
  double bs;
  Text label;
  Vector_ref<Text> tx_bottom;
  Vector_ref<Text> tx_left;
  Lines notches_y;
  Vector_ref<Rectangle> bars;
  int wb;
};
//-------------------------------------------------------------------------------------
struct Lines_window : Window{
  Lines_window(Point xy, int w, int h, const string& title);
private:  
  Open_polyline lines;
  
  Button next_button;
  Button quit_button;
  In_box next_x;
  In_box next_y;
  Out_box xy_out;
  Menu color_menu;
  Menu lnstyle_menu;
  Button color_menu_button;
  Button lnstyle_menu_button;

  void change_color(Color c) {lines.set_color(c);}
  void hide_color_menu() {color_menu.hide(); color_menu_button.show();}
  void change_lnstyle(Line_style lns) {lines.set_style(lns);}
  void hide_lnstyle_menu() {lnstyle_menu.hide(); lnstyle_menu_button.show();}

  void red_pressed() {change_color(Color::red); hide_color_menu();}
  void blue_pressed() {change_color(Color::blue); hide_color_menu();}
  void black_pressed() {change_color(Color::black); hide_color_menu();}
  void menu_color_pressed() {color_menu_button.hide(); color_menu.show();}

  void dash_pressed() {change_lnstyle(Line_style::dash); hide_lnstyle_menu();}
  void dot_pressed() {change_lnstyle(Line_style::dot); hide_lnstyle_menu();}
  void solid_pressed() {change_lnstyle(Line_style::solid); hide_lnstyle_menu();}
  void menu_lnstyle_pressed() {lnstyle_menu_button.hide(); lnstyle_menu.show();}

  void next();
  void quit();
  
  static void cb_color_red(Address, Address);
  static void cb_color_blue(Address, Address); 
  static void cb_color_black(Address, Address); 
  static void cb_color_menu(Address, Address);

  static void cb_lnstyle_dash(Address, Address);
  static void cb_lnstyle_dot(Address, Address);
  static void cb_lnstyle_solid(Address, Address);
  static void cb_lnstyle_menu(Address, Address);

  static void cb_next(Address, Address);
  static void cb_quit(Address, Address);
};
//-------------------------------------------------------------------------------------
#include "Class_exercises.cpp"
