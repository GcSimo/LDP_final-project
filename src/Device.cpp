/*
	FILE HEADER DEVICE.CPP
	Autore:     Giovanni Bordignon
*/

#include "Device.h"

namespace device {
	int Device::ID_Counter = 0;

	void Device::turnOff(const my_clock::Clock &t) {
		// se il dispositivo prima era acceso, aggiorno il consumo complessivo e l'orario dell'ultimo aggiornamento del consumo
		if (status) {
			totalEnergy += (t - lastEnergyUpdate).toHours() * energy;
			lastEnergyUpdate = t;
		}
		status = 0;
	}

	void Device::changeStatus(const my_clock::Clock &t) {
		if (status)
			this->turnOff(t);
		else
			this->turnOn(t);
	}

	void Device::refreshDevice(const my_clock::Clock &t) {
		// se il dispositivo è acceso, aggiorno il consumo (se è spento il consumo non cambia)
		if (status)
			totalEnergy += (t - lastEnergyUpdate).toHours() * energy;
		
		// aggiorno l'orario dell'ultimo aggiornamento del consumo
		lastEnergyUpdate = t;
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

	my_clock::Clock Device::get_onTime() const {
		return onTime;
	}

	my_clock::Clock Device::get_offTime() const {
		return offTime;
	}

	std::ostream &operator<<(std::ostream &os, const Device &t) {
		return os << t.toString();
	}
}
