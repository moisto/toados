#include "toados_gui_txtlabel.h"


TS_GUI_TXTLABEL::TS_GUI_TXTLABEL() {
	value = al_ustr_new("");
}

bool TS_GUI_TXTLABEL::load(char* v, int _x, int _y) {

	// @TODO: Load the font somehow. Either pass a pointer or a #define'd FONT_SIZE that knows which font to pick.
	value = al_ustr_new(v);
	hs.x1 = _x;
	hs.y1 = _y;
	// hs.x2 = hs.x1 + al_ustr_get_width(font, value);
	// hs.y2 = hs.y1 + al_ustr_get_height(font, value);

	return true;
}


bool TS_GUI_TXTLABEL::draw() {

//	al_draw_text(...);

	return true;
}


