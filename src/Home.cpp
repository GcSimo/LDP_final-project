/*
	FILE HEADER HOME.CPP
	Autore:     Andrea Visonà
*/

#include "Home.h"
#include <iostream>
#include <sstream>
#include <queue>


namespace robotic_home {
	// elenco dispositivi della casa
	std::vector<Device *> deviceList = {
		new DeviceM("Impianto_fotovoltaico", 1.5),
		new DeviceCP("Lavatrice", -2, "1:50"),
		new DeviceCP("Lavastoviglie", -1.5, "3:15"),
		new DeviceM("Pompa_di_calore_+_termostato", -2),
		new DeviceCP("Tapparelle_elettriche", -0.3, "0:01"),
		new DeviceM("Scaldabagno", -1),
		new DeviceM("Frigorifero", -0.4),
		new DeviceCP("Forno_a_microonde", -0.8, "0:02"),
		new DeviceCP("Asciugatrice", -0.5, "1:00"),
		new DeviceCP("Televisore", -0.2, "1:00"),
	};

	Home::Home() {
		// inizializza ora del giorno a 0
		time = Clock();

		// inizializzazione potenza assorbita dalla rete a 0
		power_absorption = DEFAULT_POWER_ABSORPTION;

		// inserisce i dispositivi nella casa
		for (Device *d : deviceList)
			devices.insert({d->get_name(), d});

		// esegue eventuali accensioni da svolgere all'ora 0:00
		goForward("0:00");
	}

	void Home::listen(const std::string &s) {
		std::vector<std::string> commandLines;
		std::istringstream stream(s);
		std::string line;

		// separa il comando ricevuto come stringa in un vettore di stringhe
		while (std::getline(stream, line, ' ')) {
			commandLines.push_back(line);
		}

		// stampa orario di inizio comando
		std::cout << "[" << time << "] L'orario attuale è " << time << std::endl;

		// comando set
		if (commandLines[0] == "set") {
			// -- set time ...
			if (commandLines[1] == "time") {
				this->goForward(commandLines[2]);
				std::cout << "[" << time << "] L'orario attuale è " << time << std::endl;
			}
			
			// --- set devicename ... (devicename valido)
			else if (devices.count(commandLines[1]) != 0) {
				// --- set devicename on
				if (commandLines[2] == "on") {
					if (power_absorption - devices.at(commandLines[1])->get_energy() > MAX_POWER_ABSORPTION) {
						std::cout << "[" << time << "] Il dispositivo " << devices.at(commandLines[1])->get_name() << " non si è acceso perché si supererebbe la potenza massima asorbibile dalla rete" << std::endl;
					}
					else {
						devices.at(commandLines[1])->turnOn(time);
						power_absorption -= devices.at(commandLines[1])->get_energy();
						std::cout << "[" << time << "] Il dispositivo " << commandLines[1] << " si è acceso" << std::endl;
					}
				}
				// --- set devicename off
				else if (commandLines[2] == "off") {
					devices.at(commandLines[1])->turnOff(time);
					power_absorption += devices.at(commandLines[1])->get_energy();
					std::cout << "[" << time << "] Il dispositivo " << commandLines[1] << " si è spento" << std::endl;
				}
				// --- set devicename start [stop]
				else {
					devices.at(commandLines[1])->set_onTime(commandLines[2]);
					
					// nel caso di un dispositivo manuale, imposto orario di spegnimento
					if (DeviceM *temp= dynamic_cast<DeviceM *>(devices.at(commandLines[1]))) {
						temp->set_offTime(commandLines[3]);
					}
					std::cout << "[" << time << "] Impostato un timer per il dispositivo " << commandLines[1] << " dalle " << devices.at(commandLines[1])->get_onTime() << " alle " << devices.at(commandLines[1])->get_offTime() << std::endl;
				}
			}

			// --- set devicename ... (devicename invalido)
			else
				throw ParserError(); // dispositivo inesistente
		}

		// comando rm
		else if (commandLines[0] == "rm") {
			std::cout << "[" << time << "] Rimosso il timer per il dispositivo " << commandLines[1] << std::endl;
		}

		// comando show
		else if (commandLines[0] == "show") {
			double cons = 0; // consumo complessimo
			double prod = 0; // produzione complessiva
			
			// calcolo consumo, produzione complessiva e consumo istantaneo
			for (auto d : devices) { // auto = std::pair<std::string,Device*>
				if (d.second->get_totalEnergy() < 0)
					cons -= d.second->get_totalEnergy();
				else
					prod += d.second->get_totalEnergy();
			}

			// stampo consumo e produzione del sistema
			std::cout  << "[" << time << "] Attualmente il sistema ha prodotto " << prod << " kWh e consumato " << cons << " kWh. Nello specifico:" << std::endl;
			
			// stampo nome, status e consumo individuale dei dispositivi
			// calcolo consumo complessivo e consumo istantaneo
			for (auto d : devices) { // auto = std::pair<std::string,Device*>
				std::cout << " - il dispositivo " << d.first << " ha " << (d.second->get_totalEnergy() > 0 ? "prodotto " : "consumato ")  << std::abs(d.second->get_totalEnergy()) << " kWh" << std::endl;
			}
		}

		// comando reset
		else if (commandLines[0] == "reset") {
			std::cout << "[" << time << "] L'orario attuale è " << time << std::endl;
		}
		
		// comando inesistente
		else
			throw ParserError(); // comando non valido

		std::cout << std::endl << std::endl;
	}


