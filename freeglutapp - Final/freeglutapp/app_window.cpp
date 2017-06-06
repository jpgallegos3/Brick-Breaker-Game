
# include <iostream>
# include "app_window.h"

using namespace std;


AppWindow::AppWindow(const char* label, int x, int y, int w, int h)
	:GlutWindow(label, x, y, w, h)
{
	_markx = 0;
	_marky = 0;
	addMenuEntry("Option 0", evOption0);
	addMenuEntry("Option 1", evOption1);

	//stash.push_back(new Rect(0.0f, 0.6f, 0.8f, 0.6f, 0.0f, 0.0f, 1.0f));
	//stash.push_back(new GrPlotQuadratic(-0.8f, 0.6f, 0.8f, 0.6f, 1.0f, 0.0f, 0.0f));
	//stash.push_back(new GrPlotCubic(-0.5f, 0.0f, 0.8f, 0.6f, 0.0f, 1.0f, 0.0f));
	//stash.push_back(new GrPlotQuadratic(0.0f, 0.6f, 0.8f, 0.6f, 0.0f, 0.0f, 1.0f));
	//stash.push_back(new GrPlotQuadratic(0.0f, 0.3f, 0.8f, 0.6f, 0.0f, 1.0f, 1.0f));
	//stash.push_back(new GrPlotCubic(-0.5f, 0.7f, 0.8f, 0.6f, 0.5f, 0.5f, 0.5f));
	//stash.push_back(new GrPlotCubic(0.3f, -0.1f, 0.8f, 0.6f, 0.6f, 0.4f, 0.5f));
	//stash.push_back(new Clock(-0.8f, 0.6f, 0.8f, 0.6f, 1.0f, 0.0f, 0.0f));
	//stash.push_back(new Clock(0.8f, 0.6f, 0.8f, 0.6f, 1.0f, 0.0f, 1.0f));
	block.push_back(new Block(-0.9, 0.9f, 0.2f, 0.2f, 1.0f, 0.0f, 0.0f, show));
	block.push_back(new Block(0.0f, 0.9f, 0.2f, 0.2f, 1.0f, 0.0f, 0.0f, show));
	block.push_back(new Block(-0.6f, 0.9f, 0.2f, 0.2f, 1.0f, 0.0f, 0.0f, show));
	block.push_back(new Block(-0.3f, 0.9f, 0.2f, 0.2f, 1.0f, 0.0f, 0.0f, show));
	block.push_back(new Block(0.3f, 0.9f, 0.2f, 0.2f, 1.0f, 0.0f, 0.0f, show));
	block.push_back(new Block(0.6f, 0.9f, 0.2f, 0.2f, 1.0f, 0.0f, 0.0f, show));
	P = new Paddle(0.0, -0.9f, 0.2f, 0.1f, 1.0f, 0.0f, 0.0);

		
	offsetX = 0;
	offsetY = 0;

		ball_x = 0.0f;
		ball_y = -0.85f;
		diff_x;

		
	mouseDown = false;
	dragging = false;
	Resize = false;
	space = false;
	hit = false;
	P_hit = false;
	WL_hit = false;
	WR_hit = false;
	Top_hit = false;
	crash = false;
	sign_y = 1;
	lives = 3;
	level = 1;

	std::cout << "CSE 165: Object Oriented Programming Final Project " << std::endl;
	std::cout << "Brick Breaker " << std::endl;
	std::cout << "Start with 3 lives, win the stage by breaking all the blocks " << std::endl;
	std::cout << "Game speeds up after each stage win " << std::endl;
	std::cout << "Controls: Mouse/Arrow keys to move left/right" << std::endl;
	std::cout << "Press start to launch ball" << std::endl;
	std::cout << "GOOD LUCK!! " << std::endl;
	
	std::cout << " " << std::endl;
	cout << "Level " << level << endl;
	cout << "Lives: " << lives << endl;
}

