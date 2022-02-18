#include <iostream>
#include "toados_gui_txtinput.h"





void update_cell_widths(int*, int);

void update_cell_widths(int* cwidth, int pos) {

	for (int i = pos; i < sizeof(cwidth) - 1; i++) {
		cwidth[i] = cwidth[i+1];
	}

	return;
}



void TS_TXTINPUT::update_char_w(int pos) {

	int len = al_ustr_length(value);

//	ALLEGRO_USTR* temp = al_ustr_new("");


	for (int i = pos; i < len - 1; i++)
		char_w[i] = char_w[i+1];
//		char_w[i] = al_get_ustr_width(font, value[i]);
	return;
}



int ts_get_pixel_width(int*, int, int); // pointer, start, end

int ts_get_pixel_width(int* range, int pos_begin, int pos_end) {

	int w = 0; // initialize width (return variable) to zero

	for (int i = pos_begin; i < pos_end; i++) {
		w += range[i];
	}

	return w;
}


/* Function used in TS_TXTINPUT class.
 * It evaluates an int array against a string and syncs the character widths for cursor navigation and pixel placement.
*/

int ts_find_nearest_text_char(ALLEGRO_USTR* str, int* char_w, ALLEGRO_FONT* f, int x, int y) {

	int width = al_get_ustr_width(f, str);
	int len = al_ustr_length(str);

	// If the Mouse (click) x-axis is beyond the string itself...
	if (mouse.x >= x + width)
		return len; // ...then the nearest char position would be the very last.

	// Prevent division by zero
	if (len == 0)
		len = 1;


	x = mouse.x - x;

	int rval = 0;
	int cpx = 0;
	for (int i = 0; i < len; i++) {
		cpx += char_w[i];
		if (cpx < x)
			rval++;
	}


	return rval;
}




TS_TXTINPUT::TS_TXTINPUT() {
	init(0, 0);
}

TS_TXTINPUT::TS_TXTINPUT(int _x, int _y) {
	init(_x, _y);
}

int TS_TXTINPUT::init(int _x, int _y) {

	cursor_pos = 0;
	pixel_pos = 0;		// THINK OF THIS AS "INPUT_POS" (rename variable you lazy fuck)
	caret_blink = 10;
	caret_blink_counter = 0;
	caret_visible = true;
	char_w = new int[255];
	maxlen = 0;					// Unlimited if set to zero

	for (int i = 0; i < 255; ++i) {
		char_w[i] = 0;
	}

	value = al_ustr_new("");
	current_char = value;
	value_clip = value;
	offset_clip = 0;

	meta.x = _x;
	meta.y = _y;
	// @TODO: setup a global DEFAULT META to use for loading color schemes, etc.
	// FOR NOW: manually set the TS_META to some defaults...
	meta.r1 = 30;
	meta.g1 = 30;
	meta.b1 = 140;
	meta.r2 = 80;
	meta.g2 = 80;
	meta.b2 = 80;
	meta.width = 152;
	meta.height = 22;


//	font_color = al_map_rgb(meta.r1, meta.g1, meta.b1);
//	bg_color = al_map_rgb(meta.r2, meta.g2, meta.b2);
	font_color = COLOR_INPUT_FONT;
	bg_color = COLOR_INPUT_BG;

	bmp = al_create_bitmap(meta.width, meta.height);


	// change target bitmap to draw here instead.
	al_set_target_bitmap(bmp);
	al_clear_to_color(COLOR_INPUT_BG);
	al_draw_rectangle(1, 1, meta.width, meta.height, COLOR_INPUT_BORDER, 1); // Next draw the border

	return 0;
}



void TS_TXTINPUT::move_cursor(ALLEGRO_FONT* font, int c) {
/*
	ALLEGRO_USTR* temp = value;

	al_ustr_assign_substr(temp, value, 0, c);

	cursor_pos = c;
	pixel_pos = al_get_ustr_width(font, temp);
*/

	cursor_pos = c;
	pixel_pos = ts_get_pixel_width(char_w, 0, cursor_pos);

/*	int _calcw = 0; // initialize width (return variable) to zero

	for (int i = pos_begin; pos_begin < pos_end; i++) {
		_calcw += range[i];
	}
*/
	return;
}




