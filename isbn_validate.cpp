#include <iostream>

using namespace std;

/* This quick function validates a 13-digit ISBN for you */
bool is_valid_isbn13(char digits[13]) {
	int i;
	int check = 0;

	for (i = 0; i < 13; i += 2)
		check += digits[i];
	for (i=1; i<12; i+=2)
		check += 3*digits[i];

	return check%10==0;
}
