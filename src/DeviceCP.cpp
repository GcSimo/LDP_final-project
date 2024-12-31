/*
	FILE HEADER DEVICECP.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceCP.h"

namespace device {
	DeviceCP::DeviceCP(std::string name, double energy, const my_clock::Clock& cycle) {
		this->name = name;
		id = ID_Counter++;;
		this->energy = energy;
		totalEnergy = DEFAULT_TOTALT_ENERGY;
		status = DEFAULT_STATUS;
		onTime.setInvalid();
		lastOn.setInvalid();
		offTime.setInvalid();
		this->cycle = cycle;
	}

	void DeviceCP::turnOn(const my_clock::Clock & t) {
		// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultima accensione
		if (!status)
			lastOn = t;
		status = 1;
		offTime = onTime + cycle;
	}

	void DeviceCP::set_onTime(const my_clock::Clock & onTime) /*override*/ {
    		this->onTime = onTime;
		offTime = onTime + cycle;
	}

	my_clock::Clock DeviceCP::get_cycle() const {
		return cycle;
	}

	std::string DeviceCP::toString() const {
		std::string str = "Dispositivo: " + name + "\nID: " + std::to_string(id) + "\nStato attuale: Dispositivo ";
		str += status ? "acceso\n" : "spento\n";
		if (energy > 0) str += "Produzione: " + std::to_string(energy) + "kW\nTot. produzione: " + std::to_string(totalEnergy) + " kWh\n";
		else str += "Consumo: " + std::to_string(energy) + "kW\nTot. consumo: " + std::to_string(totalEnergy) + " kWh\nUltima accensione: ";
		str +=  (lastOn.isValid()) ? lastOn.toString() : "Nessuna accensione avvenuta";
		str += "\nAccensione programmata: ";
		str += (onTime.isValid()) ? onTime.toString() : "Accensione non programmata";
		str += "\nCiclo di funzionamento: " + cycle.toString() +"\nSpegnimento programmato: ";
		str += (offTime.isValid()) ? offTime.toString() : "Spegnimento non programmato";
		str += "\n";
		return str;
	}

	std::ostream &operator<<(std::ostream &os, const DeviceCP &t) {
			return os << t.toString();
	}
}
