#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>
# define M_PI           3.14159265358979323846  /* pi */


#include "Vec.h"

using namespace std;

struct Rect
{
	vector<Vec*> points;
	float x;
	float y;	
	float w;
	float h;
	bool  sel,res;
	float r;
	float g;
	float blue;
	


	
	Rect() {


	}

	Rect(float X, float Y, float W, float H, float R, float G, float B)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
		r = R;
		g = G;
		blue = B;
		sel = false;
	}

	float getX()
	{
		return x;
	}

	void setX(float X)
	{
		x = X;
	}

	float getY()
	{
		return y;
	}

	void setY(float Y)
	{
		y = Y;
	}

	float getW()
	{
		return w;
	}

	void setW(float W)
	{
		w = W;

	}

	float getH()
	{
		return h;
	}

	void setH(float H)
	{
		h = H;

	}

	float getR()
	{
		return r;
	}

	float getG()
	{
		return g;
	}

	float getB()
	{
		return blue;
	}
	void select()
	{
		sel = true;
	}

	void deselect()
	{
		sel = false;
	}
	bool selected()
	{
		return sel;
	}
	void setresize()
	{
		res = true;
	}

	void unresize()
	{
		res = false;
	}
	bool resize()
	{
		return sel;
	}


	//bool deselected
	bool contains(Vec vec) {
		float left = x;
		float right = x + w;
		float top = y;
		float bottom = y - h;

		if ((vec.x >= left && vec.x <= right) && (vec.y <= top && vec.y >= bottom))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	void handle() {


	}

	virtual void draw() {
		
		Vec tl, tr, br, bl, m_xt, m_xb,m_yl,m_yr;

		tl = Vec(x, y);
		tr = Vec(x + w, y);
		br = Vec(x + w, y - h);
		bl = Vec(x, y - h);
		m_xt = Vec(x + w/2, y);
		m_xb = Vec(x + w / 2, y - h);
		m_yl = Vec(x, y - h / 2);
		m_yr = Vec(x + w, y - h / 2);



		glLineWidth(1);

		glColor3f(1.0, 1.0, 1.0);

		glBegin(GL_LINES);

		glVertex2f(m_xt.x, m_xt.y);
		glVertex2f(m_xb.x, m_xb.y);

		glVertex2f(m_yl.x, m_yl .y);
		glVertex2f(m_yr.x, m_yr.y);

		glEnd();

		for (std::vector<Vec *>::iterator i = points.begin(); i != points.end(); ++i) 
		{
			glBegin(GL_POINTS);

			glVertex2f(x + (*i)->x*w, y - (*i)->y*h);

			glEnd();
		}

		glBegin(GL_POLYGON);
		glColor3f(r, g, blue);
		glVertex2f(tl.x, tl.y);
		glVertex2f(tr.x, tr.y);
		glVertex2f(br.x, br.y);
		glVertex2f(bl.x, bl.y);

		glEnd();

		if (sel)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);

			//glVertex2f(tl.x, tl.y - 0.1);
			//glVertex2f(tr.x, tr.y - 0.1);

			glVertex2f(tl.x, tl.y);
			glVertex2f(tr.x, tr.y);

			glVertex2f(tr.x, tr.y);
			glVertex2f(br.x, br.y);

			glVertex2f(br.x, br.y);
			glVertex2f(bl.x, bl.y);

			glVertex2f(bl.x, bl.y);
			glVertex2f(tl.x, tl.y);

			glEnd();

		}



	}

	virtual void handle(float mx, float my) {
		points.push_back(new Vec((mx - x)/w, (y - my)/h));
	}
	
};

class GrPlotQuadratic : public Rect {
	

public:
	vector<Vec*>points;
	float a = 1;
	float b = 0;
	float c = 0;

	GrPlotQuadratic(float X, float Y, float W, float H, float R, float G, float B){

		x = X;
		y = Y;
		w = W;
		h = H;
		r = R;
		g = G;
		blue = B;
		sel = false;
		generate(-1, 1, 30);

	}

