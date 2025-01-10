#include <iostream>
#include <vector>
#include <string>
#include "Home.h"
using namespace std;

int main () {
	std::cout << "Programma Domotic-Home del gruppo ~BankAccount()" << std::endl << std::endl;
	
	// creazione casa
	domotic_home::Home h;

	// test accensione e spegnimento
	cout << h.show() << endl;
	cout << h.set("Televisore", true) << endl;
	cout << h.set("Lavatrice", true) << endl;
	cout << h.show() << endl;
	cout << h.set_time("1:00") << endl;
	cout << h.show() << endl;
	cout << h.set_time("2:00") << endl;
	cout << h.show() << endl;
	cout << h.reset_time() << endl;
	cout << h.show() << endl;
	cout << " ------------------------------ \n" << endl;
	cout << h.set("Lavastoviglie", true) << endl;
	cout << h.set("Scaldabagno", true) << endl;
	cout << h.set("Scaldabagno", "1:00", "3:00") << endl;
	cout << h.set_time("2:00") << endl;
	cout << h.show() << endl;
	//cout << h.reset_timers() << endl;
	cout << h.set_time("4:00") << endl;
	cout << h.show() << endl;
	cout << h.set_time("10:39") << endl;
	cout << h.show() << endl;
	cout << h.set_time("23:59") << endl;
	cout << h.show() << endl;
}
