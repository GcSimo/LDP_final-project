/*
	FILE SORGENTE HOME.CPP
	Autore:     Giacomo Simonetto

	Implementazione delle funzioni della classe Home
*/

#include "Home.h"
#include <queue>

namespace domotic_home {
	// elenco dispositivi con relativi consumi e durata cicli
	constexpr int nDevices = 10;
	std::string deviceName[nDevices]  = {"Impianto fotovoltaico", "Lavatrice", "Lavastoviglie", "Pompa di calore + termostato", "Tapparelle elettriche", "Scaldabagno", "Frigorifero", "Forno a microonde", "Asciugatrice", "Televisore" };
	std::string deviceCycle[nDevices] = {         "0:00",            "1:50",       "3:15",                  "0:00",                     "0:01",              "0:00",       "0:00",           "0:02",           "1:00",        "1:00"     };
	double devicePower[nDevices]      = {          1.5,               -2,           -1.5,                    -2,                         -0.3,                -1,           -0.4,             -0.8,             -0.5,          -0.2      };

	/**
	 * @brief Costruttore di default della classe Home
	 */
	Home::Home() : Home(DEFAULT_MAX_POWER_ABSORPTION) {};

	/**
	 * @brief Costruttore della classe Home con massima potenza prelevabile passata come parametro
	 * @param max_power_absorption massima potenza prelevabile dalla rete
	 * @throw NonPositiveMaxPower se la potenza massima passata come parametro è nulla o negativa
	 */
	Home::Home(double max_power_absorption) {
		// controllo che la potenza non sia negatica
		if (max_power_absorption <= 0)
			throw NonPositiveMaxPower();

		// inizializzazioni
		this->time = Clock();
		this->power_absorption = DEFAULT_POWER_ABSORPTION;
		this->max_power_absorption = max_power_absorption;

		// inserisce i dispositivi nella casa
		for (int i = 0; i < nDevices; i++) {
			Device *newDevice = nullptr;
			if (deviceCycle[i] == "0:00")
				newDevice = new DeviceM(deviceName[i], devicePower[i]);
			else 
				newDevice = new DeviceCP(deviceName[i], devicePower[i], deviceCycle[i]);
			devices.insert({newDevice->get_name(), newDevice});
		}
	}

	/**
	 * @brief Costruttore di copia
	 * 
	 * @param h oggetto da copiare
	 */
	Home::Home(const Home &h) {
		this->time = h.time;
		this->power_absorption = h.power_absorption;
		this->max_power_absorption = h.max_power_absorption;

		// copio mappa con dispositivi
		for (auto d : h.devices) {
			Device *newDevice = nullptr;
			if (dynamic_cast<DeviceM *>(d.second))
				newDevice = new DeviceM(*dynamic_cast<DeviceM *>(d.second));
			else
				newDevice = new DeviceCP(*dynamic_cast<DeviceCP *>(d.second));
			this->devices.insert({newDevice->get_name(), newDevice});
		}

		// popolo lista con i riferimenti ai dispositivi della mappa
		for (auto d : h.turned_on_devices)
			this->turned_on_devices.push_back(this->devices[d->get_name()]);
	}

	/**
	 * @brief Costruttore di move
	 * 
	 * @param h oggetto rvalue
	 */
	Home::Home(Home &&h) {
		// copio i valori
		this->time = h.time;
		this->power_absorption = h.power_absorption;
		this->max_power_absorption = h.max_power_absorption;
		this->devices = h.devices; // copia gli indirizzi di memoria, i dispositivi sono gli stessi
		this->turned_on_devices = h.turned_on_devices; // copia indirizzi di memoria, i dispositivi sono gli stessi
		
		// elimino dati in h
		h.time = Clock();
		h.power_absorption = 0;
		h.max_power_absorption = 0; // non ha senso, tanto h verrà eliminato
		h.devices.clear();
		h.turned_on_devices.clear();
	}

