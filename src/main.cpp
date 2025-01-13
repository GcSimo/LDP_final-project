/*
	FILE MAIN.CPP
	Autore:     Andrea Visonà
*/

#include <iostream>
#include <fstream>
#include "Home.h"
#include "Parser.h"

int main () {
	// dichiarazioni e inizializzazioni
	std::ofstream log("../log/main.txt"); // creazione file di sola scrittura nella cartella log
	std::string in; // stringa per memorizzare comando inserito dall'utente
	std::string out; // stringa per memorizzare messaggi di output
	domotic_home::Home h; // creazione casa

	std::cout << "Programma Domotic-Home del gruppo ~BankAccount()" << std::endl << std::endl;
	if (!log.is_open()) {
		std::cout << "Errore nell'apertura del file all'indirizzo ../log/main.txt" << std::endl;
		return 1;
	}

	// ciclo che riceve comandi da eseguire
	while(!h.isDayEnded()){
		std::cout << "> ";
		std::getline(std::cin, in);
		try {
			out = domotic_home::parser(in, h);
			std::cout << out << std::endl;
			log << out << std::endl;
		}
		catch(const domotic_home::Clock::HourRangeError& e) {
			std::cout << e.what() << '\n';
		}
		catch(const domotic_home::Clock::MinuteRangeError& e) {
			std::cout << e.what() << '\n';
		}
		catch(const domotic_home::Clock::StringFormatError& e) {
			std::cout << e.what() << '\n';
		}
		catch(const domotic_home::Home::InvalidDeviceName& e) {
			std::cout << e.what() << '\n';
		}
		catch(const domotic_home::Home::InvalidDeviceType& e) {
			std::cout << e.what() << '\n';
		}
		catch(const domotic_home::Home::TimeRangeError& e) {
			std::cout << e.what() << '\n';
		}
	}

	out = "Il sistema ha raggiunto le 23:59 e si è arrestato correttamente\n";
	std::cout << out << std::endl;
	log << out << std::endl;
}
