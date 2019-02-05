#include <bits/stdc++.h>
#include "blackbox.h"
using namespace std;

int main() {
	BlackBox obj;
	obj.move_1(5); int x1, y1, x2, y2;
	cout<<"status = "<<obj.check_status(5,5)<<endl;
	// cout<<"print = "<<obj.print()<<endl;
	// cout<<"x1 = "<<obj.x1<<endl;
	pair<int, int> t1, t2;
	while(1) {
		char c;
		cin>>c;
		t1 = obj.get_turtle_pos1();
		t2 = obj.get_turtle_pos2();
		x1 = t1.first; y1 = t1.second;
		x2 = t2.first; y2 = t2.second;
		switch(c) {
			case 'w': obj.move_1(0); break;
			case 's': obj.move_1(1); break;
			case 'a': obj.move_1(2); break;
			case 'd': obj.move_1(3); break;

			case '1': cout<<"status = "<<obj.check_status(x1-1, y1)<<endl; break;
			case '2': cout<<"status = "<<obj.check_status(x1+1, y1)<<endl; break;
			case '3': cout<<"status = "<<obj.check_status(x1, y1-1)<<endl; break;
			case '4': cout<<"status = "<<obj.check_status(x1, y1+1)<<endl; break;

			case 'c': cout<<" pos1 = "<<t1.first<<","<<t1.second<<endl; break;	 

			case 'i': obj.move_2(0); break;
			case 'k': obj.move_2(1); break;
			case 'j': obj.move_2(2); break;
			case 'l': obj.move_2(3); break;

		}
	}
	// cout<<check_link()<<endl;
	return 0;
}