	/**
	 * @brief Distruttore della classe home
	 * libera l'area di memoria occupata dai dispositivi
	 */
	Home::~Home() {
		// per ogni dispositivo, ci accedo con un puntatore specifico del suo tipo e lo dealloco
		for (auto d : this->devices) {
			if (dynamic_cast<DeviceM *>(d.second)) {
				DeviceM *temp = dynamic_cast<DeviceM *>(d.second);
				delete temp;
			}
			else {
				DeviceCP *temp = dynamic_cast<DeviceCP *>(d.second);
				delete temp;
			}
		}
	}

	/**
	 * @brief Assegnamento di copia
	 * 
	 * @param h oggetto da copiare
	 * @return Home& destinazione
	 */
	Home &Home::operator=(const Home &h) {
		// elimino dati vecchi
		for (auto d : this->devices) {
			if (dynamic_cast<DeviceM *>(d.second)) {
				DeviceM *temp = dynamic_cast<DeviceM *>(d.second);
				delete temp;
			}
			else {
				DeviceCP *temp = dynamic_cast<DeviceCP *>(d.second);
				delete temp;
			}
		}
		this->devices.clear();
		this->turned_on_devices.clear();

		// inserisco dati nuovi
		this->time = h.time;
		this->power_absorption = h.power_absorption;
		this->max_power_absorption = h.max_power_absorption;

		// copio mappa con dispositivi
		for (auto d : h.devices) {
			Device *newDevice = nullptr;
			if (dynamic_cast<DeviceM *>(d.second))
				newDevice = new DeviceM(*dynamic_cast<DeviceM *>(d.second));
			else
				newDevice = new DeviceCP(*dynamic_cast<DeviceCP *>(d.second));
			this->devices.insert({newDevice->get_name(), newDevice});
		}

		// popolo lista con i riferimenti ai dispositivi della mappa
		for (auto d : h.turned_on_devices)
			this->turned_on_devices.push_back(this->devices[d->get_name()]);
		
		// restituisco oggetto this
		return *this;
	}

	/**
	 * @brief Assegnamento di move
	 * 
	 * @param h oggetto rvalue
	 * @return Home& destinazione
	 */
	Home &Home::operator=(Home &&h) {
		// elimino dati vecchi
		for (auto d : this->devices) {
			if (dynamic_cast<DeviceM *>(d.second)) {
				DeviceM *temp = dynamic_cast<DeviceM *>(d.second);
				delete temp;
			}
			else {
				DeviceCP *temp = dynamic_cast<DeviceCP *>(d.second);
				delete temp;
			}
		}
		this->devices.clear();
		this->turned_on_devices.clear();

		// inserisco quelli nuovi
		this->time = h.time;
		this->power_absorption = h.power_absorption;
		this->max_power_absorption = h.max_power_absorption;
		this->devices = h.devices; // copia gli indirizzi di memoria
		this->turned_on_devices = h.turned_on_devices; // copia indirizzi di memoria
		
		// elimino dati in h
		h.time = Clock();
		h.power_absorption = 0;
		h.max_power_absorption = 0; // non ha senso, tanto h verrà eliminato
		h.devices.clear();
		h.turned_on_devices.clear();

		// restituisco oggetto this
		return *this;
	}


	/**
	 * @brief Funzione per accendere / spegnere un dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @param new_status true -> accendere / false -> spegnere
	 * @return std::string messaggio di output
	 * @throw InvalidDeviceName se devicename non è presente nella casa
	 */
	std::string Home::set(const std::string &devicename, bool new_status) {
		// verifico presenza dispositivo nella mappa
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// accendo/spengo il dispositivo tramite funzione ausiliaria set
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		log += set(devices[devicename], new_status, time);

		return log;
	}

