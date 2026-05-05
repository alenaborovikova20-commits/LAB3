#include <iostream>
#include <cmath>
using namespace std;


int main(){
	float y;
	cout << " x" << "  " << "y" << endl;
	for (float x = -5; x <= 6; ++x){
		if (x <= -1){
			y = -2 - x;
			cout << x << "  " << y << endl;}
		else if(x >= -1 && x < 0){
			y = sqrt(1 - (x * x)) - 1;
		       cout << x << "  " << y << endl;}
		else if (x >= 0 && x <= 2){
			y = 2 - sqrt(4 - x * x);
			cout << " " << x << "  " << y << endl;}
		else if (x >=2 && x <= 4){
			y = -1.0;
			cout << " " << x << "  " << y << endl;}
		else if (x >= 4 && x <= 6){
			y = 0.5 * x - 3;
			cout << " " << x << "  " << y << endl;}
		}	       
	return 0;
	} 