void AppWindow::idle() {
	crash = false;
	if (space && !hit && !P_hit && !WR_hit && !WL_hit && !Top_hit) {
		ball_y += 0.003*sign_y;
		diff_x = 0.0f;
	}

	for (vector<Block*>::iterator i = block.begin(); i != block.end(); i++) {
		if ((*i)->contains(Vec(ball_x,ball_y)) && (*i)->showing == true)
		{
			diff_x = ball_x - ((*i)->x + (*i)->w / 2);
			hit = true;
			P_hit = false;
			WL_hit = false;
			WR_hit = false;
			Top_hit = false;
			crash = false;
			sign_y = -sign_y;
			//i = block.erase(i);
			(*i)->showing = false;
			counter = counter - 1;
			

		}
	}

	if (counter == 0)
	{
		for (vector<Block*>::iterator i = block.begin(); i != block.end(); i++) {
			(*i)->showing = true;
			(*i)->r = (*i)->r - 0.2;
			if ((*i)->r <= 0) {
				(*i)->r = 1.0;
			}

			(*i)->blue = (*i)->blue - 0.5;
			if ((*i)->blue <= 0) {
				(*i)->blue = 1.0;
			}

			(*i)->g = (*i)->g - 0.1;
			if ((*i)->g <= 0) {
				(*i)->g = 1.0;
			}
		}
		counter = 6;
		space = false;
		P_hit = false;
		Top_hit = false;
		hit = false;
		WR_hit = false;
		WL_hit = false;
		crash = true;
		sign_y = 1;
		level += 1;
		cout << "Level " << level << endl;

	}

	if (lives == 0)
	{
		for (vector<Block*>::iterator i = block.begin(); i != block.end(); i++) {
			(*i)->showing = true;
			(*i)->r = 1;
			(*i)->blue = 0;
			(*i)->g = 0;
		}
		counter = 6;
		space = false;
		P_hit = false;
		Top_hit = false;
		hit = false;
		WR_hit = false;
		WL_hit = false;
		crash = true;
		sign_y = 1;
		cout << "Lives: " << lives << endl;
		cout << "GAME OVER!!" << endl;
		cout << " " << endl;
		lives = 3;
		level = 1;
		cout << "Level " << level<< endl;
		cout << "Lives: " << lives << endl;
		
		
	}

	if (P->contains(Vec(ball_x, ball_y)))
	{
		diff_x = ball_x - (P->x + P->w / 2);
		P_hit = true;
		hit = false;
		WL_hit = false;
		WR_hit = false;
		Top_hit = false;
		crash = false;
		sign_y = 1;
		
	}

	if (ball_x >= 1.0f)
	{
		P_hit = false;
		hit = false;
		WR_hit = true;
		WL_hit = false;
		Top_hit = false;
		crash = false;
		diff_x = -diff_x;
		
	}

	if (ball_x <= -1.0f)
	{
		P_hit = false;
		hit = false;
		WR_hit = false;
		WL_hit = true;
		Top_hit = false;
		crash = false;
		diff_x = -diff_x;

	}

	if (ball_y >= 1.0f)
	{
		Top_hit = true;
		hit = false;
		WR_hit = false;
		WL_hit = false;
		P_hit = false;
		crash = false;
		sign_y = -1;

	}

	if (ball_y <= -0.95f)
	{
		space = false;
		P_hit = false;
		Top_hit = false;
		hit = false;
		WR_hit = false;
		WL_hit = false;
		crash = true;
		sign_y = 1;
		lives = lives - 1;
		if (lives > 0) {
			cout << "Lives: " << lives << endl;
		}

	}

	if (hit) {
		ball_y = ball_y + 0.003*sign_y;
		ball_x = ball_x + 0.003*diff_x;
	}

	if (P_hit) {
		ball_y += 0.003*sign_y;
		ball_x = ball_x + 0.003*diff_x;
	}

	if (WL_hit)
	{
		ball_y += 0.003*sign_y;
		ball_x = ball_x + 0.003*diff_x;
	}

	if (WR_hit)
	{
		ball_y += 0.003*sign_y;
		ball_x = ball_x + 0.003*diff_x;
	}

	if (Top_hit)
	{
		ball_y = ball_y + 0.003*sign_y;
		ball_x = ball_x + 0.003*diff_x;
	}

	if (crash)
	{
		ball_y = -0.85f;
		ball_x = 0.0f;
	}

	redraw();
}

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene(float& x, float &y)
{
	x = (2.0f*(x / float(_w))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(_h)));
}