	/**
	 * @brief Funzione per impostare un'accensione programmata del dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @param start orario di accensione
	 * @return std::string messaggio di output
	 * @throw InvalidDeviceName se devicename non è presente nella casa
	 * @throw TimeRangeError se start è precedente all'orario della casa
	 */
	std::string Home::set(const std::string &devicename, const Clock &start) {
		// verifico presenza dispositivo nella mappa
		if (!devices.count(devicename))
			throw InvalidDeviceName();
		
		// verifico che l'orario non sia nel passato
		if(start < time)
			throw TimeRangeError();

		// imposto orario di accensione dopo aver rimosso gli orari vecchi
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		devices[devicename]->resetTime();
		devices[devicename]->set_onTime(start);
		log += "[" + time.toString() + "] Impostato un timer per il dispositivo " + devicename + " dalle " + devices[devicename]->get_onTime().toString();
		log += (devices[devicename]->get_offTime().isValid() ? " alle " + devices[devicename]->get_offTime().toString() : " in poi") + "\n";

		// se l'orario di accensione è l'orario corrente, il dispositivo viene acceso
		if (time == start)
			log += set(devices[devicename], true, time);

		return log;
	}

	/**
	 * @brief Funzione ausiliaria di overloading della funzione set(string, clock) in modo da poter
	 * utilizzare string-literal come orari di accensione e spegnimento.
	 *
	 * Quando si invoca la funzione set(string, Clock) inserendo uno string-literal come orario,
	 * il secondo parametro è di tipo const char* e il compilatore preferisce utilizzare il casting
	 * implicito da puntatore (const char*) a bool al posto di eseguire il cast da const char*
	 * a Clock, specificato nel costruttore Clock(const char*).
	 * Per questo motivoviene invocata la funzione set(string, true) al posto di set(string, clock).
	 * 
	 * Con questo overloading si fa in modo di forzare la chiamata della funzione set desiderata.
	 * 
	 * @param devicename nome del dispositivo
	 * @param start orario di accensione
	 * @return std::string
	 */
	std::string Home::set(const std::string &devicename, const char *start) {
		return set(devicename, Clock(start));
	}

	/**
	 * @brief Funzione per impostare accensione e spegnimento programmati
	 * 
	 * @param devicename nome del dispositivo
	 * @param start orario di accensione
	 * @param stop orario di spegnimento
	 * @return std::string messaggio di output
	 * @throw InvalidDeviceName se devicename non è presente nella casa
	 * @throw InvalidDeviceType se si tenta di impostare un orario di spegnimento programmato ad un dispositivo CP
	 * @throw TimeRangeError se start è precedente all'orario di sistema o se stop è precedente a start
	 */
	std::string Home::set(const std::string &devicename, const Clock &start, const Clock &stop) {
		// verifico presenza dispositivo nella mappa e che sia di tipo manuale
		if (!devices.count(devicename))
			throw InvalidDeviceName();
		
		if (!dynamic_cast<DeviceM *>(devices[devicename]))
			throw InvalidDeviceType();

		// verifico validità orari
		if(start < time || stop <= start)
			throw TimeRangeError();
		
		// imposto orari accensione e spegnimento dopo aver rimosso gli orari vecchi
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		DeviceM *temp = dynamic_cast<DeviceM *>(devices[devicename]);
		temp->resetTime();
		temp->set_onTime(start);
		temp->set_offTime(stop);
		log += "[" + time.toString() + "] Impostato un timer per il dispositivo " + devicename + " dalle " + devices[devicename]->get_onTime().toString();
		log += (devices[devicename]->get_offTime().isValid() ? " alle " + devices[devicename]->get_offTime().toString() : " in poi") + "\n";

		// se l'orario di accensione è l'orario corrente, il dispositivo viene acceso
		if (time == start)
			log += set(devices[devicename], true, time);

		return log;
	}

