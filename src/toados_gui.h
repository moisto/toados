#ifndef TOADOS_H_GUI
#define TOADOS_H_GUI

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"


/* This is the main GUI class meant to be used as a singleton, just the one for the whole program.
*  It makes the code neater.
*  And it takes care of all the mid-level management of setting up a user interface.
*  It is designed to make life easier.
*/

//typdef int TS_TRIGGER {  }

class TS_GUI {
	public:
		TS_GUI();
		ALLEGRO_EVENT* status();		// Returns latest event in queue
		int draw();
		int init(char*, int, int);		 // Window title text, width, and height
		int quit();
		void set_window_title(char*);

		ALLEGRO_DISPLAY* display;
		ALLEGRO_FONT* font;
		ALLEGRO_FONT* font_sm;
		ALLEGRO_FONT* font_lg;
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_MOUSE_STATE mouse;


		bool active;			// To check if program is still running

	private:
		char* title;			// Window title
		int width;
		int height;
};



#endif // TOADOS_H_GUI
