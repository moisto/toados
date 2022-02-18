#ifndef TOADOS_GUI_TXTLABEL_H
#define TOADOS_GUI_TXTLABEL_H

#include "allegro5/allegro.h"

#include "toados_hotspot.h"

class TS_GUI_TXTLABEL {

	TS_GUI_TXTLABEL();
	bool load(char*, int, int);
	HS_FLAG tick();		/* If you just want to draw the text, you don't need to run the tick() function.
						 * Running tick() will run through the hotspot functions and return mouse info.
						*/
	bool draw();


	TS_HOTSPOT hs;
	ALLEGRO_USTR* value;
};


#endif // TOADOS_GUI_TXTLABEL_H