	/**
	 * @brief Funzione per rimuovere accensione/spegnimento programmati
	 * 
	 * @param devicename nome del dispositivo
	 * @return std::string messaggio di ouput
	 * @throw InvalidDeviceName se devicename non è presente nella casa
	 */
	std::string Home::rm(const std::string &devicename) {
		// verifico presenza dispositivo nella mappa
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// rimuovo timer
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		devices[devicename]->resetTime();
		log += "[" + time.toString() + "] Rimosso il timer dal dispositivo " + devicename + "\n";

		return log;
	}

	/**
	 * @brief Funzione per stampare i dispositivi della casa e relativi consumi
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::show() const {
		double cons = 0; // consumo complessimo
		double prod = 0; // produzione complessiva

		// calcolo consumo, produzione complessiva e consumo istantaneo
		for (auto d : devices) {
			if (d.second->get_totalEnergy() < 0)
				cons -= d.second->get_totalEnergy();
			else
				prod += d.second->get_totalEnergy();
		}

		// stampo consumo e produzione del sistema
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		log += "[" + time.toString() + "] Attualmente il sistema ha prodotto " + std::to_string(prod)  + " kWh e consumato " + std::to_string(cons) + " kWh. Nello specifico:\n";
		
		// stampo nome, status e consumo individuale dei dispositivi
		for (auto d : devices) {
			log += " - il dispositivo " + d.first + " ha " + (d.second->get_totalEnergy() > 0 ? "prodotto " : "consumato ");
			log += std::to_string(std::abs(d.second->get_totalEnergy())) + " kWh\n";
		}

		return log;
	}

	/**
	 * @brief Funzione per stampare il consumo di un dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @return std::string messaggio di output
	 * @throw InvalidDeviceName se devicename non è presente nella casa
	 */
	std::string Home::show(const std::string &devicename) const {
		// verifico presenza dispositivo nella mappa
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// calcolo messaggio di output
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		log += "[" + time.toString() + "] Il dispositivo " + devicename + " ha attualmente " + (devices.at(devicename)->get_totalEnergy() > 0 ? "prodotto " : "consumato ");
		log += std::to_string(std::abs(devices.at(devicename)->get_totalEnergy())) + "kWh \n";

		return log;
	}

	// struct evento da memorizzare nella priority queue per funzione set_time()
	struct event {
		Clock time; // orario dell'evento
		Device *dev; // puntatore al dispositivo su cui agire
		bool command; // true -> turnOn, false -> turnOff
	};

	/**
	 * @brief funciton object per ordinamento eventi nella priority queue per funzione set_time()
	 * Interpretazione risultato:
	 * - true:  e2 ha priorità maggiore  -  e2 viene prima di e1
	 * - false: e1 ha priorità maggiore  -  e1 viene prima di e2
	 * 
	 * Calcolo del risultato:
	 * - l'orario minore è quello con priorità più alta
	 *   - se e1.time > e2.time -> prima e2 -> return true
	 *   - se e1.time < e2.time -> prima e1 -> return false
	 * 
	 * - a parità di orario, ha priorità maggiore l'evento di spegnimento:
	 *   - se e1 accensione, e2 spegnimento -> prima e2 -> return true
	 *   - se e1 spegnimento, e2 accensione -> prima e1 -> return false
	 *   - se sono due accensioni -> stessa priorità    -> return false
	 *   - se sono due spegnimenti -> stesa priorità    -> return false
	 */
	struct eventCompare {
		bool operator()(const event &e1, const event &e2) const {
			return e1.time == e2.time ? e1.command && !e2.command : e1.time > e2.time;
		}
	};

