/*
	FILE HEADER HOME.CPP
	Autore:     Andrea Visonà
*/

#include "Home.h"
#include <queue>

namespace domotic_home {
	// elenco dispositivi della casa con consumi e durata cicli
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

	/**
	 * @brief Costruttore vuoto della classe Home
	 */
	Home::Home() : Home(MAX_POWER_ABSORPTION) {};

	/**
	 * @brief Costruttore della classe Home con massima potenza assorbibile passata come parametro
	 * @param max_power_absorption massima potenza assorbibile dalla rete
	 */
	Home::Home(double max_power_absorption) {
		// inizializzazioni
		this->time = Clock();
		this->power_absorption = DEFAULT_POWER_ABSORPTION;
		this->max_power_absorption = max_power_absorption;

		// inserisce i dispositivi nella casa
		for (Device *d : deviceList)
			devices.insert({d->get_name(), d});
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
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// effettuo accensione e spegnimento necessari con funzione ausiliaria
		log += set(devices[devicename], new_status, time);

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione per impostare un'accensione programmata del dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @param start orario di accensione
	 * @return std::string messaggio di output
	 * @throw InvalidDeviceName se devicename non è presente nella casa
	 */
	std::string Home::set(const std::string &devicename, const Clock &start) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// imposto orario di accensione
		devices[devicename]->set_onTime(start);
		
		// calcolo messaggio di output
		log += "[" + time.toString() + "] Impostato un timer per il dispositivo " + devicename + " dalle " + devices[devicename]->get_onTime().toString();
		log += (devices[devicename]->get_offTime().isValid() ? " alle " + devices[devicename]->get_offTime().toString() : " in poi") + "\n";

		// se l'orario di accensione è l'orario corrente, il dispositivo viene acceso
		if (time == start)
			log += set(devices[devicename], true, time);

		// restituisco messaggio di output
		return log;
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
	 */
	std::string Home::set(const std::string &devicename, const Clock &start, const Clock &stop) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();
		
		// verifico che il dispositivo sia di tipo manuale
		if (!dynamic_cast<DeviceM *>(devices[devicename]))
			throw InvalidDeviceType();

		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// imposto orari accensione e spegnimento
		DeviceM *temp = dynamic_cast<DeviceM *>(devices[devicename]);
		temp->set_onTime(start);
		temp->set_offTime(stop);
		// variante se set_offTime è virtual e disponibile per classe virtuale Device
		//devices[devicename]->set_onTime(start);
		//devices[devicename]->set_offTime(stop);

		// calcolo messaggio di output
		log += "[" + time.toString() + "] Impostato un timer per il dispositivo " + devicename + " dalle " + devices[devicename]->get_onTime().toString();
		log += (devices[devicename]->get_offTime().isValid() ? " alle " + devices[devicename]->get_offTime().toString() : " in poi") + "\n";

		// se l'orario di accensione è l'orario corrente, il dispositivo viene acceso
		if (time == start)
			log += set(devices[devicename], true, time);

		// restituisco messaggio di output
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
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// resetto il timer del dispositivo
		devices[devicename]->resetTime();

		// calcolo messaggio di output
		log += "[" + time.toString() + "] Rimosso il timer dal dispositivo " + devicename + "\n";

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione per stampare i dispositivi della casa e relativi consumi
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::show() {
		double cons = 0; // consumo complessimo
		double prod = 0; // produzione complessiva

		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";
			
		// calcolo consumo, produzione complessiva e consumo istantaneo
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			if (d.second->get_totalEnergy() < 0)
				cons -= d.second->get_totalEnergy();
			else
				prod += d.second->get_totalEnergy();
		}

		// stampo consumo e produzione del sistema
		log += "[" + time.toString() + "] Attualmente il sistema ha prodotto " + std::to_string(prod)  + " kWh e consumato " + std::to_string(cons) + " kWh. Nello specifico:\n";
		
		// stampo nome, status e consumo individuale dei dispositivi
		// calcolo consumo complessivo e consumo istantaneo
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			log += " - il dispositivo " + d.first + " ha " + (d.second->get_totalEnergy() > 0 ? "prodotto " : "consumato ");
			log += std::to_string(std::abs(d.second->get_totalEnergy())) + " kWh\n";
		}

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione per stampare il consumo di un dispositivo
	 * 
	 * @param devicename nome del dispositivo
	 * @return std::string messaggio di output
	 * @throw InvalidDeviceName se devicename non è presente nella casa
	 */
	std::string Home::show(const std::string &devicename) {
		// verifico presenza dispositivo
		if (!devices.count(devicename))
			throw InvalidDeviceName();

		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// calcolo messaggio di output
		log += "[" + time.toString() + "] Il dispositivo " + devicename + " ha attualmente " + (devices[devicename]->get_totalEnergy() > 0 ? "prodotto " : "consumato ");
		log += std::to_string(std::abs(devices[devicename]->get_totalEnergy())) + "kWh \n";

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione per far avanzare l'orario della casa e accendere/spegnere i dispositivi in base agli orari programmati
	 * 
	 * @param endTime orario di arrivo
	 * @return std::string messaggio di output
	 * @throw TimeRangeError quando si prova a tornare indietro nel tempo
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

		// se orario invalido -> lancio eccezione
		if (startTime > endTime)
			throw TimeRangeError();

		// messaggio da stampare
		std::string log = "[" + startTime.toString() + "] L'orario attuale è " + startTime.toString() + "\n";

		// inserisco i dati nella priority queue
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
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
		for (auto d : devices) { // auto = std::pair<std::string,Device*>
			d.second->refreshDevice(endTime);
		}

		// aggiorno l'orario della casa
		startTime = endTime;

		// aggiungo l'orario finale al messaggio di stampa
		log += "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione di debug per riportare l'orario della casa al valore iniziale (0:00)
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_time() {
		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// spengo i dispotivi e resetto i consumi
		for (auto x : this->devices) {
			x.second->turnOff(this->time);
			x.second->resetTotalEnergy();
		}

		// elimino tutti i dispositivi dalla lista dei dispositivi accesi
		turned_on_devices.clear();

		// resetto i consumi della casa
		power_absorption = DEFAULT_POWER_ABSORPTION;

		// reimposto l'ora della casa
		this->time = Clock();

		// calcolo messaggio di output
		log += "[" + time.toString() + "] RESET-TIME -> L'orario attuale è " + time.toString() + "\n";

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione di debug per resettare i timer di tutti i dispositivi
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_timers() {
		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// reimposto gli orari di accensione e spegnimento programmati di ogni dispotivo
		for (auto x : this->devices){
			x.second->resetTime();
		}

		// calcolo messaggio di output
		log += "[" + time.toString() + "] RESET-TIMERS per tutti i dispositivi\n";

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione per riportare lo stato della casa alle condizioni iniziali
	 * 
	 * @return std::string messaggio di output
	 */
	std::string Home::reset_all() {
		// messaggio da stampare
		std::string log = "[" + time.toString() + "] L'orario attuale è " + time.toString() + "\n";

		// spengo i dispotivi, resetto i consumi e programmi
		for (auto x : this->devices) {
			x.second->turnOff(this->time);
			x.second->resetTotalEnergy();
			x.second->resetTime();
		}

		// elimino tutti i dispositivi dalla lista dei dispositivi accesi
		turned_on_devices.clear();

		// resetto i consumi della casa
		power_absorption = DEFAULT_POWER_ABSORPTION;

		// reimposto l'ora della casa
		this->time = Clock();

		// calcolo messaggio di output
		log += "[" + time.toString() + "] RESET-ALL -> L'orario attuale è " + time.toString() + "\n";

		// restituisco messaggio di output
		return log;
	}

	/**
	 * @brief Funzione che verifica se si è arrivati a fine giornata
	 * 
	 * @return true se orario del sistema è = 23:59
	 * @return false se orario del sistema è < 23:59
	 */
	bool Home::isDayEnded() {
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
			if (power_absorption - d->get_energy() > max_power_absorption) {
				log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " non si è acceso perché si supererebbe la potenza massima asorbibile dalla rete\n";
				log += turn_off_policy(t, d->get_energy());
			}

			d->turnOn(t);
			power_absorption -= d->get_energy();
			if (d->get_energy() < 0) // se consuma, lo inserisco nella lista dei dispositivi che si possono spegnere al bisogno
				turned_on_devices.push_back(d);
			log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " si è acceso\n";
		}
		
		// dispositivo da spegnere, quando è acceso
		else if (!s && d->get_status()) {
			// se assorbimento dalla rete supera il limite -> applico la politica di spegnimento
			if (power_absorption + d->get_energy() > max_power_absorption) {
				log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " non si è spento perché si supererebbe la potenza massima asorbibile dalla rete\n";
				log += turn_off_policy(t, d->get_energy());
			}
			
			d->turnOff(t);
			power_absorption += d->get_energy();
			if (d->get_energy() < 0) // se consuma ovvero se è nella lista, lo rimuovo
				turned_on_devices.remove(d);
			log += "[" + t.toString() + "] Il dispositivo " + d->get_name() + " si è spento\n";
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

		// restituisco messaggio di output
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
		while (power_absorption + std::abs(p) - max_power_absorption > 1e-14) {
			turned_on_devices.front()->turnOff(t);
			power_absorption += turned_on_devices.front()->get_energy();
			log += "[" + t.toString() + "] Il dispositivo " + turned_on_devices.front()->get_name() + " si è spento per ridurre il consumo del sistema\n";
			turned_on_devices.pop_front();
		}

		return log;
	}
}
