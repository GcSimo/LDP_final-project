#include <iostream>
#include "Clock.h"
using namespace std;

int main() {
	my_clock::Clock c0;
	cout << "c0: " << c0 << endl;

	my_clock::Clock c1(0,0);
	cout << "c1: " << c1 << endl;

	my_clock::Clock c2(12,27);
	cout << "c2: " << c2 << endl;

	my_clock::Clock c3("9:1");
	cout << "c3: " << c3 << endl;

	my_clock::Clock c4("9:02");
	cout << "c4: " << c4 << endl;

	my_clock::Clock c5("09:3");
	cout << "c5: " << c5 << endl;

	my_clock::Clock c6("09:04");
	cout << "c6: " << c6 << endl;

	try {
		my_clock::Clock c7(":03");
	}
	catch(my_clock::Clock::StringFormatError) {
		cout << "errore :03" << endl;
	}
	try {
		my_clock::Clock c7("03:");
	}
	catch(my_clock::Clock::StringFormatError) {
		cout << "errore 03:" << endl;
	}
	try {
		my_clock::Clock c7("00");
	}
	catch(my_clock::Clock::StringFormatError) {
		cout << "errore 00" << endl;
	}
	try {
		my_clock::Clock c7("56:233");
	}
	catch(my_clock::Clock::StringFormatError) {
		cout << "errore 56:233" << endl;
	}
}