	/**
	 * @brief Funzione per far avanzare l'orario della casa e accendere/spegnere i dispositivi in base agli orari programmati
	 * 
	 * @param endTime orario di arrivo
	 * @return std::string messaggio di output
	 * @throw TimeRangeError quando si prova a tornare indietro nel tempo
	 */
	std::string Home::set_time(const Clock &endTime) {
		/**
		 * priority_queue eventList:
		 * - memorizza oggetti di tipo event (struct <time,device>)
		 * - usa come container un vector (impostazione di default)
		 * - usa la function object eventCompare come criterio di ordinamento
		 */
		std::priority_queue<event, std::vector<event>, eventCompare> eventList;
		Clock &startTime = time; // così il nome è più esplicito

		// se orario nel passato -> lancio eccezione
		if (startTime > endTime)
			throw TimeRangeError();

		// messaggio di output
		std::string log = "[" + startTime.toString() + "] L'orario attuale è " + startTime.toString() + "\n";

		// inserisco i dati nella priority queue
		for (auto d : devices) {
			if (d.second->get_onTime() > startTime && d.second->get_onTime() <=  endTime)
				eventList.push({d.second->get_onTime(), d.second, true});
			if (d.second->get_offTime() > startTime && d.second->get_offTime() <=  endTime)
				eventList.push({d.second->get_offTime(), d.second, false});
		}

		// ciclo while per processare gli eventi nella priority queue
		while (!eventList.empty()) {
			log += set(eventList.top().dev, eventList.top().command, eventList.top().time);
			eventList.pop();
		}

		// aggiorno i consumi
		for (auto d : devices)
			d.second->refreshDevice(endTime);

		// aggiorno l'orario della casa
		startTime = endTime;

		// aggiungo l'orario finale al messaggio di stampa
		log += "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		return log;
	}

	/**
	 * @brief Funzione di debug per riportare l'orario della casa al valore iniziale (0:00)
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_time() {
		// spengo i dispotivi e resetto i consumi
		for (auto x : this->devices) {
			x.second->turnOff(this->time);
			x.second->resetTotalEnergy();
		}

		// reinizializzazioni
		power_absorption = DEFAULT_POWER_ABSORPTION;
		turned_on_devices.clear();
		this->time = Clock();

		// calcolo messaggio di output
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		log += "[" + time.toString() + "] RESET-TIME -> L'orario attuale è " + time.toString() + "\n";
		return log;
	}

	/**
	 * @brief Funzione di debug per resettare i timer di tutti i dispositivi
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_timers() {
		// reimposto gli orari di accensione e spegnimento programmati di ogni dispotivo
		for (auto x : this->devices)
			x.second->resetTime();

		// calcolo messaggio di output
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		log += "[" + time.toString() + "] RESET-TIMERS per tutti i dispositivi\n";
		return log;
	}

	/**
	 * @brief Funzione per riportare lo stato della casa alle condizioni iniziali
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_all() {
		// spengo i dispotivi, resetto i consumi e programmi
		for (auto x : this->devices) {
			x.second->turnOff(this->time);
			x.second->resetTotalEnergy();
			x.second->resetTime();
		}

		// reinizializzazioni
		power_absorption = DEFAULT_POWER_ABSORPTION;
		turned_on_devices.clear();
		this->time = Clock();

		// calcolo messaggio di output
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
		log += "[" + time.toString() + "] RESET-ALL -> L'orario attuale è " + time.toString() + "\n";
		return log;
	}

	/**
	 * @brief Funzione che verifica se si è arrivati a fine giornata
	 * 
	 * @return true se orario del sistema è = 23:59
	 * @return false se orario del sistema è < 23:59
	 */
	bool Home::isDayEnded() const {
		return time == Clock("23:59");
	}

