#include <stdio.h>
#include <iostream>
#include <string>

#define ALLEGRO_STATICLINK
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

//#include "src/toados_globals.h"
#include "src/toados_helper_triggers.h"
#include "src/toados_gui.h"
#include "src/toados_gui_button.h"
#include "src/toados_gui_txtbutton.h"
#include "src/toados_gui_txtinput.h"
#include "src/toados_config.h"
#include "src/toados_console.h"
#include "src/toados_hotspot.h"


// Global system variables
ALLEGRO_COLOR COLOR_MAIN_BG;
ALLEGRO_COLOR COLOR_MAIN_FONT;
ALLEGRO_COLOR COLOR_INPUT_BG;
ALLEGRO_COLOR COLOR_INPUT_BG_ACTIVE;
ALLEGRO_COLOR COLOR_INPUT_FONT;
ALLEGRO_COLOR COLOR_INPUT_BORDER;
ALLEGRO_COLOR COLOR_INPUT_BORDER_ACTIVE;
ALLEGRO_COLOR COLOR_BUTTON_BG;
ALLEGRO_COLOR COLOR_BUTTON_FONT;
ALLEGRO_COLOR COLOR_BUTTON_ALT_BG;
ALLEGRO_COLOR COLOR_BUTTON_ALT_FONT;
ALLEGRO_COLOR COLOR_VIEW_BG;
ALLEGRO_COLOR COLOR_VIEW_FONT;
ALLEGRO_COLOR COLOR_VIEW_ALT_BG;
ALLEGRO_COLOR COLOR_VIEW_ALT_FONT;

std::string CFG_TOOLTIP_ENABLE;
std::string CFG_TOOLTIP_TYPE;

int CFG_TOOLTIP_DELAY;
int CFG_TOOLTIP_SPROUT;
int CFG_TOOLTIP_WILT;







class TS_STR {
	public:
		TS_STR(ALLEGRO_FONT*, int); // Convert columns to width px
		int col;
		int row;
		int wpx;
		int hpx;

	private:

};

TS_STR::TS_STR(ALLEGRO_FONT* f, int c) {
	col = c;
	row = 1;
	hpx = 14;

}



/* These are some global functions and other shit that need a home... */


ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_MOUSE_STATE mouse;
ALLEGRO_FONT* font;
ALLEGRO_FONT* font2_big; // new font
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
const float FPS = 60;
bool redraw = true;


/*
 * For now these images are kept in memory for faster window resizing...
 * but they may just hog space, especially if it only gets resized like once or never.
 * Currently the function ts_create_background(void) is run whenever a resize occurs.
 * The function relies on the following three BITMAPs, especially the last two which
 * are textured patterns that repeat and get clipped as needed.
 * @todo: Look into memory resource management and write some code that destroys the
 * 	resources if it needs the memory, otherwise keep them (faster resize load-time).
*/

ALLEGRO_BITMAP* bmp_background = NULL;	// Compiled background image made from Patterns 1 and 2
ALLEGRO_BITMAP* bmp_bg1 = NULL;			// Pattern 1
ALLEGRO_BITMAP* bmp_bg2 = NULL;			// Pattern 2



ALLEGRO_BITMAP* bmp_watermark = NULL;	// A text watermark for displaying version info or anything else.


// MARGIN CLIPPING BOX
int MARGIN_X1 = 140;
int MARGIN_Y1 = 70;
int MARGIN_X2 = 0;
int MARGIN_Y2 = 50;

//
// @todo: write a text to bitmap function
// ALLEGRO_BITMAP* ts_create_text_to_bitmap("Hi, I'm much faster to draw as a BITMAP rather than TTF text!");
//

