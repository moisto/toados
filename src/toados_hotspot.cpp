#include "toados_hotspot.h"


TS_HOTSPOT::TS_HOTSPOT() {
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	ti = 0; // Initial tab index set to zero, which means "no preference"
	active = false; // Only one HOTSPOT "can" be active at a time. So default is set to false (i.e. does not have user input focus)
	visible = true; // Visible means the hotspot's element is visible on
	f1 = HS_FLAG_INACTIVE;
	f2 = HS_FLAG_NULL; // Has been set to INACTIVE until now, so if things break revert the change.
}

void hotspot_set_flag(TS_HOTSPOT* hs, HS_FLAG nf) {
	hs->f2 = hs->f1; // save current flag state for reference later, to determine how they connect and what it means.
	hs->f1 = nf; // new flag
}

void hotspot_create(TS_HOTSPOT* hs, int _x1, int _y1, int _x2, int _y2) {

	hs->x1 = _x1;
	hs->y1 = _y1;
	hs->x2 = _x2;
	hs->y2 = _y2;

	return;
}

bool hotspot_mouseclick(TS_HOTSPOT* hs, int mx, int my) {

	if (hs->f1 == HS_FLAG_MOUSEOVER) {
		if ((mx >= hs->x1 && mx <= hs->x2) && (my >= hs->y1 && my <= hs->y2)) {
			hs->f2 = hs->f1; // save previous flag
			hs->f1 = HS_FLAG_MOUSECLICK;
			return true;
		}
	}

	return false;
}

bool hotspot_mouseover(TS_HOTSPOT* hs, int mx, int my) {

	if (hs->f1 != HS_FLAG_MOUSEOVER || hs->f2 == HS_FLAG_MOUSEOVER) {
		if ((mx > hs->x1 && mx < hs->x2) && (my > hs->y1 && my < hs->y2)) {
			hs->f2 = hs->f1; // save previous flag
			hs->f1 = HS_FLAG_MOUSEOVER;
			return true;
		}
	}

	return false;
}

bool hotspot_mouseout(TS_HOTSPOT* hs, int mx, int my) {

	if (hs->f1 == HS_FLAG_MOUSEOVER) {
		if ((mx > hs->x1 && mx < hs->x2) && (my > hs->y1 && my < hs->y2)) {
			return false;
		} else {
			hs->f2 = hs->f1; // save previous flag
			hs->f1 = HS_FLAG_MOUSEOUT;
			return true;
		}
	}

	return false;
}

int hotspot_active(TS_HOTSPOT* hs) {
	return hs->f1 == HS_FLAG_ACTIVE;
}
