/*
	FILE HEADER HOME.CPP
	Autore:     Andrea Visonà
*/

#include "Home.h"
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
		set_time("0:00");
	}

	/**
	 * @brief Funzione per accendere / spegnere un dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @param new_status true -> accendere / false -> spegnere
	 * @return std::string messaggio di output
	 */
	std::string Home::set(const std::string &devicename, bool new_status) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// set devicename off
		if (new_status) {
			// controllo assorbimento
			if (power_absorption - devices[devicename]->get_energy() > MAX_POWER_ABSORPTION) {
				out += "[" + time.toString() + "] Il dispositivo " + devicename + " non si è acceso perché si supererebbe la potenza massima asorbibile dalla rete\n";
			}
			else {
				devices[devicename]->turnOn(time);
				power_absorption -= devices[devicename]->get_energy();
				out += "[" + time.toString() + "] Il dispositivo " + devicename + " si è acceso\n";
			}
		}

		// set devicename off
		else {
			// controllo assorbimento - per pannelli
			if (power_absorption + devices[devicename]->get_energy() > MAX_POWER_ABSORPTION) {
				out += "[" + time.toString() + "] Il dispositivo " + devicename + " non si è spento perché si supererebbe la potenza massima asorbibile dalla rete\n";
			}
			else {
				devices[devicename]->turnOff(time);
				power_absorption += devices[devicename]->get_energy();
				out += "[" + time.toString() + "] Il dispositivo " + devicename + " si è spento\n";
			}
		}
		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione per impostare un'accensione programmata del dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @param start orario di accensione
	 * @return std::string messaggio di output
	 */
	std::string Home::set(const std::string &devicename, const Clock &start) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// imposto orario di accensione
		devices[devicename]->set_onTime(start);
		
		// calcolo messaggio di output
		out += "[" + time.toString() + "] Impostato un timer per il dispositivo " + devicename + " dalle " + devices[devicename]->get_onTime().toString() + " alle " + devices[devicename]->get_offTime().toString() + "\n";

		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione per impostare accensione e spegnimento programmati
	 * 
	 * @param devicename nome del dispositivo
	 * @param start orario di accensione
	 * @param stop orario di spegnimento
	 * @return std::string messaggio di output
	 */
	std::string Home::set(const std::string &devicename, const Clock &start, const Clock &stop) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();
		
		// verifico che il dispositivo sia di tipo manuale
		if (!dynamic_cast<DeviceM *>(devices[devicename]))
			throw InvalidDeviceType();

		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// imposto orari accensione e spegnimento
		DeviceM *temp = dynamic_cast<DeviceM *>(devices[devicename]);
		temp->set_onTime(start);
		temp->set_offTime(stop);
		//devices[devicename]->set_onTime(start);
		//devices[devicename]->set_offTime(stop);

		// calcolo messaggio di output
		out += "[" + time.toString() + "] Impostato un timer per il dispositivo " + devicename + " dalle " + devices[devicename]->get_onTime().toString() + " alle " + devices[devicename]->get_offTime().toString() + "\n";

		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione per rimuovere accensione/spegnimento programmati
	 * 
	 * @param devicename nome del dispositivo
	 * @return std::string messaggio di ouput
	 */
	std::string Home::rm(const std::string &devicename) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// calcolo messaggio di output
		out += "[" + time.toString() + "] --- rm devicename / FUNZIONE NON IMPLEMENTATA ---\n";

		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione per stampare i dispositivi della casa e relativi consumi
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::show() {
		double cons = 0; // consumo complessimo
		double prod = 0; // produzione complessiva

		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
			
		// calcolo consumo, produzione complessiva e consumo istantaneo
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			if (d.second->get_totalEnergy() < 0)
				cons -= d.second->get_totalEnergy();
			else
				prod += d.second->get_totalEnergy();
		}

		// stampo consumo e produzione del sistema
		out += "[" + time.toString() + "] Attualmente il sistema ha prodotto " + std::to_string(prod)  + " kWh e consumato " + std::to_string(cons) + " kWh. Nello specifico:\n";
		
		// stampo nome, status e consumo individuale dei dispositivi
		// calcolo consumo complessivo e consumo istantaneo
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			out += " - il dispositivo " + d.first + " ha " + (d.second->get_totalEnergy() > 0 ? "prodotto " : "consumato ") + std::to_string(std::abs(d.second->get_totalEnergy())) + " kWh\n";
		}

		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione per stampare il consumo di un dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @return std::string messaggio di output
	 */
	std::string Home::show(const std::string &devicename) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// calcolo messaggio di output
		out += "[" + time.toString() + "] --- show devicename / FUNZIONE NON IMPLEMENTATA ---\n";

		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione di debug per riportare l'orario della casa al valore iniziale (0:00)
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_time() {
		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// spengo i dispotivi
		for (auto x : this->devices) {
			x.second->turnOff(this->time);
		}

		// reimposto l'ora della casa
		this->time = Clock("0:00");

		// calcolo messaggio di output
		out += "[" + time.toString() + "] --- reset_time ---\n";

		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione di debug per resettare i timer di tutti i dispositivi
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_timers() {
		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// reimposto gli orari di ogni dispotivo
		for (auto x : this->devices){
			x.second->get_onTime() = Clock(0);
			x.second->get_offTime() = Clock(0);
		}

		// calcolo messaggio di output
		out += "[" + time.toString() + "] --- reset_timers ---\n";

		// restituisco messaggio di output
		return out;
	}

	/**
	 * @brief Funzione per riportare lo stato della casa alle condizioni iniziali
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_all() {
		// stringa per output
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// calcolo messaggio di output
		out += "[" + time.toString() + "] --- reset_all / FUNZIONE NON IMPLEMENTATA ---\n";

		// restituisco messaggio di output
		return out;
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

	/**
	 * @brief Funzione per far avanzare l'orario della casa e accendere/spegnere i dispositivi in base agli orari programmati
	 * 
	 * @param endTime orario di arrivo
	 * @return std::string messaggio di output
	 */
	std::string Home::set_time(const Clock &endTime) {
		/**
		 * priority queue eventList
		 * - memorizza oggetti di tipo event (struct <time,device>)
		 * - usa come container un vector (impostazione di default)
		 * - usa la function object eventCompare come criterio di ordinamento
		 */
		std::priority_queue<event, std::vector<event>, eventCompare> eventList;
		Clock &startTime = time; // così il nome è più esplicito
		std::string out = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

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
				out += "[" + eventList.top().time.toString() + "] Il dispositivo " + eventList.top().dev->get_name() + " non si è acceso perché si supererebbe la potenza massima asorbibile dalla rete\n";
			}
			else if (eventList.top().command) { // dispositivo da accendere
				eventList.top().dev->turnOn(eventList.top().time);
				power_absorption -= eventList.top().dev->get_energy();
				out += "[" + eventList.top().time.toString() + "] Il dispositivo " + eventList.top().dev->get_name() + " si è acceso\n";
			}
			else { // dispositivo da spegnere
				eventList.top().dev->turnOff(eventList.top().time);
				power_absorption += eventList.top().dev->get_energy();
				out += "[" + eventList.top().time.toString() + "] Il dispositivo " + eventList.top().dev->get_name() + " si è spento\n";
			}
			eventList.pop();
		}

		// aggiorno i consumi
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			d.second->refreshDevice(endTime);
		}

		// aggiorno l'orario della casa
		startTime = endTime;

		// restituisco messaggio di output
		return out;
	}
}
