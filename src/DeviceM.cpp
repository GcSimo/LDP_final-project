/*
	FILE HEADER DEVICEM.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceM.h"

namespace device {
	DeviceM::DeviceM(std::string name, double energy) {
		this->name = name;
		id = ID_Counter++;
		status = DEFAULT_STATUS;
		this->energy = energy;
		totalEnergy = DEFAULT_TOTALT_ENERGY;
		onTime.setInvalid();
		offTime.setInvalid();
		lastEnergyUpdate.setInvalid();
	}

	void DeviceM::turnOn(const my_clock::Clock & t) {
		// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultimo aggiornamento del consumo
		// infatti se prima era spento, il consumo non è cambiato dall'ultima volta in cui è stato aggiornato
		if (!status)
			lastEnergyUpdate = t;
		status = 1;
	}

	void DeviceM::set_onTime(const my_clock::Clock & onTime) {
   		this->onTime = onTime;
	}

	void DeviceM::set_offTime(const my_clock::Clock& offTime) {
		this->offTime = offTime;
	}

	std::string DeviceM::toString() const {
		std::string str = "Dispositivo: " + name + "\nID: " + std::to_string(id) + "\nStato attuale: Dispositivo ";
		str += status ? "acceso\n" : "spento\n";
		if (energy > 0) str += "Produzione: " + std::to_string(energy) + "kW\nTot. produzione: " + std::to_string(totalEnergy) + " kWh\n";
		else str += "Consumo: " + std::to_string(energy) + "kW\nTot. consumo: " + std::to_string(totalEnergy) + " kWh\nUltima accensione: ";
		str +=  (lastEnergyUpdate.isValid()) ? lastEnergyUpdate.toString() : "Nessun aggiornamento sul consumo avvenuto";
		str += "\nAccensione programmata: ";
		str += (onTime.isValid()) ? onTime.toString() : "Accensione non programmata";
		str += "\nSpegnimento programmato: ";
		str += (offTime.isValid()) ? offTime.toString() : "Spegnimento non programmato";
		str += "\n";
		return str;
	}

	std::ostream &operator<<(std::ostream &os, const DeviceM &t) {
			return os << t.toString();
	}
}
