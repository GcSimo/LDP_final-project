/*
	FILE SORGENTE MAIN.CPP
	Autore:     Andrea Visonà

	Programma principale che gestisce l'input, l'output e l'interfacciamento
	dell'utente con i dispositivi nella casa.
*/

#include "Home.h"
#include "Parser.h"
#include <iostream>
#include <fstream>

int main (int argc, char** argv) {
	// dichiarazioni e inizializzazioni
	std::ofstream log("../log/main.txt"); // creazione file di sola scrittura nella cartella log
	std::string in; // stringa per memorizzare comando inserito dall'utente
	std::string out; // stringa per memorizzare messaggi di output
	
	// creazione casa
	domotic_home::Home h;
	if (argc == 2) {
		try
		{
			h = domotic_home::Home(std::stod(argv[1]));
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Uso improprio dei parametri da linea di comando. Utilizzo corretto: \n  main potenza_massima_assorbibile_dalla_rete\n";
			return 0;
		}
		catch (const domotic_home::Home::NonPositiveMaxPower &e) {
			std::cout << e.what() << "\n\n";
			return 0;
		}
	}
	

	std::cout << "Programma Domotic-Home del gruppo ~BankAccount()" << std::endl << std::endl;
	if (!log.is_open()) {
		std::cout << "Errore nell'apertura del file all'indirizzo ../log/main.txt" << std::endl;
		return 1;
	}

	// ciclo che riceve comandi da eseguire
	while(!h.isDayEnded()){
		// leggo il comando
		std::cout << "> ";
		std::getline(std::cin, in);
		
		// comando per terminare l'esecuzione prima di raggiungere le 23:59
		if (in == "exit")
			break;
		
		// parser eseguito solo se l'utente inserisce qualcosa
		else if (in != "") {
			try {
				out = domotic_home::parser(in, h);
				std::cout << out << std::endl;
				log << out << std::endl;
			}
			catch(const domotic_home::Clock::HourRangeError& e) {
				std::cout << e.what() << "\n\n";
			}
			catch(const domotic_home::Clock::MinuteRangeError& e) {
				std::cout << e.what() << "\n\n";
			}
			catch(const domotic_home::Clock::StringFormatError& e) {
				std::cout << e.what() << "\n\n";
			}
			catch(const domotic_home::Home::InvalidDeviceName& e) {
				std::cout << e.what() << "\n\n";
			}
			catch(const domotic_home::Home::InvalidDeviceType& e) {
				std::cout << e.what() << "\n\n";
			}
			catch(const domotic_home::Home::TimeRangeError& e) {
				std::cout << e.what() << "\n\n";
			}
			catch(const domotic_home::ParserError& e) {
				std::cout << e.what() << "\n\n";
			}
		}
	}

	if (h.isDayEnded())
		out = "Il sistema ha raggiunto le 23:59 e si è arrestato correttamente\n";
	else
		out = "Il sistema si è arrestato correttamente\n";
	std::cout << out << std::endl;
	log << out << std::endl;

	return 0;
}