	/**
	 * @brief Funzione membro ausiliaria privata per semplificare l'accensione e lo spegnimento
	 * dei dispositivi della casa
	 * 
	 * Funzionamento:
	 * - controllo se l'evento è accensione o spegnimento -> differenzio i due casi
	 * - verifico che l'operazione faccia cambiare stato al dispositivo -> altrimenti non faccio nulla
	 * - verifico che l'energia assorbita dopo l'operazione non superi il limite -> altrimenti non faccio nulla
	 * - eseguo l'operazione prevista e aggiorno quanto necessario
	 * 
	 * Per la politica di rimpiazzo, è necessario salvare il riferimento dei dispositivi accesi, in ordine di accensione,
	 * in una linked-list, in modo da poterli rimuovere agevolmente se vengono spenti da utente o da timer e poterli
	 * recuperare in ordine di accensione per spegnerli quando si vuole ridurre la potenza consumata.
	 * - quando accendo un dispositivo -> salvo il dispositivo in coda alla lista
	 * - quando riaccendo un dispositivo -> non facco nulla
	 * - quando spengo un dispositivo -> rimuovo il dispositivo dalla lista
	 * - quando rispengo un dispositivo -> non faccio nulla
	 * - quando è necessario ridurre potenza -> estraggo dispositivi dalla testa e li spengo
	 * NB: la politica di spegnimento si applica solo ai dispositivi che consumano, non a quelli che producono.
	 * 
	 * @param d puntatore al dispositivo su cui agire
	 * @param s true -> accensione / false -> spegnimento
	 * @param t orario in cui è effettuata l'azione
	 * @return std::string messaggio di output
	 */
	std::string Home::set(Device *d, bool s, const Clock &t) {
		// messaggio da stampare
		std::string log = "";

		// dispositivo da accendere, quando è spento
		if (s && !d->get_status()) {
			// se assorbimento dalla rete supera il limite -> applico la politica di spegnimento
			if (power_absorption - d->get_energy() - max_power_absorption > 1e-15) {
				log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " non si è acceso perché si supererebbe la potenza massima prelevabile dalla rete\n";
				log += turn_off_policy(t, d->get_energy());
			}

			d->turnOn(t);
			power_absorption -= d->get_energy();
			log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " si è acceso\n";
			if (d->get_energy() < 0) // se consuma, lo inserisco nella lista dei dispositivi che si possono spegnere al bisogno
				turned_on_devices.push_back(d);
		}
		
		// dispositivo da spegnere, quando è acceso
		else if (!s && d->get_status()) {
			// se assorbimento dalla rete supera il limite -> applico la politica di spegnimento
			if (power_absorption + d->get_energy() - max_power_absorption > 1e-15) {
				log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " non si è spento perché si supererebbe la potenza massima prelevabile dalla rete\n";
				log += turn_off_policy(t, d->get_energy());
			}
			
			d->turnOff(t);
			power_absorption += d->get_energy();
			log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " si è spento\n";
			turned_on_devices.remove(d); // se non c'è nella lista, non viene rimosso nulla
		}

		// se dispositivo è già acceso -> non lo riaccendo, ma chiamo lo stesso turnOn per far ripartire il timer nei DeviceCP
		else if (s && d->get_status()) {
			d->turnOn(t);
			log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " è già acceso\n";
		}
		// se dispositivo è già spento -> non lo rispengo
		else if (!s && !d->get_status()) {
			log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " è già spento\n";
		}

		return log;
	}

	/**
	 * @brief Funzione membro ausiliaria privata che applica la politica di spegnimento ai dispositivi,
	 * quando si ha che la potenza assorbita dalla rete supera il limite imposto
	 * 
	 * @param t orario di spegnimento dei dispositivi
	 * @param p potenza assorbita/prodotta dal dispositivo che si vuole spegnere/accendere
	 * @return std::string messaggio di output
	 */
	std::string Home::turn_off_policy(const Clock &t, double p) {
		std::string log = "";

		// se voglio accendere un dispositivo che consuma, devo ridurre la potenza per poterlo accendere senza problemi
		// se voglio spegnere un dispositivo che produce, devo fare in modo che la potenza dei vari dispositivi non superi il massimo
		while (power_absorption + std::abs(p) - max_power_absorption > 1e-15) {
			turned_on_devices.front()->turnOff(t);
			power_absorption += turned_on_devices.front()->get_energy();
			log += "[" + t.toString() + "] Il dispositivo " + turned_on_devices.front()->get_name() + " si è spento per ridurre il consumo del sistema\n";
			turned_on_devices.pop_front();
		}

		return log;
	}
}