	// struct evento da memorizzare nella priority queue
	struct event {
		Clock time; // orario dell'evento
		Device *dev; // puntatore al dispositivo su cui agire
		bool command; // true -> turnOn, false -> turnOff
	};


	// funciton object per ordinamento eventi nella priority queue: l'orario minore è quello con priorità più alta
	struct eventCompare {
		bool operator()(const event &e1, const event &e2) const { return e1.time > e2.time; }
	};

	// funzione per far proseguire il tempo
	void Home::goForward(const Clock &endTime) {
		/**
		 * priority queue eventList
		 * - memorizza oggetti di tipo event (struct <time,device>)
		 * - usa come container un vector (impostazione di default)
		 * - usa la function object eventCompare come criterio di ordinamento
		 */
		std::priority_queue<event, std::vector<event>, eventCompare> eventList;
		Clock &startTime = time; // così il nome è più esplicito

		// inserisco i dati nella priority queue
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			if (d.second->get_onTime() > startTime && d.second->get_onTime() <=  endTime)
				eventList.push({d.second->get_onTime(), d.second, true});
			if (d.second->get_offTime() > startTime && d.second->get_offTime() <=  endTime)
				eventList.push({d.second->get_offTime(), d.second, false});
		}

		// estraggo i dati dalla priority queue
		while (!eventList.empty()) {
			// impossibile accendere il dispositivo perché la potenza assorbita dalla rete supera la potenza massima della rete
			if (eventList.top().command && power_absorption - eventList.top().dev->get_energy() > MAX_POWER_ABSORPTION) {
				std::cout << "[" << eventList.top().time << "] Il dispositivo " << eventList.top().dev->get_name() << " non si è acceso perché si supererebbe la potenza massima asorbibile dalla rete" << std::endl;
			}
			else if (eventList.top().command) { // dispositivo da accendere
				eventList.top().dev->turnOn(eventList.top().time);
				power_absorption -= eventList.top().dev->get_energy();
				std::cout << "[" << eventList.top().time << "] Il dispositivo " << eventList.top().dev->get_name() << " si è acceso" << std::endl;
			}
			else { // dispositivo da spegnere
				eventList.top().dev->turnOff(eventList.top().time);
				power_absorption += eventList.top().dev->get_energy();
				std::cout << "[" << eventList.top().time << "] Il dispositivo " << eventList.top().dev->get_name() << " si è spento" << std::endl;
			}
			eventList.pop();
		}

		// aggiorno i consumi
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			d.second->refreshDevice(endTime);
		}

		startTime = endTime;
	}
}