/*
	The main event manager for text input fields
*/
TS_TRIGGER TS_TXTINPUT::tick(ALLEGRO_FONT* font, ALLEGRO_EVENT* ev) {

	// Handle the caret blink logic
	if (caret_blink_counter < caret_blink)
		caret_blink_counter++;
	else {
		caret_blink_counter = 0;
		caret_visible = !caret_visible;
	}


	if (ev->type == ALLEGRO_EVENT_KEY_CHAR) {


		switch (ev->keyboard.keycode) {
			case ALLEGRO_KEY_TAB:
				// For now, tab only switches focus to next element (a feature which still doesn't exist)
				// Ideally, there should be the option to treat TAB as a character.
				return TRIGGER_TABINDEX;
				break;

			case ALLEGRO_KEY_ESCAPE:
				//return TRIGGER_TAB;
				break;

			case ALLEGRO_KEY_LEFT:
				if (cursor_pos > 0) {
					--cursor_pos;
					pixel_pos -= char_w[cursor_pos];
				}
				break;

			case ALLEGRO_KEY_RIGHT:
				if (cursor_pos < al_ustr_length(value)) {
					++cursor_pos;
					ALLEGRO_USTR* temp;

				//	char_w[cursor_pos] =
				//	al_get_ustr_width(font, current_char);
					pixel_pos = al_get_ustr_width(font, value);
				}

				break;

			default:
				break;
		}


		// @TODO: Insert DELETE functionality, similar to BACKSPACE.

		if (ev->keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
			if (cursor_pos > 0) {
				cursor_pos--;
				al_ustr_remove_chr(value, cursor_pos);
				pixel_pos -= char_w[cursor_pos];
			}
		} else if (ev->keyboard.keycode == ALLEGRO_KEY_DELETE) {
			if (cursor_pos < al_ustr_length(value)) {

			}

		} else if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER) {

			// @TODO: Make the ENTER key send a SUBMIT signal
			// @todo: Allow support for multiline input boxes by adding a NEWLINE and repositioning caret to next line.

			return TRIGGER_SUBMIT;

		} else {
			// @todo: (DONE) Figure out a good way to IGNORE the Fn keys, they're adding GARBAGE whitespace to the value.
			//al_ustr_assign_cstr(current_char, ev->keyboard.unichar);

			// If an "actual" character was pressed, let's add it to the string. This prevents garbage keys from being added.
			if (ev->keyboard.unichar != 0) {

				current_char = al_ustr_new(""); // Clear the spaghetti-code variable, which should only be one character long.

				// Grab the current key
				al_ustr_append_chr(current_char, ev->keyboard.unichar);

				// Insert the new key into the string at cursor_pos
				al_ustr_insert(value, cursor_pos, current_char);

				//char_w[cursor_pos] = al_get_ustr_width(font, current_char);
				update_char_w(cursor_pos);

				pixel_pos += char_w[cursor_pos];
				cursor_pos++;
			}
		}
	}



	return TRIGGER_NULL;
}


void TS_TXTINPUT::draw(ALLEGRO_FONT *font) {

	// Draw to the current target which by now should be the display.
	al_draw_bitmap(bmp, meta.x, meta.y, 0);


	al_set_clipping_rectangle(meta.x, meta.y, meta.width - 2, meta.height);
	// Then add some code to reposition the text along the X axis, with pixel_pos, at it moves beyond the input rectangle.
	// Instead of trimming the text, use pixel_pos to offset the drawing position and clip it inside the borders.
	al_draw_ustr(font, COLOR_INPUT_FONT, meta.x + 2, meta.y + 2, ALLEGRO_ALIGN_LEFT, value); // the +2 is for padding.
	al_reset_clipping_rectangle();


	// Uncomment for debugging:
	// al_draw_textf(font, COLOR_MAIN_FONT, meta.x + 2, meta.y + 60, ALLEGRO_ALIGN_LEFT, "%i : %i px", cursor_pos, pixel_pos);


	// Draw the cursor caret line...
	// @TODO: Make the caret stay at the border edge while new characters are added, or while the input is filled
	//if (caret_visible)
		al_draw_line(meta.x + 2 + pixel_pos, meta.y, meta.x + 2 + pixel_pos, meta.y + meta.height-1, al_map_rgb(40, 40, 40), 1.4); // The last part is line thickness.



	return;
}


