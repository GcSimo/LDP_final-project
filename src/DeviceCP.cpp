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

	void DeviceCP::turnOn(const Clock & t) {
		// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultimo aggiornamento del consumo
		// infatti se prima era spento, il consumo non è cambiato dall'ultima volta in cui è stato aggiornato
		if (!status)
			lastEnergyUpdate = t;
		status = 1;

		// imposto l'orario di spegnimento
		offTime = t + cycle;
	}

	void DeviceCP::set_onTime(const Clock & onTime) {
		this->onTime = onTime;
		offTime = onTime + cycle;
	}

	Clock DeviceCP::get_cycle() const {
		return cycle;
	}
}
