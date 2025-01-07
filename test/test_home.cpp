#include <iostream>
#include "DeviceM.h"
#include "DeviceCP.h"
#include "Home.h"
using namespace std;

int main () {
	cout << "Programma Robotic-Home del gruppo ~BankAccount()" << endl << endl;
	
	// creazione casa
	robotic_home::Home h;

	vector<string> inputs = {
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

	for(string s : inputs)
		h.listen(s);
	
	/* while(true){
		std::string str;
		std::getline(std::cin,str);
		h.listen(str);
	} */
}
