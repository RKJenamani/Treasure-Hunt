#include <bits/stdc++.h>
using namespace std;
class BlackBox
{
	int r,c;
	int x,y;
	int x1,y1;
	int x2,y2;
	int direction[4];
	//up,down,left right
	
public:

	BlackBox();

	int get_rows();

	int get_cols();

	void move_1(int d);

	void move_2(int d);

	
	pair<int,int> get_turtle_pos1();

	pair<int,int> get_turtle_pos2();

	int check_status(int xc, int yc);

	void update_food();

};