
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <vector>

# include "glut_window.h"
# include "Rect.h"

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    enum MenuEv { evOption0, evOption1 };
    float _markx, _marky;
    int _w, _h;

	//Vector of GrRect*
	std::vector<Rect*> stash;
	std::vector<Block*> block;
	Paddle * P;
	Vec * ball;
	bool space, hit,P_hit,WL_hit,WR_hit,Top_hit, crash;
	bool show = true;
	bool Resize = false;
	bool dragging = false;
	bool mouseDown;
	float offsetX;
	float offsetY;
	float sign_y;
	int counter = 6;
	int lives = 3;
	int level;

	float ball_x, ball_y,diff_x;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void windowToScene ( float& x, float &y );

   private : // functions derived from the base class
    virtual void handle ( const Event& e );
    virtual void draw ();
    virtual void resize ( int w, int h );
	virtual void idle();
 };

#endif // APP_WINDOW_H
