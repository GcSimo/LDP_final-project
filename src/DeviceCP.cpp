/*
	FILE SORGENTE DEVICECP.CPP
	Autore:     Giovanni Bordignon

	Implementazione delle funzioni della sottoclasse DeviceCP.
*/

#include "DeviceCP.h"

namespace domotic_home {
	/**
	 * @brief Costruttore della sottoclasse DeviceCP con parametri stringa (--> nome), double (--> energia) e Clock (--> ciclo di funzionamento)
	 * 
	 * @param name stringa 
	 * @param energy consumo energetico istantaneo
	 * @param cycle ciclo di funzionamento prefissato del dispositivo
	 */
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

	/**
	 * @brief Funzione per l'accensione del dispositivo
	 * 
	 * @param t orario di accensione del dispositivo
	 */
	void DeviceCP::turnOn(const Clock & t) {
		// se in precedenza il dispositivo era spento, si aggiorna l'orario dell'ultimo aggiornamento del consumo / produzione
		// infatti se prima era spento, il consumo / produzione non è cambiato dall'ultima volta in cui è stato aggiornato.
		if (!status) {
			lastEnergyUpdate = t;
			status = 1;
		}

		// si imposta (o aggiorna) l'orario di spegnimento
		offTime = t + cycle;
	}

	/**
	 * @brief Funzione per il settaggio dell'orario di accensione del dispositivo
	 * 
	 * @param onTime orario di accensione del dispositivo
	 */
	void DeviceCP::set_onTime(const Clock & onTime) {
		this->onTime = onTime;
		// Calcolo dell'orario di spegnimento del dispositivo
		offTime = onTime + cycle;
	}
}

