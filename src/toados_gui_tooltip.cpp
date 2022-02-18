#include "toados_gui_tooltip.h"

/*
enum TS_TOOLTIP_SPROUT { TS_TOOLTIP_SPROUT_FADE, TS_TOOLTIP_SPROUT_INSTANT, TS_TOOLTIP_SPROUT_ZOOM };

struct TS_GUI_TOOLTIP {

	TS_GUI_TOOLTIP();

	bool sprout(TS_TOOLTIP_SPROUT);
	void draw();

	ALLEGRO_USTR* text;
	int x;
	int y;
	int w;
	int h;
	int delay_ticks;			// How many ticks (in milliseconds) after its activated for it to become VISIBLE and "sprout"?
	int sprout_ticks;			// The length of time for any fade-out effect to elapse
	bool visible;
};
*/


TS_GUI_TOOLTIP::TS_GUI_TOOLTIP() {
	visible = false;
	tick_delay = 500; // ideally 500ms, for example
}
