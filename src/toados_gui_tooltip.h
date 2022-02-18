#ifndef TOADOS_GUI_TOOLTIP_H
#define TOADOS_GUI_TOOLTIP_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include "toados_console.h"

/* This is the standard GUI tooltip which is quite beautiful.
 * It takes a custom font, and is drawn with a rounded rectangle.
 * The x,y is the position where it should "sprout". Depending on
 * width and height of tooltip text, this point leads in a triangular
 * pitch outwards towards the rectangle, like a speech bubble.
 * To make sure the whole tooltip is visible, the sprout point may
 * draw the tooltip in a dynamic position relative to display edges.
 * CUSTOMIZE: The triangle cone is on by default, but you can turn
 * it off if you just want the rectangular box
 */

extern TS_CONSOLE console;

enum TS_TOOLTIP_SPROUT {
	TS_TOOLTIP_SPROUT_INSTANT,	// 0 = no fancy effect, just appear.
	TS_TOOLTIP_SPROUT_FADE,		// 1 = fade in effect
	TS_TOOLTIP_SPROUT_ZOOM		// 2 = zoom in / zoom out effect
};

struct TS_GUI_TOOLTIP {

	TS_GUI_TOOLTIP();

	bool sprout(TS_TOOLTIP_SPROUT);		// Specify how the tooltip behaves
	bool wilt(TS_TOOLTIP_SPROUT);		// Specify how the tooltip disappears
	void tick();						// This function runs on every logic cycle
	void draw();						// Draw (or not) the tooltip

	ALLEGRO_USTR* text;
	TS_TOOLTIP_SPROUT sprout_in;	// FADE IN EFFECT (if any)
	TS_TOOLTIP_SPROUT sprout_out;
	int x;
	int y;
	int w;
	int h;
	int tick_delay;				// How many ticks after its activation for it to become VISIBLE
	int tick_sprout;			// The length of time for any fade-out effect to elapse
	int tick_wilt;				// How many ticks for the tooltip to fully disappear.
	bool visible;
};


#endif // TOADOS_GUI_TOOLTIP_H
