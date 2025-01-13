/*
	FILE SORGENTE DEVICEM.CPP
	Autore:     Giovanni Bordignon

	Implementazione delle funzioni della sottoclasse DeviceM. 
*/

#include "DeviceM.h"

namespace domotic_home {
	/**
	 * @brief Costruttore della sottoclasse DeviceM con parametri stringa (--> nome) e double (--> energia)
	 * 
	 * @param name nome del dispositivo
	 * @param energy consumo istantaneo del dispositivo
	 */
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

	/**
	 * @brief Funzione per l'accensione del dispositivo
	 * 
	 * @param t orario di accensione del dispositivo
	 */
	void DeviceM::turnOn(const Clock & t) {
		// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultimo aggiornamento del consumo
		// infatti se prima era spento, il consumo non è cambiato dall'ultima volta in cui è stato aggiornato
		if (!status)
			lastEnergyUpdate = t;
		status = 1;
	}

	/**
	 * @brief Funzione per il settaggio dell'orario di accensione del dispositivo
	 * 
	 * @param onTime orario di accensione del dispositivo
	 */
	void DeviceM::set_onTime(const Clock & onTime) {
   		this->onTime = onTime;
	}

	/**
	 * @brief Funzione per il settaggio dell'orario di spegnimento del dispositivo
	 * 
	 * @param offTime orario di spegnimento del dispositivo
	 */
	void DeviceM::set_offTime(const Clock & offTime) {
		this->offTime = offTime;
	}
}
