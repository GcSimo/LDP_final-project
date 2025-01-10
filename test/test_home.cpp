#include <iostream>
#include <vector>
#include <string>
#include "Home.h"
using namespace std;

int main () {
	std::cout << "Programma Domotic-Home del gruppo ~BankAccount()" << std::endl << std::endl;
	
	// creazione casa
	domotic_home::Home h;
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

	std::vector<std::string> inputs = {
		"show",
		"set Impianto_fotovoltaico 6:00 12:00",
		"set Pompa_di_calore_+_termostato 1:20 7:20",
		"set time 6:00",
		"show",
		"set Televisore 10:00",
		"set time 12:00",
		"set Lavatrice 12:30",
		"set Lavastoviglie 12:31",
		"set Televisore 12:32",
		"set time 13:00",
		"set Televisore on",
		"set time 14:30",
		"show",
		"reset timers",
		//"set time 300",
		//"set Frigorifero on",
		//"set time 600",
		//"set Frigorifero off",
		//"set time 660",
		//"set Frigorifero on",
		//"set time 1260",
		//"set Frigorifero off",
		//"set Televisore 1300",
		//"set time 1400",
		"show"
	};
}
