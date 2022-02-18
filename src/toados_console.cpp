#include "toados_console.h"

// TS_LOG_INFO			11
// TS_LOG_GOODNEWS		22
// TS_LOG_WARNING		33
// TS_LOG_ERROR			666

using namespace std;


TS_CONSOLE::TS_CONSOLE() {
	active = false;
	filename = "log.txt";
	console_str = al_ustr_new("");
}

int TS_CONSOLE::init(ALLEGRO_DISPLAY* pt_display) {

	display = pt_display; // Grab the display as memory pointer

	add_entry("[ New ToadOS session has started ]", TS_LOG_GOODNEWS);	// A simple welcome message.

	// Initialize the bitmap...
	console_bmp = al_create_bitmap(al_get_display_width(display), al_get_display_height(display));

	al_set_target_bitmap(console_bmp);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_set_target_bitmap(al_get_backbuffer(display));
	return 0;
}


bool TS_CONSOLE::add_entry(char* entry, int priority) {
	// This function will add the next log entry to console_str, and keep the priority saved for special formatting
	// ... for example GOODNEWS will be bright green, INFO will be white, WARNING is orange, and ERROR is bright red.
	return true; // True. For now...?
}


bool TS_CONSOLE::toggle() {
	// Set up a callback function or something...
	return active = !active;
}


bool TS_CONSOLE::is_active() {
	return active;
}


void TS_CONSOLE::draw() {

	//This will draw the bitmap 50% transparently.
	// WARNING: using LOGIC inside a DRAWING function; These should ordinarily be separated.
	if (active) {
		al_draw_tinted_bitmap(console_bmp, al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 0);
	}

	return;
}


