/*
	FILE HEADER DEVICE.CPP
	Autore:     Giovanni Bordignon
*/

#include "Device.h"

namespace domotic_home {
	int Device::ID_Counter = 0;

	void Device::turnOff(const Clock &t) {
		// se il dispositivo prima era acceso, aggiorno il consumo complessivo e l'orario dell'ultimo aggiornamento del consumo
		if (status) {
			totalEnergy += (t - lastEnergyUpdate).toHours() * energy;
			lastEnergyUpdate = t;
		}
		status = 0;
	}

	void Device::refreshDevice(const Clock &t) {
		// se il dispositivo è acceso, aggiorno il consumo (se è spento il consumo non cambia)
		if (status)
			totalEnergy += (t - lastEnergyUpdate).toHours() * energy;
		
		// aggiorno l'orario dell'ultimo aggiornamento del consumo
		lastEnergyUpdate = t;
	}

	void Device::resetTime() {
		onTime.setInvalid();
		offTime.setInvalid();
	}

	void Device::resetTotalEnergy() {
		totalEnergy = DEFAULT_TOTALT_ENERGY;
		lastEnergyUpdate.setInvalid();
	}

	std::string Device::toString() const {
		return name;
	}

	std::ostream &operator<<(std::ostream &os, const Device &t) {
		return os << t.toString();
	}
}
