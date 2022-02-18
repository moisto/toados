#ifndef TOADOS_H_CONSOLE
#define TOADOS_H_CONSOLE

#include <stdio.h>
#include <fstream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"


#define TS_LOG_INFO			11
#define TS_LOG_GOODNEWS		22
#define TS_LOG_WARNING		33
#define TS_LOG_ERROR		666

enum TS_STATUS {TS_STAT_NORMAL, TS_STAT_GOODNEWS, TS_STAT_WARNING, TS_STAT_ERROR};


class TS_CONSOLE {
	public:
		TS_CONSOLE();					// Default constructor, set up some defaults, etc.
		bool toggle();					// Show or hide the console window
		bool is_active();				// Check if console window is active
		bool add_entry(char*, int);		// Add a new entry
		bool save_output(int);			// Save the session to filename. (1) = append, (2) = overwrite
		void draw();					// Draw the console window
		int exec();						// Execute the logic cycle
		int init(ALLEGRO_DISPLAY*);		// Once everything else is running, we'll set up the console!


	private:
		ALLEGRO_DISPLAY* display;		// Pointer to the display gets passed in during init()
		ALLEGRO_FONT* console_font;		// A simple mono-spaced should do nicely.
		ALLEGRO_BITMAP* console_bmp;	// The console bitmap! We're gonna draw all over you... YEAAAH!
		ALLEGRO_USTR* console_str;		// The entire session's console output including newlines, etc.
		char* filename;					// Path to save the logfile/console output
		bool active;					// Console active flag
};

#endif // TOADOS_H_CONSOLE
