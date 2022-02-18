#include "toados_config.h"
#include "toados_gui_button.h"



TS_BUTTON::TS_BUTTON() {
	active = false;
}


int TS_BUTTON::load(char* path) {

	img = al_load_bitmap(path);

	img_w = al_get_bitmap_width(img);
	img_h = al_get_bitmap_height(img);
	padding_w = 0;
	padding_h = 0;
	bgcolor = al_map_rgb(80, 80, 80);

	img2 = al_create_bitmap(img_w, img_h);
	al_set_target_bitmap(img2);
	al_draw_tinted_bitmap(img, al_map_rgba_f(1, 1, 1, 0.8), 0, 0, 0);
	al_set_target_bitmap(al_get_backbuffer(display));

	return 0;
}


int TS_BUTTON::plot(int _x, int _y) {

	hs.x1 = _x;
	hs.y1 = _y;
	hs.x2 = _x + img_w - 1;
	hs.y2 = _y + img_h - 1;

	return 0;
}



int TS_BUTTON::tick(ALLEGRO_MOUSE_STATE* mouse) {

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



int TS_BUTTON::draw() {

	if (hs.f1 == HS_FLAG_MOUSEOVER) {
		al_draw_filled_rectangle(hs.x1, hs.y1, hs.x2, hs.y2, bgcolor);
		al_draw_bitmap(img2, hs.x1 + (img_w/2) - (padding_w/2), hs.y1 + (padding_h/2), 0);
	} else {

		// Draw the bitmap, centered within the padding
		al_draw_bitmap(img, hs.x1 + (img_w/2) - (padding_w/2), hs.y1 + (padding_h/2), 0);
	}

	return 0;
}



int TS_BUTTON::set_padding(int _w, int _h) {

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


int TS_BUTTON::set_padding(int _wh) {

	// Make equal padding of width and height
	set_padding(_wh, _wh);

	return 0;
}
