//BEGIN Room
//-----------------------------------------------------------------------------
struct Room{
	Room(int num_room, int tun1, int tun2, int tun3)
		: nr(num_room), t1(tun1), t2(tun2), t3(tun3) {}
    int number() const { return nr; }
    int tunnel_1() const { return t1; }
    int tunnel_2() const { return t2; }
    int tunnel_3() const { return t3; }
private:
	int nr; // number of room
	int t1, t2, t3; // rooms in which need to go
};
//-----------------------------------------------------------------------------
//END Room

//BEGIN Cave
//-----------------------------------------------------------------------------
struct Cave{
	Cave();
	vector<string> feel_near(); // someone close
	void move_wump(); // random move Wumpus
	bool move_player(int nt);

	string after_step(); // text message, if the player comes into a room that is not empty
	string dart_flight(int path); // text message, if the arrow reaches the Wumpus
	bool room_with_bat(); // if a room with a bat, it moves the player to a random next room
	bool correct_path(int path);

	int wump_rm() const { return wmp+1; }
	int bat_rm() const { return bt+1; }
	int pit_rm() const { return pt+1; }
	int player_rm() const { return plr+1; }
	int cnt_dart() const { return cnt_d; } 

	void print_all(); // for debug (the location of all)
private:
	void locate_all(); // random location
	void build(); // build cave
	
	int wmp, bt, pt, plr, cnt_d;
	vector<Room> rooms;
};
//-----------------------------------------------------------------------------
//END Cave

#include "Logic_game.cpp"

