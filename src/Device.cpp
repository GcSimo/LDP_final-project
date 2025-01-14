/*
	FILE SORGENTE DEVICE.CPP
	Autore:     Giovanni Bordignon

	Implementazione delle funzioni della classe Device.
*/

#include "Device.h"

namespace domotic_home {
	// Definizione della variabile statica ID_Counter
	int Device::ID_Counter = 0;

	/**
	 * @brief Funzione per lo spegnimento del dispositivo; se il dispositivo viene effettivamente spento, si procede poi
	 * all'aggiornamento del consumo / produzione energetica totale del dispositivo.
	 * 
	 * @param t orario di spegnimento
	 */
	void Device::turnOff(const Clock &t) {
		// se il dispositivo risulta acceso, si aggiorna il consumo / produzione complessiva e l'orario dell'ultimo aggiornamento del consumo / produzione
		if (status) {
			totalEnergy += (t - lastEnergyUpdate).toHours() * energy;
			lastEnergyUpdate = t;
			status = 0;
		}
	}

	/**
	 * @brief Funzione per l'aggiornamento del consumo / produzione energetica totale del dispositivo
	 * 
	 * @param t orario a cui si desidera aggiornare il consumo del dispositivo
	 */
	void Device::refreshDevice(const Clock &t) {
		// se il dispositivo risulta acceso, si aggiorna il consumo / produzione (se è spento il consumo / produzione non cambia)
		if (status)
			totalEnergy += (t - lastEnergyUpdate).toHours() * energy;
		
		// si procede ad aggiornare l'orario dell'ultimo aggiornamento del consumo / produzione
		lastEnergyUpdate = t;
	}

	/**
	 * @brief Funzione per il reset degli orari di accensione e spegnimento impostati ad un dispositivo
	 */
	void Device::resetTime() {
		onTime.setInvalid();
		offTime.setInvalid();
	}

	/**
	 * @brief Funzione per il reset del consumo / produzione energetica totale del dispositivo
	 */
	void Device::resetTotalEnergy() {
		totalEnergy = DEFAULT_TOTALT_ENERGY;
		lastEnergyUpdate.setInvalid();
	}
}
