/* This "globals" file is where I put everything that can be reached from a global scope.
 * I'm not a fan of global variables (I find them messy and/or unnecessary at times).
 * But with a project this size, I've realized global variables actually make things *less* messy.
 * Instead of passing a thousand pointers along every function, I can simply access them directly
 * which should result in neater code.
 * If I remain vigilant... there will be no security risks... only crisper, cleaner code.
 * Cross your fingers.
*/

#ifndef TOADOS_GLOBALS_H
#define TOADOS_GLOBALS_H


#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"


enum TS_FONT_SIZE {
	TS_FONT_SIZE_S = 0,
	TS_FONT_SIZE_M = 1,
	TS_FONT_SIZE_L = 2
};

enum TS_FONT_TYPE {
	TS_FONT_TYPE_REG = 0,
	TS_FONT_TYPE_BOLD = 1,
	TS_FONT_TYPE_ITALIC = 2
};

enum TS_FONT_FACE {
	TS_FONT_FACE_SANS = 0,
	TS_FONT_FACE_MONO = 1,
	TS_FONT_FACE_SERIF = 2
};



//ALLEGRO_FONT* font[3][3]; // font[family][size]

/* Specify the font face (sans, mono, serif), the font filename, and then three sizes.
 * This allows a total of 9 fonts.
 * Font styles like bold/italic are not supported, but you can load the bold version of a font
 * under a different FONT_FACE and access it that way if you really want.
*/
bool ts_load_font(int, char*, int, int, int);


#endif // TOADOS_GLOBALS_H
