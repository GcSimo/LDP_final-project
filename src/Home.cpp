/*
	FILE HEADER HOME.CPP
	Autore:     Andrea Visonà
*/

#include "Home.h"
#include <iostream>
#include <sstream>
#include <queue>

// elenco dispositivi della casa
std::vector<device::Device *> deviceList = {
	new device::DeviceM("Impianto_fotovoltaico", 1.5),
	new device::DeviceCP("Lavatrice", -2, "1:50"),
	new device::DeviceCP("Lavastoviglie", -1.5, "3:15"),
	new device::DeviceM("Pompa_di_calore_+_termostato", -2),
	new device::DeviceCP("Tapparelle_elettriche", -0.3, "0:01"),
	new device::DeviceM("Scaldabagno", -1),
	new device::DeviceM("Frigorifero", -0.4),
	new device::DeviceCP("Forno_a_microonde", -0.8, "0:02"),
	new device::DeviceCP("Asciugatrice", -0.5, "1:00"),
	new device::DeviceCP("Televisore", -0.2, "1:00"),
};

Home::Home() {
	// inizializza ora del giorno a 0
	time = my_clock::Clock();

	// inserisce i dispositivi nella casa
	for (device::Device *d : deviceList)
		devices.insert({d->get_name(), d});
}

void Home::listen(const std::string &s) {
	std::vector<std::string> commandLines;
	std::istringstream stream(s);
	std::string line;

	// separa il comando ricevuto come stringa in un vettore di stringhe
	while (std::getline(stream, line, ' ')) {
		commandLines.push_back(line);
	}

	// comando set
	if (commandLines[0] == "set") {
		// -- set time ...
		if (commandLines[1] == "time") {
			std::cout << "\n\nTempo : " << time << " ---> " << commandLines[2] << "\n\n";
			this->goForward(commandLines[2]);
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
				devices.at(commandLines[1])->set_onTime(commandLines[2]);
				// nel caso di un dispositivo manuale, imposto orario di spegnimento
				// if (devices.at(commandLines[1])->isManual()) {
				// 	devices.at(commandLines[1])->set_offTime(commandLines[3]);
				// }
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


// struct evento da memorizzare nella priority queue
struct event {
	my_clock::Clock time; // orario dell'evento
	device::Device *dev; // puntatore al dispositivo su cui agire
	bool command; // true -> turnOn, false -> turnOff
};


// funciton object per ordinamento eventi nella priority queue: l'orario minore è quello con priorità più alta
struct eventCompare {
	bool operator()(const event &e1, const event &e2) const { return e1.time > e2.time; }
};

// funzione per far proseguire il tempo
void Home::goForward(const my_clock::Clock &endTime) {
	/**
	 * priority queue eventList
	 * - memorizza oggetti di tipo event (struct <time,device>)
	 * - usa come container un vector (impostazione di default)
	 * - usa la function object eventCompare come criterio di ordinamento
	 */
	std::priority_queue<event, std::vector<event>, eventCompare> eventList;
	my_clock::Clock &startTime = time; // così il nome è più esplicito

	// inserisco i dati nella priority queue
	for (device::Device *d : deviceList) {
		if (d->get_onTime() > startTime || d->get_onTime() <=  endTime)
			eventList.push({d->get_onTime(), d, true});
		if (d->get_offTime() > startTime || d->get_offTime() <=  endTime)
			eventList.push({d->get_offTime(), d, false});
	}

	// estraggo i dati dalla priority queue
	while (!eventList.empty()) {
		if(eventList.top().command) // dispositivo da accendere
			eventList.top().dev->turnOn(eventList.top().time);
		else // dispositivo da spegnere
			eventList.top().dev->turnOff(eventList.top().time);
		eventList.pop();
	}

	// aggiorno i consumi
	//for (device::Device *d : deviceList) {
	//	d->update_energy();
	//}

	startTime = endTime;
}
