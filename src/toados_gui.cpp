#include "toados_gui.h"


TS_GUI::TS_GUI() {
	display = NULL;
	event_queue = NULL;
	title = "";
	active = false;
}


int TS_GUI::init(char* t, int _w, int _h) {

	set_window_title(t);
	width = _w;
	height = _h;
	active = true;

	return 0;
}



ALLEGRO_EVENT* TS_GUI::status() {

	// Pre-shit
	al_init_timeout(&timeout, 0.06);

	return &ev;
}


int TS_GUI::draw() {

	// Set target back to display
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	return 0;
}


int TS_GUI::quit() {

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

void TS_GUI::set_window_title(char* t) {

	title = t;
	al_set_window_title(display, t);

	return;
}
