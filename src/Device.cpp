/*
	FILE HEADER DEVICE.CPP
	Autore:     Giovanni Bordignon
*/

#include "Device.h"

namespace device {
	int Device::ID_Counter = 0;

	void Device::turnOff(const my_clock::Clock &t) {
		// se il dispositivo prima era acceso, aggiorno il consumo complessivo
		if (status)
			totalEnergy += (t - lastOn).toHours() * energy;
		status = 0;
	}

	void Device::changeStatus(const my_clock::Clock &t) {
		if (status)
			this->turnOff(t);
		else
			this->turnOn(t);
	}

	void Device::refreshDevice(const my_clock::Clock &t) {
		if (t >= onTime)
			this->turnOn(onTime);
		if (t >= offTime)
			this->turnOff(offTime);
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

	my_clock::Clock Device::get_onTime() const {
		return onTime;
	}

	my_clock::Clock Device::get_offTime() const {
		return offTime;
	}

	double Device::get_totalEnergy(const my_clock::Clock &t) {
		/**
		 * calcola l'energia complessiva consumata:
		 * E_tot =  E_vecchie_accensioni + E_utltima_accensione
		 * 
		 * l'energia delle vecchie accensioni viene aggiornata ogni volta che viene eseguito un turnOff
		 * l'energia dell'utltima accensione viene sommata solo se il dispositivo è acceso, infatti se
		 * il dispositivo è spento (status == 0) il valore si annulla perché viene moltiplicato per 0 
		 */
		return totalEnergy + (t - lastOn).toHours() * energy * status;
	}

	std::ostream &operator<<(std::ostream &os, const Device &t) {
		return os << t.toString();
	}
}
