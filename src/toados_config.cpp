#include "toados_config.h"
#include <fstream>

using namespace std;


int ts_load_config(char* path) {

	ALLEGRO_COLOR color;
	int r;
	int g;
	int b;
	int ival;
	string strval;
	string input_type;

	ifstream file(path);
	string key;

	char comment[255];

	while (file >> key) {

		if (key[0] != '#') { // Ignore anything after the '#' comment character on that line


			if (key == "<color>") {
				input_type = "<color>";
				file >> key;
			} else if (key == "<int>") {
				input_type = "<int>";
				file >> key;
			} else if (key == "<string>") {
				input_type = "<string>";
				file >> key;
			}


			if (input_type == "<color>") {
				// Assign all the color variables

				file >> r;
				file >> g;
				file >> b;
				color = al_map_rgb(r, g, b);

				if (key == "main-bg:")
					COLOR_MAIN_BG = color;
				if (key == "main-font:")
					COLOR_MAIN_FONT = color;
				if (key == "input-bg:")
					COLOR_INPUT_BG = color;
				if (key == "input-font:")
					COLOR_INPUT_FONT = color;
				if (key == "input-bg-active:")
					COLOR_INPUT_BG_ACTIVE = color;
				if (key == "input-border:")
					COLOR_INPUT_BORDER = color;
				if (key == "input-border-active:")
					COLOR_INPUT_BORDER_ACTIVE = color;
				if (key == "button-bg:")
					COLOR_BUTTON_BG = color;

			} else if (input_type == "<string>") {

				file >> strval;

				if (key == "TOOLTIP_ENABLE")
					CFG_TOOLTIP_ENABLE = strval;

			} else if (input_type == "<int>") {

				file >> ival;

				if (key == "TOOLTIP_SPROUT")
					CFG_TOOLTIP_SPROUT = ival;
				if (key == "TOOLTIP_WILT")
					CFG_TOOLTIP_WILT = ival;
				if (key == "TOOLTIP_DELAY")
					CFG_TOOLTIP_DELAY = ival;

			}

/*
			// Handle any settings for colors
			if (key.find("COLOR_")) {
				file >> r;
				file >> g;
				file >> b;
				color = al_map_rgb(r, g, b);

				// Assign all the color variables

				if (key == "main-bg:")
					COLOR_MAIN_BG = color;
				if (key == "main-font:")
					COLOR_MAIN_FONT = color;
				if (key == "input-bg:")
					COLOR_INPUT_BG = color;
				if (key == "input-font:")
					COLOR_INPUT_FONT = color;
				if (key == "input-bg-active:")
					COLOR_INPUT_BG_ACTIVE = color;
				if (key == "input-border:")
					COLOR_INPUT_BORDER = color;
				if (key == "input-border-active:")
					COLOR_INPUT_BORDER_ACTIVE = color;
				if (key == "button-bg:")
					COLOR_BUTTON_BG = color;

			} else {

				// Send in the value as a string
				file >> strval;

				// Check if the string is actually a number
				if (is_number(&strval)) {
					// Handle all the numeric variables


				} else {
					// Assign all the string variables!
				}

			}
*/

		} else {
			file.getline(comment, 255);
		}
	}

	file.close();

	return 0;
}


int ts_load_stock_config() {

	// Load the default settings!
/*
	BLOOD_PER_CHUNK = 45;
	CHANCE_OF_FLIGHT = 2000;
	CHANCE_OF_GEM = 25;
	CHICKEN_SPEED = 5;
	CHUNKS_PER_CHICKEN = 20;
	FULLSCREEN = 1;
	GAME_SPEED_OFFSET = 0;
	GRAVITY = 0.7;
	MAX_CHICKENS = 80;
	MUTE = 0;
	POINTS_FOR_ROCKET = 100;
	POINTS_FOR_SHOTGUN = 250;
	POINTS_FOR_TENDERIZER = 100;
	INITIAL_CHICKENS = 3;
	RESPAWN_RATE = 25;
	ROCKET_RELOAD = 10;
	ROCKET_SIZE = 50;
	SHOTGUN_RELOAD = 55;
	SHOTGUN_SIZE = 40;
	SMOKE_LINGERING = 35;
	SMOKE_PUFFS = 20;
	TIMER = 120;
	TRANSLUCENT_SMOKE = 1;
	VOLUME = 255;
*/
	return 0;

}