	void generate(float xini,float xend, float inc)
	{
		float Q;
		float increment = (xend - xini) / inc;

		while (xini <= xend)
		{
			Q = a*xini*xini + b*xini + c;
			points.push_back(new Vec(xini, Q));
			xini = xini + increment;

		}

	}

	virtual void draw() {

		Vec tl, tr, br, bl, m_xt, m_xb, m_yl, m_yr;

		tl = Vec(x, y);
		tr = Vec(x + w, y);
		br = Vec(x + w, y - h);
		bl = Vec(x, y - h);
		m_xt = Vec(x + w / 2, y);
		m_xb = Vec(x + w / 2, y - h);
		m_yl = Vec(x, y - h / 2);
		m_yr = Vec(x + w, y - h / 2);



		glLineWidth(1);

		glColor3f(1.0, 1.0, 1.0);

		glBegin(GL_LINES);

		glVertex2f(m_xt.x, m_xt.y);
		glVertex2f(m_xb.x, m_xb.y);

		glVertex2f(m_yl.x, m_yl.y);
		glVertex2f(m_yr.x, m_yr.y);

		glEnd();

		for (std::vector<Vec *>::iterator i = points.begin(); i != points.end(); ++i)
		{
			glBegin(GL_POINTS);
			glVertex2f((w / 2) * (*i)->x + x + (w / 2), (h / 2) * (*i)->y + y - (h / 2));
			//glVertex2f(x + (*i)->x*w, y - (*i)->y*h);

			glEnd();
		}

		glBegin(GL_POLYGON);
		glColor3f(r, g, blue);
		glVertex2f(tl.x, tl.y);
		glVertex2f(tr.x, tr.y);
		glVertex2f(br.x, br.y);
		glVertex2f(bl.x, bl.y);

		glEnd();

		if (sel)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);

			//glVertex2f(tl.x, tl.y - 0.1);
			//glVertex2f(tr.x, tr.y - 0.1);

			glVertex2f(tl.x, tl.y);
			glVertex2f(tr.x, tr.y);

			glVertex2f(tr.x, tr.y);
			glVertex2f(br.x, br.y);

			glVertex2f(br.x, br.y);
			glVertex2f(bl.x, bl.y);

			glVertex2f(bl.x, bl.y);
			glVertex2f(tl.x, tl.y);

			glEnd();

		}



	}

	virtual void handle(float mx, float my) {
		//points.push_back(new Vec((mx - x) / w, (y - my) / h));
	}

};


class GrPlotCubic : public Rect {
	
public:
	vector<Vec*>points;
	float a;
	float b;
	float c;
	float d;

	GrPlotCubic(float X, float Y, float W, float H, float R, float G, float B) {

		x = X;
		y = Y;
		w = W;
		h = H;
		r = R;
		g = G;
		blue = B;
		sel = false;
		generate(-1, 1, 30);

	}

	void generate(float xini, float xend, float inc)
	{
		a = 1;
		b = 0;
		c = 0;
		d = 0;

		float Q;
		float increment = (xend - xini) / inc;

		while (xini <= xend)
		{
			Q = a*xini*xini*xini + b*xini*xini + c*xini + d;
			points.push_back(new Vec(xini, Q));
			xini = xini + increment;
		}

	}

	virtual void draw() {

		Vec tl, tr, br, bl, m_xt, m_xb, m_yl, m_yr;

		tl = Vec(x, y);
		tr = Vec(x + w, y);
		br = Vec(x + w, y - h);
		bl = Vec(x, y - h);
		m_xt = Vec(x + w / 2, y);
		m_xb = Vec(x + w / 2, y - h);
		m_yl = Vec(x, y - h / 2);
		m_yr = Vec(x + w, y - h / 2);



		glLineWidth(1);

		glColor3f(1.0, 1.0, 1.0);

		glBegin(GL_LINES);

		glVertex2f(m_xt.x, m_xt.y);
		glVertex2f(m_xb.x, m_xb.y);

		glVertex2f(m_yl.x, m_yl.y);
		glVertex2f(m_yr.x, m_yr.y);

		glEnd();

		for (std::vector<Vec*>::iterator i = points.begin(); i != points.end(); ++i)
		{
			glBegin(GL_POINTS);
			glVertex2f((w/2) * (*i)->x + x + (w / 2), (h / 2) * (*i)->y + y - (h / 2));
			//glVertex2f(x + (*i)->x*w, y - (*i)->y*h);

			glEnd();
		}

		glBegin(GL_POLYGON);
		glColor3f(r, g, blue);
		glVertex2f(tl.x, tl.y);
		glVertex2f(tr.x, tr.y);
		glVertex2f(br.x, br.y);
		glVertex2f(bl.x, bl.y);

		glEnd();

		if (sel)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);