void ts_create_watermark(char* text) {
	// This function will be deprecated by or make use of the ts_create_text_to_bitmap() function.
	// The watermark in my case is just a short string of text anyways.
	int bbw;	// The text width
	int bbh;	// ... and its height
	int bbx; // The true bounding box offset for x
	int bby; // ... and for y

	al_get_text_dimensions(font, text, &bbx, &bby, &bbw, &bbh);

	bmp_watermark = al_create_bitmap(bbw + bbx, bbh + bby);

	al_set_target_bitmap(bmp_watermark);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));

	al_draw_text(font, al_map_rgb(200, 200, 200), 0, 0, 0, text);

	// Back to normal display drawing mode.
	al_set_target_bitmap(al_get_backbuffer(display));

	return;
}


int ts_create_background() {

	int margin_x = MARGIN_X1;
	int margin_y = MARGIN_Y1;

	bmp_background = al_create_bitmap(al_get_display_width(display), al_get_display_height(display));

	if (bmp_bg1 == NULL)
		bmp_bg1 = al_load_bitmap("data/img/backgrounds/bg_black_striped.png");
	if (bmp_bg2 == NULL)
		bmp_bg2 = al_load_bitmap("data/img/backgrounds/bg_white_grid.png");


	al_set_target_bitmap(bmp_background);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	// Draw the main background pattern.
	for (int i = 0; i < al_get_bitmap_width(bmp_background); i += al_get_bitmap_width(bmp_bg1)) {
		for (int j = 0; j < al_get_bitmap_height(bmp_background); j += al_get_bitmap_height(bmp_bg1)) {
			al_draw_bitmap(bmp_bg1, i, j, 0);
		}
	}

	al_set_clipping_rectangle(margin_x, margin_y, MARGIN_X2, al_get_display_height(display) - 130);

	// Draw the main content window background.
	for (int i = margin_x; i < al_get_bitmap_width(bmp_background); i += al_get_bitmap_width(bmp_bg2)) {
		for (int j = margin_y; j < al_get_bitmap_height(bmp_background); j += al_get_bitmap_height(bmp_bg2)) {
			al_draw_bitmap(bmp_bg2, i, j, 0);
		}
	}


	al_reset_clipping_rectangle();
	al_set_target_bitmap(al_get_backbuffer(display));

	return 0;
}

/* End of global stuff */






/*
 * NEXT UP, A TEMPORARY ISBN READER / VIEWER... FOR DEMONSTRATION USE **ONLY**
 *
*/


struct TS_INVENTORY {

	TS_INVENTORY();
	std::string isbn_list;


};


int ts_load_isbn_file(char* path) {

	return 0;
}



using namespace std;

