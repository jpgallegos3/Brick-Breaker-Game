#include <iostream>
#include <vector>
using namespace std;

struct Vec {
	public:

		float x;
		float y;


	Vec(){
		x = 0;
		y = 0;
	}

	Vec(float X, float Y){
		x = X;
		y = Y;
	}

	float getX()
	{
		return x;

	}

	float getY()
	{
		return y;

	}
	void add(Vec vec){
		x = x + vec.x;
		y = y + vec.y;
	}

	void print(){
		cout << "(" << x << ", " << y << ")" << endl;
	}
};
