#ifndef TS_HELPER_TRIGGER_H
#define TS_HELPER_TRIGGER_H

/*
 * This file doesn't have or need a companion .cpp file
 * It's just an enum definition, at least for the time being...
 * Should I switch to the .hpp naming convention? For this, but the other header files too? Hmm... maybe later.
*/

enum TS_TRIGGER {
	TRIGGER_NULL,		// Nothing happened
	TRIGGER_TABINDEX,	// For switching between TS_HOTSPOT objects or any other element
	TRIGGER_SUBMIT,		// For whenever something needs to be processed or submitted within the program
	TRIGGER_FOCUS,		// For giving an element mouse/keyboard focus
	TRIGGER_BLUR,		// For when an element loses any kind of focus it previously had
	TRIGGER_ESCAPE		// For handling ALLEGRO_KEY_ESCAPE presses in different situations
};

/*
struct TS_TRIGGER {
	TS_TRIGGER();
	~TS_TRIGGER();
	int t;
};
*/

#endif // TS_HELPER_TRIGGER_H
