#ifndef TOADOS_H_GUITXTBUTTON
#define TOADOS_H_GUITXTBUTTON

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include "toados_gui.h"
#include "toados_hotspot.h"

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font;


class TS_TXTBUTTON {
	public:
		TS_TXTBUTTON();
		int load(char*); 				// pass button text
		int plot(int, int);				// Set x, y
		int tick(ALLEGRO_MOUSE_STATE*);	// Logic cycle
		int draw();						// Draws the button to display
		int set_padding(int, int);		// Set individual width and height
		int set_padding(int);			// Equal padding for both width and height


		TS_HOTSPOT hs;
		ALLEGRO_BITMAP* img;
		ALLEGRO_BITMAP* img2;
		ALLEGRO_COLOR color_blur;
		ALLEGRO_COLOR color_focus;
		ALLEGRO_COLOR color_disabled;
		ALLEGRO_COLOR bgcolor;		// Default is set to transparent.

		char* button_text;
		bool active;				// If the button has focus. Variable might be DEPRECATED soon.

		int w;						// Image width + padding_w
		int h;						// Image height + padding_h
	private:
		int padding_w;
		int padding_h;
		int img_w;					// Save the width of button image for future use
		int img_h;					// Do the same for height...
};


#endif // TOADOS_H_GUITXTBUTTON
