/*
	FILE HEADER DEVICE.CPP
	Autore:     Giovanni Bordignon
*/

#include "Device.h"

namespace domotic_home {
	int Device::ID_Counter = 0;

	bool Device::turnOff(const Clock &t) {
		// se il dispositivo prima era acceso, aggiorno il consumo complessivo e l'orario dell'ultimo aggiornamento del consumo
		if (status) {
			totalEnergy += (t - lastEnergyUpdate).toHours() * energy;
			lastEnergyUpdate = t;
			status = 0;
			return true;
		}
		return false;
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
	}

	std::string Device::get_name() const {
		return name;
	}

	int Device::get_id() const {
		return id;
	}

	bool Device::get_status() const {
		return status;
	}

	double Device::get_energy() const {
		return energy;
	}

	double Device::get_totalEnergy() const {
		return totalEnergy;
	}

	Clock Device::get_onTime() const {
		return onTime;
	}

	Clock Device::get_offTime() const {
		return offTime;
	}

	std::string Device::toString() const {
		return name;
	}

	std::ostream &operator<<(std::ostream &os, const Device &t) {
		return os << t.toString();
	}
}
