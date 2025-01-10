/*
	FILE HEADER DEVICECP.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceCP.h"

namespace domotic_home {
	DeviceCP::DeviceCP(std::string name, double energy, const Clock& cycle) {
		this->name = name;
		id = ID_Counter++;;
		status = DEFAULT_STATUS;
		this->energy = energy;
		totalEnergy = DEFAULT_TOTALT_ENERGY;
		onTime.setInvalid();
		offTime.setInvalid();
		lastEnergyUpdate.setInvalid();
		this->cycle = cycle;
	}

	bool DeviceCP::turnOn(const Clock & t) {
		// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultimo aggiornamento del consumo
		// infatti se prima era spento, il consumo non è cambiato dall'ultima volta in cui è stato aggiornato
		if (!status) {
			lastEnergyUpdate = t;
			status = 1;
			// Imposto l'orario di spegnimento
			offTime = t + cycle;
			return true;
		}

		// imposto l'orario di spegnimento
		offTime = t + cycle;

		return false;
	}

	void DeviceCP::set_onTime(const Clock & onTime) {
		this->onTime = onTime;
		offTime = onTime + cycle;
	}

	Clock DeviceCP::get_cycle() const {
		return cycle;
	}

	std::string DeviceCP::toString() const {
		std::string str = "Dispositivo: " + name + "\nID: " + std::to_string(id) + "\nStato attuale: Dispositivo ";
		str += status ? "acceso\n" : "spento\n";
		if (energy > 0) str += "Produzione: " + std::to_string(energy) + "kW\nTot. produzione: " + std::to_string(totalEnergy) + " kWh\n";
		else str += "Consumo: " + std::to_string(energy) + "kW\nTot. consumo: " + std::to_string(totalEnergy) + " kWh\nUltima accensione: ";
		str +=  (lastEnergyUpdate.isValid()) ? lastEnergyUpdate.toString() : "Nessun aggiornamento sul consumo avvenuto";
		str += "\nAccensione programmata: ";
		str += (onTime.isValid()) ? onTime.toString() : "Accensione non programmata";
		str += "\nCiclo di funzionamento: " + cycle.toString() +"\nSpegnimento programmato: ";
		str += (offTime.isValid()) ? offTime.toString() : "Spegnimento non programmato";
		str += "\n";
		return str;
	}
}
