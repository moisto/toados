#ifndef TS_GUI_TXTINPUT_H
#define TS_GUI_TXTINPUT_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include "toados_helper_triggers.h"
#include "toados_hotspot.h"

extern ALLEGRO_COLOR COLOR_MAIN_BG;
extern ALLEGRO_COLOR COLOR_MAIN_FONT;
extern ALLEGRO_COLOR COLOR_INPUT_BG;
extern ALLEGRO_COLOR COLOR_INPUT_BG_ACTIVE;
extern ALLEGRO_COLOR COLOR_INPUT_FONT;
extern ALLEGRO_COLOR COLOR_INPUT_BORDER;
extern ALLEGRO_COLOR COLOR_INPUT_BORDER_ACTIVE;
extern ALLEGRO_COLOR COLOR_BUTTON_BG;
extern ALLEGRO_COLOR COLOR_BUTTON_FONT;
extern ALLEGRO_COLOR COLOR_BUTTON_ALT_BG;
extern ALLEGRO_COLOR COLOR_BUTTON_ALT_FONT;
extern ALLEGRO_COLOR COLOR_VIEW_BG;
extern ALLEGRO_COLOR COLOR_VIEW_FONT;
extern ALLEGRO_COLOR COLOR_VIEW_ALT_BG;
extern ALLEGRO_COLOR COLOR_VIEW_ALT_FONT;


extern ALLEGRO_MOUSE_STATE mouse;


/* This function takes mouse x,y coordinates and rounds them to the nearest character at which to place the cursor!
 * It's genius, I know...
*/
int ts_find_nearest_text_char(ALLEGRO_USTR*, int*, ALLEGRO_FONT*, int, int);


// @TODO: The TS_META struct belongs in some kind of "helper" file, but i'm leaving it here for now.

/* This is how you pass info around for drawing objects to screen later on, etc. */
struct TS_META {
	int x;
	int y;
	int z;
	int r1, r2;
	int g1, g2;
	int b1, b2;
	int width;
	int height;
};




/* A good old fashioned text input field, set to any dimensions you please! */

class TS_TXTINPUT {
	public:
		ALLEGRO_BITMAP* bmp;
		ALLEGRO_COLOR font_color;
		ALLEGRO_COLOR bg_color;
		ALLEGRO_USTR* value;
		TS_HOTSPOT hs;
		TS_META meta;
		int offset_clip;
		int* char_w;		// Width of each character in px
		int cursor_pos;		// Cursor position index
		int pixel_pos;		// Current place to draw next character
		int maxlen;			// Max length of characters. Unlimited = 0 (default)
		bool active;
		bool disabled;

		TS_TXTINPUT();
		TS_TXTINPUT(int, int);
		int init(int, int);
		TS_TRIGGER tick(ALLEGRO_FONT*, ALLEGRO_EVENT*);	// The main logic routine
		void draw(ALLEGRO_FONT*);
		void move_cursor(ALLEGRO_FONT*, int);		// Place the cursor at int index
		void update_char_w(int);

	private:
		ALLEGRO_USTR* value_clip;
		ALLEGRO_USTR* current_char;
		int caret_blink;				// If caret_blink is more than zero, it will blink!
		int caret_blink_counter;		// Used for counting cycles between caret blinks.
		bool caret_visible;				// Switches true/false and is checked during the drawing routine.

};


#endif // TS_GUI_TXTINPUT_H


