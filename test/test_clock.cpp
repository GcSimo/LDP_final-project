#include <iostream>
#include "Clock.h"

using namespace std;
using namespace domotic_home;

int main() {
	Clock c0;
	cout << "c0: " << c0 << endl;

	Clock c1(0,0);
	cout << "c1: " << c1 << endl;

	Clock c2(12,27);
	cout << "c2: " << c2 << endl;

	Clock c3("9:1");
	cout << "c3: " << c3 << endl;

	Clock c4("9:02");
	cout << "c4: " << c4 << endl;

	Clock c5("09:3");
	cout << "c5: " << c5 << endl;

	Clock c6("09:04");
	cout << "c6: " << c6 << endl;

	try {
		Clock c7(":03");
	}
	catch(Clock::StringFormatError) {
		cout << "errore :03" << endl;
	}
	try {
		Clock c7("03:");
	}
	catch(Clock::StringFormatError) {
		cout << "errore 03:" << endl;
	}
	try {
		Clock c7("00");
	}
	catch(Clock::StringFormatError) {
		cout << "errore 00" << endl;
	}
	try {
		Clock c7("56:233");
	}
	catch(Clock::StringFormatError) {
		cout << "errore 56:233" << endl;
	}

	cout << "+: " << Clock("22:00") + Clock("12:00") << endl;
}