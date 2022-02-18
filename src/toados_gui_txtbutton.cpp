#include "toados_config.h"
#include "toados_gui_txtbutton.h"



TS_TXTBUTTON::TS_TXTBUTTON() {
	active = false;
}


int TS_TXTBUTTON::load(char* _text) {

	button_text = _text;

	padding_w = 0;
	padding_h = 0;
	color_blur = al_map_rgb(255, 255, 255);
	color_focus = al_map_rgb(20, 80, 255);
	color_disabled = al_map_rgb(110, 110, 110);
	bgcolor = al_map_rgb(80, 80, 80);

	return 0;
}


int TS_TXTBUTTON::plot(int _x, int _y) {

	hs.x1 = _x;
	hs.y1 = _y;
	hs.x2 = _x + img_w - 1;
	hs.y2 = _y + img_h - 1;

	return 0;
}



int TS_TXTBUTTON::tick(ALLEGRO_MOUSE_STATE* mouse) {

	/* The logic function ticks every cycle.
	 * It checks the hotspot and handles mouseOver, clicks, all that.
	*/

	if (hotspot_mouseover(&hs, mouse->x, mouse->y)) {
		hotspot_set_flag(&hs, HS_FLAG_MOUSEOVER);
		al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	}

	if (hotspot_mouseout(&hs, mouse->x, mouse->y)) {
		hotspot_set_flag(&hs, HS_FLAG_MOUSEOUT);
		al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	}

	return 0;
}



int TS_TXTBUTTON::draw() {

	if (hs.f1 == HS_FLAG_MOUSEOVER) {
		// Drsw the mouse-over (focus) text version.
//		al_draw_filled_rectangle(hs.x1, hs.y1, hs.x2, hs.y2, bgcolor);
		al_draw_text(font, color_focus, hs.x1 + (120/2) - (padding_w/2), hs.y1 + (padding_h/2), ALLEGRO_ALIGN_CENTER, button_text);
	} else {

		// Drsw the mouse-out (blur) text version...
		al_draw_text(font, color_blur, hs.x1 + (120/2) - (padding_w/2), hs.y1 + (padding_h/2), ALLEGRO_ALIGN_CENTER, button_text);
	}

	return 0;
}



int TS_TXTBUTTON::set_padding(int _w, int _h) {

	/* Initially padding is set to zero px.
	 * In case the user decides to change padding multiple times, we
	 * have to make sure we remove the old padding from hotspot before
	 * updating and adding the new padding.
	*/
	if (padding_w > 0)
		hs.x2 -= padding_w;
	if (padding_h > 0)
		hs.y2 -= padding_h;

	// Update new padding numbers
	padding_w = _w * 2;
	padding_h = _h * 2;

	// Finally, update the hotspot.
	hs.x2 += _w * 2;
	hs.y2 += _h * 2;

	return 0;
}


int TS_TXTBUTTON::set_padding(int _wh) {

	// Make equal padding of width and height
	set_padding(_wh, _wh);

	return 0;
}
