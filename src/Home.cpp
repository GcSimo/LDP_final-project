/*
	FILE HEADER HOME.CPP
	Autore:     Andrea Visonà
*/

#include "Home.h"
#include <iostream>
#include <sstream>

// elenco dispositivi della casa
std::vector<Device *> DeviceList = {
	new DeviceM("Impianto_Fotovoltaico", 1.5),
	new DeviceCP("Lavatrice", -2, 110),
	new DeviceCP("Lavastoviglie", -1.5, 195),
	new DeviceM("Pompa di calore + termostato", -2),
	new DeviceCP("Tapparelle elettriche", -0.3, 1),
	new DeviceM("Scaldabagno", -1),
	new DeviceM("Frigorifero", -0.4),
	new DeviceCP("Forno a microonde", -0.8, 2),
	new DeviceCP("Asciugatrice", -0.5, 60),
	new DeviceCP("Televisore", -0.2, 60),
};

Home::Home() {
	// inizializza ora del giorno a 0
	time = my_clock::Clock();

	// inserisce i dispositivi nella casa
	for (Device* d : DeviceList)
		devices.insert({d->get_name(), d});
}


void Home::listen(std::string s) {
	std::vector<std::string> commandLines;
	std::istringstream stream(s);
	std::string line;

	// separa il comando in un vettore di stringhe
	while (std::getline(stream, line, ' ')) {
		commandLines.push_back(line);
	}

	// comando set
	if (commandLines[0] == "set") {
		// -- set time ...
		if (commandLines[1] == "time") {
		   if (commandLines[2].empty())
				throw ParserError(); // orario non specificato
			int timeto = std::stoi(commandLines[2]);
			std::cout << "\n\nTempo : " << time << " ---> " << timeto << "\n\n";
			time = timeto;
			this->goForward(timeto);
		}
		
		// --- set devicename ... (devicename valido)
		else if (devices.count(commandLines[1]) != 0) {
			// --- set devicename on
			if (commandLines[2] == "on") {
				devices.at(commandLines[1])->turnOn(time);
				std::cout << "dispositivo " << commandLines[1] << " ON";
			}
			// --- set devicename off
			else if (commandLines[2] == "off") {
				devices.at(commandLines[1])->turnOff(time);
				std::cout << "dispositivo " << commandLines[1] << " OFF";
			}
			// --- set devicename start [stop]
			else {
				int timefromtimer = std::stoi(commandLines[2]);
				devices.at(commandLines[1])->set_onTime(timefromtimer);
				// nel caso di un dispositivo manuale, imposto orario di spegnimento
				//if (devices.at(commandLines[1])->isManual()) {
   				//	int timetotimer = std::stoi(commandLines[3]);
				//	devices.at(commandLines[1])->set_offTime(timetotimer);
				//}
			}
		}

		// --- set devicename ... (devicename invalido)
		else
			throw ParserError(); // dispositivo inesistente
	}

	// comando rm
	else if (commandLines[0] == "rm") {

	}

	// comando show
	else if (commandLines[0] == "show") {
		float cons = 0;
		float actualcons = 0;
		std::cout << "Show al tempo " << time << " :\n";
		// stampo nome, status e consumo individuale dei dispositivi
		// calcolo consumo complessivo e consumo istantaneo
		for (auto &d : devices) {
			float thiscons = d.second->get_totalEnergy(time);
			std::cout << d.first << " : " << (d.second)->get_status() << ", ha consumato " << thiscons << "KW fino ad ora\n";
			cons += thiscons;
			if((d.second)->get_status())
				actualcons += d.second->get_energy();
		}
		// stampo consumo complessivo e consumo istantaneo
		std::cout << "\nConsumo totale della casa fino alle " << time << " : " << cons << "Kw/h\nE con un attuale consumo di " << actualcons << "Kw\n\n";
		return;
	}

	// comando reset
	else if (commandLines[0] == "reset") {

	}
	
	// comando inesistente
	else
		throw ParserError(); // comando non valido
}

// funzione per far proseguire il tempo
void Home::goForward(short ti) {
	//for (auto &d : devices)
	//	(d.second)->refreshTimers(ti);
	//this->time = ti;
}