			//glVertex2f(tl.x, tl.y - 0.1);
			//glVertex2f(tr.x, tr.y - 0.1);

			glVertex2f(tl.x, tl.y);
			glVertex2f(tr.x, tr.y);

			glVertex2f(tr.x, tr.y);
			glVertex2f(br.x, br.y);

			glVertex2f(br.x, br.y);
			glVertex2f(bl.x, bl.y);

			glVertex2f(bl.x, bl.y);
			glVertex2f(tl.x, tl.y);

			glEnd();

		}



	}

	virtual void handle(float mx, float my) {
		//points.push_back(new Vec((mx - x) / w, (y - my) / h));
	}

};

class Clock : public Rect {

 public:
	 vector<Vec*> points;

	//float clockR = 80.0f;
	//float clockVol = 100.0f;
	float angle1min = M_PI / 30.0f;
	float minStart = 0.9f;
	float minEnd = 1.0f;
	float stepStart = 0.8f;
	float stepEnd = 1.0f;
	const float DEG2RAD = 3.14159 / 180;


	float hours;
	float minutes;
	float seconds;
	float xs, ys, xm, ym, xh, yh;

	Clock(){
		hours = 0;
		minutes = 0;
		seconds = 0;
	}

	Clock(float X, float Y, float W, float H, float R, float G, float B) {

		x = X;
		y = Y;
		w = W;
		h = H;
		r = R;
		g = G;
		blue = B;
		sel = false;

		
	}

	void add(const Clock& C) {
		seconds = seconds + C.getSeconds();
		if (seconds >= 60)
		{
			seconds = seconds - 60;
			minutes = minutes + 1;
		}

		minutes = minutes + C.getMinutes();
		if (minutes >= 60)
		{
			minutes = minutes - 60;
			hours = hours + 1;
		}

		hours = hours + C.getHours();
		if (hours >= 12)
		{
			hours = hours - 12;
		}
	}

	float getHours() const {
		return hours;

	}

	float getMinutes() const {
		return minutes;

	}

	float getSeconds() const {
		return seconds;

	}

	void getAngles(float& h, float& m, float& s) {
		s = (6 * seconds); //Calculates in degrees

		if ((s + 90) >= 360) //Conversion to specified angles
		{
			s = (450 - s);
			s = s *(M_PI / 180);
		}
		else
		{
			s = s + 90;
			if (s > 180 && s < 360)
			{
				s = 180 - s;
				s = s *(M_PI / 180);
			}

			else
			{
				s = 180 - s;
				s = s *(M_PI / 180);
			}

		}

		m = (6 * minutes); //Calculates in degrees

		if ((m + 90) >= 360)  //in 4th quad
		{
			m = (450 - m);
			m = m *(M_PI / 180);
		}

		else
		{
			m = m + 90;
			if (m > 180 && m < 360)
			{
				m = 180 - m;
				m = m *(M_PI / 180);
			}
			else
			{
				m = 180 - m;
				m = m *(M_PI / 180);
			}
		}

		h = (0.5 * (hours * 60 + minutes)); //Calculates in degrees along with minutes

		if ((h + 90) >= 360)
		{
			h = (450 - h);
			h = h *(M_PI / 180);
		}

		else
		{
			h = h + 90;
			if (h > 180 && h < 360)
			{
				h = 180 - h;
				h = h *(M_PI / 180);
			}

			else
			{
				h = 180 - h;
				h = h *(M_PI / 180);
			}
		}

	}

