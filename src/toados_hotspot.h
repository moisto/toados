#ifndef TS_HOTSPOT_H
#define TS_HOTSPOT_H

enum HS_FLAG {
	HS_FLAG_NULL,			// Nothing at all
	HS_FLAG_INACTIVE,
	HS_FLAG_MOUSEOVER,
	HS_FLAG_MOUSEOUT,
	HS_FLAG_MOUSEDOWN,
	HS_FLAG_MOUSEUP,
	HS_FLAG_MOUSECLICK,
	HS_FLAG_DOUBLECLICK,
	HS_FLAG_ACTIVE
};

struct TS_HOTSPOT {
	TS_HOTSPOT();
	int x1;
	int y1;
	int x2;
	int y2;
	int ti;	// Tab Index
	bool active;	// Do not confuse with 'bool visible'! Set to true when you want the parent element to gain user focus.
	bool visible;	// Set to false when parent object is no longer on screen or whenever you want to disable something
	HS_FLAG f1;		// Hotspot Flag 1
	HS_FLAG f2;		// Hotspot Flag 2 (this one stores the previous state of f1)
};


void hotspot_set_flag(TS_HOTSPOT*, HS_FLAG);
void hotspot_create(TS_HOTSPOT*, int, int, int, int);
bool hotspot_mouseover(TS_HOTSPOT*, int, int);
bool hotspot_mouseclick(TS_HOTSPOT*, int, int);
bool hotspot_mouseout(TS_HOTSPOT*, int, int);
int hotspot_active(TS_HOTSPOT*);




#endif // TS_HOTSPOT_H