// Called every time there is a window event
void AppWindow::handle(const Event& e)
{
	bool rd = true;

	if (e.type == Keyboard)
		switch (e.key)
		{
		case ' ': // space bar
			space = true;
			//_markx = 1.5;
			_marky = 1.5;
			redraw();
			break;

		case 27: // Esc was pressed
			exit(1);
		}

	if (e.type == MouseDown || e.type == Motion)
	{
		_markx = (float)e.mx;
		_marky = (float)e.my;
		windowToScene(_markx, _marky);

		Vec mousePos = Vec(_markx, _marky);

		if (!mouseDown) {
			for (vector<Rect*>::iterator i = stash.begin(); i != stash.end(); i++)
			{
				(*i)->deselect();
				(*i)->unresize();
			}

			for (vector<Rect*>::iterator i = stash.begin(); i != stash.end(); i++)
			{
				if ((*i)->contains(mousePos))
				{
						Rect * temp = *i;
						temp->select();

						stash.erase(i);
						stash.insert(stash.begin(), temp);

						if (stash[0]->getY() - _marky <= 0.1) {
							dragging = true;

							offsetX = _markx - stash[0]->getX();
							//offsetY = _marky - temp->getY();
							offsetY = stash[0]->getY() - _marky;
						}

						//if (((_markx >= right - 0.1) && (vec.x <= right)) && ((vec.y >= bottom) && (vec.y <= bottom + 0.1)))
						if (((_markx >= stash[0]->getX() + stash[0]->getW() - 0.1) && (_markx <= stash[0]->getX() + stash[0]->getW())) && ((_marky >= stash[0]->getY() - stash[0]->getH()) && (_marky <= stash[0]->getY() - stash[0]->getH() + 0.1)))
						{
							Resize = true;
							temp->setresize();

							offsetX = _markx - stash[0]->getX();
							offsetY = _marky - temp->getY();
							
						}

						else {
							stash[0]->handle(_markx, _marky);
						}

						break;
			  }

		  }
	  }
	  mouseDown = true;

	  if (dragging)
	  {
		  Rect * top = stash[0];

		  top->setX(_markx - offsetX);
		  //top->setY(_marky - offsetY);
		  top->setY(_marky + offsetY);
	  }

	  if (Resize)
	  {
		  Rect * top = stash[0];
		  top->setW(_markx - stash[0]->getX());
		  top->setH(stash[0]->getY() - _marky);
	  }
   }

   if ( e.type==Menu )
    { std::cout<<"Menu Event: "<<e.menuev<<std::endl;
      rd=false; // no need to redraw
    }

   if (e.type == MouseUp)
   {
	   mouseDown = false;
	   dragging = false;
	   Resize = false;
   }
   

   const float incx=0.03f;
   const float incy=0.02f;
   if ( e.type==SpecialKey )
    switch ( e.key )
    { case GLUT_KEY_LEFT:  _markx-=incx; break;
      case GLUT_KEY_RIGHT: _markx+=incx; break;
      case GLUT_KEY_UP:    _marky+=incy; break;
      case GLUT_KEY_DOWN:  _marky-=incy; break;
      default: rd=false; // no redraw
	}

   if (rd) 
	   redraw(); // ask the window to be rendered when possible
}


void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::draw()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear the trasnformation stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	for (vector<Block*>::iterator i = block.begin(); i != block.end(); i++)
	{
		(*i)->draw();
	}
	
	//Paddle * P = new Paddle(_markx, -0.9f, 0.2f, 0.1f, 1.0f, 0.0f, 0.0);
	P->setX(_markx);
	P->draw();

	Vec ball(ball_x, ball_y);

	if (!space)
	{
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2f(_markx + P->w / 2, ball.y);
		glEnd();
		ball_x = _markx + P->w / 2;
	}

	if (space)
	{
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(ball_x, ball.y);
		glEnd();
	}
	




	//Swap buffers
	glFlush();         // flush the pipeline (usually not necessary)
	glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}