	void getHourCoords(float& x, float& y)
	{
		float a_h, a_m, a_s = 0.0f;
		getAngles(a_h, a_m, a_s);

		x = cos(a_h);
		y = sin(a_h);
	}

	void getMinuteCoords(float& x, float& y)
	{
		float a_h, a_m, a_s = 0.0f;
		getAngles(a_h, a_m, a_s);

		x = cos(a_m);
		y = sin(a_m);
	}

	void getSecondsCoords(float& x, float& y)
	{
		float a_h, a_m, a_s = 0.0f;
		getAngles(a_h, a_m, a_s);

		x = cos(a_s);
		y = sin(a_s);
	}


	void newLine(float rStart, float rEnd, float angle) {
		float c = cos(angle), s = sin(angle);
		glVertex2f(rStart*c*w/2 + x + w/2, rStart*s*h/2 + y -h/2);
		glVertex2f(rEnd*c*w / 2 + x + w / 2, rEnd*s*h / 2 + y - h / 2);
	}

	void get() {
		std::time_t t = std::time(NULL);
		std::tm* tm = std::localtime(&t); // returns pointer to a static object
		hours = tm->tm_hour;
		minutes = tm->tm_min;
		seconds = tm->tm_sec;
	}

	virtual void draw() {
		
		Vec tl, tr, br, bl, m_xt, m_xb, m_yl, m_yr,m_xy;

		tl = Vec(x, y);
		tr = Vec(x + w, y);
		br = Vec(x + w, y - h);
		bl = Vec(x, y - h);
		m_xt = Vec(x + w / 2, y);
		m_xb = Vec(x + w / 2, y - h);
		m_yl = Vec(x, y - h / 2);
		m_yr = Vec(x + w, y - h / 2);
		m_xy = Vec(x + w / 2, y - h / 2);



		get();

		getSecondsCoords(xs, ys);
	
		//cout << "Seconds = " << seconds << endl;
		getMinuteCoords(xm, ym);
		
		//cout << "Minutes = " << minutes << endl;
		getHourCoords(xh, yh);
		
		//cout << "Hours = " << hours << endl;


		/*glLineWidth(1);

		glColor3f(1.0, 1.0, 1.0);

		glBegin(GL_LINES);

		glVertex2f(m_xt.x, m_xt.y);
		glVertex2f(m_xb.x, m_xb.y);

		glVertex2f(m_yl.x, m_yl.y);
		glVertex2f(m_yr.x, m_yr.y);

		glEnd();*/


		//Draws marks along circle
		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(2.0f);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glBegin(GL_LINES);
		for (int i = 0; i <60; i++) {
			if (i % 5) { // normal minute
				if (i % 5 == 1)
					glColor3f(1.0f, 1.0f, 1.0f);
					newLine(minStart, minEnd, i*angle1min);
				
			}
			else {
				glColor3f(0.0f, 1.0f, 0.0f);
				newLine(stepStart, stepEnd, i*angle1min);
			}
		}
		glEnd();

		//Draw seconds hand
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2d(m_xy.x,m_xy.y);
		glVertex2d(xs*w/2 + x + w/2, ys*h/2 + y - h/2);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2d(m_xy.x, m_xy.y);
		glVertex2d(xm*w / 2 + x + w / 2, ym*h / 2 + y - h / 2);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2d(m_xy.x, m_xy.y);
		glVertex2d(xh*w / 2 + x + w / 2, yh*h / 2 + y - h / 2);
		glEnd();


		for (std::vector<Vec*>::iterator i = points.begin(); i != points.end(); ++i)
		{
			glBegin(GL_LINES);
			glVertex2f((w / 2) * (*i)->x + x + (w / 2), (h / 2) * (*i)->y + y - (h / 2));
			//glVertex2f(x + (*i)->x*w, y - (*i)->y*h);

			glEnd();
		}

		glBegin(GL_POLYGON);
		glColor3f(r, g, blue);
		glVertex2f(tl.x, tl.y);
		glVertex2f(tr.x, tr.y);
		glVertex2f(br.x, br.y);
		glVertex2f(bl.x, bl.y);

		glEnd();

		if (sel)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);

