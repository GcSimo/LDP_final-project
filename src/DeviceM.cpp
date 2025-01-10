/*
	FILE HEADER DEVICEM.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceM.h"

namespace domotic_home {
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

	bool DeviceM::turnOn(const Clock & t) {
		// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultimo aggiornamento del consumo
		// infatti se prima era spento, il consumo non è cambiato dall'ultima volta in cui è stato aggiornato
		if (!status) {
			lastEnergyUpdate = t;
			status = 1;
			return true;
		}
		return false;
	}

	void DeviceM::set_onTime(const Clock & onTime) {
   		this->onTime = onTime;
	}

	void DeviceM::set_offTime(const Clock& offTime) {
		this->offTime = offTime;
	}
}
