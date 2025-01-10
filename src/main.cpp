/*
	FILE MAIN.CPP
	Autore:     Andrea Visonà
*/

#include <iostream>
#include <vector>
#include <string>
#include "Home.h"
#include "Parser.h"

int main () {
	std::cout << "Programma Domotic-Home del gruppo ~BankAccount()" << std::endl << std::endl;
	
	// creazione casa
	domotic_home::Home h;

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

	/* while(true){
		std::string str;
		std::getline(std::cin,str);
		h.listen(str);
	} */

	for(std::string s : inputs) {
		domotic_home::parser(s,h);
	}
}