int main(int argc, char* argv[]) {


	/*
	 * @todo: Fix the "font" issue. I need more than one font in one size. Get
	 *  that 3d ALLEGRO_FONT* array working so i can do stuff like 'font[SANS][SM]'
	 *
	 * @todo: Build SEARCH BAR at top of screen!!
	 *
	 * @todo: Finish implementing the design. It looks good in AI, now make it real.
			- Everything translucent should be at 55% opacity/alpha
			- Headers with large text and green/red/blue/grey translucent background
				- Green: al_map_rgba(0, 212, 29, 0.55)	#00d41d
				- Red: al_map_rgba(255, 92, 42, 0.55)	#ff5c2a
				- Blue: al_map_rgba(63, 106, 255, 0.55)	#3f6aff
				- Grey: al_map_rgba(0, 0, 0, 0.55)		#000000

			- Build a welcome screen with news (local and/or from toados.com)
				- Click on the toados logo to reload or visit at any time.

			- Finish adding buttons to main menu
				- Add the button text colors
					- mouseover	al_map_rgba(29, 191, 0, 1)		#1dbf00 // GREEN
					- mouseout	al_map_rgba(255, 255, 255, 1)	#ffffff
					- active	al_map_rgba(21, 80, 255, 1)		#1550ff // BLUE
					- disabled	al_map_rgba(151, 151, 151, 1)	#979797
				- Add sweeping black-tinted bar to menu items, slightly lags behind mouse (for effect)

	 *
	 * @todo: Organize my code! Things are starting to get a little dirty
	 *  in here, especially main.cpp and the launch process. Also there
	 *  are too many globals, and they're starting to drift.
	 *
	 * @todo: Build a sweet splash screen with a loading bar.
	 * @todo: Have a few different sizes of splash screen ready for low/high res screens
	 *
	 * The splash can be disabled under preferences, but will be on by default.
	 * Before/During the splash, allegro attempts to load everything.
	 * 		1. Load Allegro itself
			2. Create display
			3. Check for keyboard
			4. Check for mouse
			5. Load the event handler
			6. Initialize the allegro addons
				- font
				- ttf
				- image
				- primitives
				- ???
			7. Load the font resources
			8. Check for local .toad setting files
				- If no settings file found then WARN user via popup and continue by running built-in default settings
				- Ask to look elsewhere for settings file
				- Ask to save the built-in settings to default text file location (to fix this missing file error)
			9. Check sound card (keep silent unless instructed to beep or play sound in the settings file)
			10. Load all the image resources
			11. Check LAN status
				- Identify self
				- Locate "backroom" server
				- Track LAN satellites, request handshake and connect
			12. Check internet connection
				- Locate toados.com server
					- If DNS lookup fails, try dedicated toados.com IP instead.
					- Identify self
					- Request handshake with the other store servers (WAN)
	*/


	if(!al_init()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}


	/*
	 * These two flags are both required to make the window resizable.
	 * @todo: Start the program off with a different flag FULLSCREEN_WINDOW (or look into it some more)
	 * @todo: Learn how to mash the flags together into one "flags" int
	*/
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	/*
	 * This function is only available in Allegro 5.1 or higher. I'm using current stable branch 5.0.1 right now.
	al_set_window_constraints(display, 300, 400, 0, 0); // min width and height, then max. Zero means no constraint.
	 *
	*/

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();

	font = al_load_font("data/fonts/calibri.ttf", 16, 0);
	font2_big = al_load_font("data/fonts/greyscale_bold_italic.ttf", 30, 0);
//	font = al_load_font("data/fonts/calibri.ttf", 16, 0);
//	font = al_load_font("data/fonts/Cousine_Regular.ttf", 16, 0);
	display = al_create_display(900, 720);

	//ts_load_font(TS_FONT_FACE_SANS, "data/fonts/Berylium.ttf", 12, 16, 28);

	if(!display) {
		fprintf(stderr, "Failed to create display!\n");
		return -1;
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "Failed to initialize the keyboard!\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "Failed to initialize the mouse!\n");
		return -1;
	}


	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}


	event_queue = al_create_event_queue();

	if (!event_queue) {
		fprintf(stderr, "Failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	ts_load_config("toad-settings/default-color-scheme.toad");


	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();


	al_set_window_title(display, "Main - toadOS");



	ALLEGRO_BITMAP* bmp_tslogo;
	bmp_tslogo = al_load_bitmap("data/img/logo_toados_110.png");

	TS_CONSOLE console;
	console.init(display);

	TS_TXTINPUT inputField(MARGIN_X2 - 152, 22); // 22 is just the constant height of Search box
	/*
	@todo Fix the TS_TXTINPUT bounding box drawing problem, among other things.
	@todo Track the LEFT/RIGHT/UP/DOWN arrow keys, to navigate through text boxes
	*/

	/*
	@todo Create HOTSPOTs that detect mouse-over and click events, in addition they will manage tabindex like in HTML.
			Each HOTSPOT will be passed a memory pointer to any TSGUI object, for now that's just TS_TXTINPUT but soon
			it will include TS_BUTTON and all the rest!
	*/

	TS_TXTBUTTON menu_btn_one;
	TS_TXTBUTTON menu_btn_two;
	TS_TXTBUTTON menu_btn_three;
	TS_TXTBUTTON menu_btn_four;
	menu_btn_one.load("point of sale");
	menu_btn_one.plot(5, 100);
	//menu_btn_one.set_padding(20, 5);

	menu_btn_two.load("lookup");
	menu_btn_two.plot(5, 140);

	menu_btn_three.load("reports");
	menu_btn_three.plot(5, 180);

	menu_btn_four.load("settings");
	menu_btn_four.plot(5, 220);


	TS_BUTTON btn_www;
	btn_www.load("data/img/gui/btn_search_16.png");
	btn_www.plot(20, 50);
	btn_www.set_padding(4);

	TS_BUTTON btn_menu_lookup;
	btn_menu_lookup.load("data/img/toadstool_80.png");
	btn_menu_lookup.plot(0, 0);
	btn_menu_lookup.set_padding(20, 5);//w = 120; // TODO: Make a function to resize width or height.

	TS_BUTTON btn_menu_checkout;
	btn_menu_checkout.load("data/img/settings2_80.png");
	btn_menu_checkout.plot(0, 90);
	btn_menu_checkout.set_padding(20, 5);//w = 120; // TODO: Make a function to resize width or height.

	TS_BUTTON btn_menu_reports;
	btn_menu_reports.load("data/img/reports_80.png");
	btn_menu_reports.plot(0, 180);
	btn_menu_reports.set_padding(20, 5);//w = 120; // TODO: Make a function to resize width or height.

	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	ALLEGRO_BITMAP* icons[3];
	icons[0] = al_load_bitmap("data/img/tslogo_16.png");
	icons[1] = al_load_bitmap("data/img/tslogo_32.png");
	icons[2] = al_load_bitmap("data/img/tslogo_64.png");

	al_set_display_icons(display, 3, icons);


	// TS_GUI gui;
	// gui.init("ToadOS", 800, 600);
	// while (gui.active) {


	TS_HOTSPOT hotspot[20];

	hotspot_create(&hotspot[0], 200, 200, 352, 222);


	// When the program starts, or when the window gets resized we must call this function!
	ts_create_background();

	// Build and save the watermark bitmap for drawing later.
	ts_create_watermark("toados build 0.0.4.323 (alpha)");


	//timer = al_create_timer(1.0 / 60);


//	al_set_display_flag(display, ALLEGRO_FRAMELESS, true);

/*
	UX Idea:
	SCROLLBAR LIKE SUBLIME TEXT
		- Grab the display/content bitmap and scale it down.
		- Draw a smooth looking scrollbar on the right side of screen
		- Place the full-length content bitmap at the top of scrollbar, just like in sublime text.
*/

	ALLEGRO_BITMAP* header_bg_green = al_create_bitmap(2000, 50);
	al_set_target_bitmap(header_bg_green);
	al_clear_to_color(al_map_rgb(0, 212, 29));
	al_set_target_bitmap(al_get_backbuffer(display));


	al_flip_display();
	al_start_timer(timer);

	bool uglyhack = true;

	while(1) {

      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);


//		ALLEGRO_TIMEOUT timeout;
//		al_init_timeout(&timeout, 0.06);
//		bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);				ts_create_background(); // rebuild the background as needed.


		al_get_mouse_state(&mouse);

		//if (get_event) {

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}

			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				break;

			if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE || uglyhack) {
				uglyhack = false;
				al_acknowledge_resize(display);
				MARGIN_X2 = al_get_display_width(display) - MARGIN_X1 - 90; // Window/Header WIDTH
				MARGIN_Y2 = 50; // set height of header

				ts_create_background();

				// ugly hack
				inputField.meta.x = MARGIN_X2 - 152;

				redraw = true;
			}


			/*
			 * This bit is the original quake-style dropdown console code i wrote in the beginning. Ignore for time being.
			if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				if (ev.keyboard.keycode == ALLEGRO_KEY_TILDE)
					console.toggle();
			}
			*/



			if (hotspot_mouseover(&hotspot[0], mouse.x, mouse.y)) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_EDIT);
			}

			if (hotspot_mouseout(&hotspot[0], mouse.x, mouse.y)) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			}

			if (mouse.buttons & 1 && hotspot[0].f1 == HS_FLAG_MOUSEOVER) {
				inputField.move_cursor(font, ts_find_nearest_text_char(inputField.value, inputField.char_w, font, inputField.meta.x, inputField.meta.y));
			}

			menu_btn_one.tick(&mouse);
			menu_btn_two.tick(&mouse);
			menu_btn_three.tick(&mouse);
			menu_btn_four.tick(&mouse);

			//btn_menu_reports.tick(&mouse);
			//btn_menu_checkout.tick(&mouse);
			//btn_menu_lookup.tick(&mouse);

			// Check for console.
			if (console.is_active()) {
				// handle keyboard events or whatever else for the console.
			} else {
				if (inputField.tick(font, &ev) == TRIGGER_SUBMIT)
					while (1) {};

			}

      //}





		// Draw to screen ONLY when ready!
		if(redraw && al_is_event_queue_empty(event_queue)) {

			// Only draw things when the system has nothing else to do...

			redraw = false; // reset the variable back to false

			// Set target back to display
			//al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(80, 80, 80));

			//////////////////////////////

			// [OLD] Draw the background stuff...

			// The main menu background
			// al_draw_filled_rectangle(0, 0, 120, al_get_display_height(display), al_map_rgb(40, 40, 40));

			// The bottom statusbar background
			// al_draw_filled_rectangle(0, al_get_display_height(display) - 30, al_get_display_width(display), al_get_display_height(display), al_map_rgb(100, 100, 100));


			al_draw_bitmap(bmp_background, 0, 0, 0);
			/*----------------------------------------*/

			// DRAW THE HEADER AND A GREEN BACKGROUND
			al_set_clipping_rectangle(MARGIN_X1, MARGIN_Y1, MARGIN_X2, 50);
			al_draw_tinted_bitmap(header_bg_green, al_map_rgba_f(0.5, 0.5, 0.5, 0.55), MARGIN_X1, MARGIN_Y1, 0);
			al_reset_clipping_rectangle();

			// DRAW HEADER TEXT
			al_draw_text(font2_big, al_map_rgb(40, 40, 40), MARGIN_X2 + 140 - 10, MARGIN_Y1 + 12, ALLEGRO_ALIGN_RIGHT, "Welcome to the new system.");

			al_draw_text(font, al_map_rgb(40, 40, 40), MARGIN_X1 + 10, MARGIN_Y1 + 50 + 10, 0, "It's been a long time comin' and it's *still* not ready");


			inputField.draw(font); // Draws onto the separate bitmap

			menu_btn_one.draw();
			menu_btn_two.draw();
			menu_btn_three.draw();
			menu_btn_four.draw();

			//btn_www.draw();
			//btn_menu_lookup.draw();
			//btn_menu_checkout.draw();
			//btn_menu_reports.draw();

			//console.draw();

			//////////////////////////////

			// Draw the ToadOS logo thing
			//al_draw_tinted_bitmap(bmp_tslogo, al_map_rgba(255, 255, 255, 1.0), 5, 5, 0);
			al_draw_bitmap(bmp_tslogo, 5, 5, 0);

			//////////////////////////////

			// Lastly draw the text and images that go on top of everything else

			// Draw the text labels and headers for the current MODE.
			//al_draw_text(font, COLOR_MAIN_FONT, al_get_display_width(display) - 2, al_get_display_height(display) - 25, ALLEGRO_ALIGN_RIGHT, "ToadOS alpha [blackbetty]");

			al_draw_bitmap(bmp_watermark, al_get_display_width(display) - 200, al_get_display_height(display) - 25, 0);


			al_flip_display();
		}


	}



	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