			//glVertex2f(tl.x, tl.y - 0.1);
			//glVertex2f(tr.x, tr.y - 0.1);

			glVertex2f(tl.x, tl.y);
			glVertex2f(tr.x, tr.y);

			glVertex2f(tr.x, tr.y);
			glVertex2f(br.x, br.y);

			glVertex2f(br.x, br.y);
			glVertex2f(bl.x, bl.y);

			glVertex2f(bl.x, bl.y);
			glVertex2f(tl.x, tl.y);

			glEnd();

		}



	}

	virtual void handle(float mx, float my) {
		//points.push_back(new Vec((mx - x) / w, (y - my) / h));
		points.push_back(new Vec(mx, my));
	}


};

class Block : public Rect {

public:
	vector<Vec*> points;
	float x;
	float y;
	float w;
	float h;
	float r;
	float g;
	float blue;
	bool showing;


	Block() {

	}

	Block(float X, float Y, float W, float H, float R, float G, float B, bool s)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
		r = R;
		g = G;
		blue = B;
		showing = s;
	}

	float getX()
	{
		return x;
	}

	void setX(float X)
	{
		x = X;
	}

	float getY()
	{
		return y;
	}

	void setY(float Y)
	{
		y = Y;
	}

	float getW()
	{
		return w;
	}

	void setW(float W)
	{
		w = W;

	}

	float getH()
	{
		return h;
	}

	void setH(float H)
	{
		h = H;

	}

	float getR()
	{
		return r;
	}

	float getG()
	{
		return g;
	}

	float getB()
	{
		return blue;
	}



	//bool deselected
	bool contains(Vec vec) {
		float left = x;
		float right = x + w;
		float top = y;
		float bottom = y - h;

		if ((vec.x >= left && vec.x <= right) && (vec.y <= top && vec.y >= bottom))
		{
			return true;
		}

		else
		{
			return false;
		}
	}


	virtual void draw() {

		Vec tl, tr, br, bl, m_xt, m_xb, m_yl, m_yr;

		tl = Vec(x, y);
		tr = Vec(x + w, y);
		br = Vec(x + w, y - h);
		bl = Vec(x, y - h);
		m_xt = Vec(x + w / 2, y);
		m_xb = Vec(x + w / 2, y - h);
		m_yl = Vec(x, y - h / 2);
		m_yr = Vec(x + w, y - h / 2);

		if (this->showing == true) {
			glBegin(GL_POLYGON);
			glColor3f(r, g, blue);
			glVertex2f(tl.x, tl.y);
			glVertex2f(tr.x, tr.y);
			glVertex2f(br.x, br.y);
			glVertex2f(bl.x, bl.y);

			glEnd();
		}


	}

	virtual void handle(float mx, float my) {
		//points.push_back(new Vec((mx - x) / w, (y - my) / h));
	}


};

class Paddle {
public:
	float x;
	float y;
	float w;
	float h;
	float r;
	float g;
	float blue;

	Paddle(float X, float Y, float W, float H, float R, float G, float B) {
		x = X;
		y = Y;
		w = W;
		h = H;
		r = R;
		g = G;
		blue = B;

	}

	bool contains(Vec vec) {
		float left = x;
		float right = x + w;
		float top = y;
		float bottom = y - h;

		if ((vec.x >= left && vec.x <= right) && (vec.y <= top && vec.y >= bottom))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	void setX(float X)
	{
		x = X;
	}

	virtual void draw() {

		Vec tl, tr, br, bl;

		tl = Vec(x, y);
		tr = Vec(x + w, y);
		br = Vec(x + w, y - h);
		bl = Vec(x, y - h);
	


		glBegin(GL_POLYGON);
		glColor3f(r, g, blue);
		glVertex2f(tl.x, tl.y);
		glVertex2f(tr.x, tr.y);
		glVertex2f(br.x, br.y);
		glVertex2f(bl.x, bl.y);

		glEnd();



	}


};




