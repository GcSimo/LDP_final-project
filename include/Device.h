/*
	FILE HEADER DEVICE.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICE_H
#define DEVICE_H

#include "Clock.h"
#include <iostream>

namespace domotic_home {
	class Device {
		protected:
			// Costanti per i valori di default
			static constexpr int DEFAULT_TOTALT_ENERGY = 0;
			static constexpr int DEFAULT_STATUS = 0;

			// Contatore per assegnare gli ID ai dispositivi
			static int ID_Counter;

			// Variabili membro
			std::string name;         // Nome del dispositivo
			int id;                   // Codice ID del dispositivo
			bool status;              // Stato del dispositivo: 1 --> ON, 0 --> OFF
			double energy;            // Valore di consumo / produzione energetica istantanea del dispositivo
			double totalEnergy;       // Valore di consumo / produzione energetica complessiva del dispositivo
			Clock onTime;   // Orario di accensione del dispositivo
			Clock offTime;  // Orario di spegnimento del dispositivo
			Clock lastEnergyUpdate; // Orario dell'ultimo aggiornamento del consumo complessivo

		public:
			// Funzioni deputate all'accensione e allo spegnimento del dispositivo (--> viene modificata variabile booleana "status")
			// Le funzioni ritornano TRUE se lo stato del Dispositivo viene effettivamente modificato, altrimenti FALSE.
			virtual bool turnOn(const Clock &) = 0;
			bool turnOff(const Clock &);

			// Funzione atta al settaggio dell'orario di accensione del dispositivo
			virtual void set_onTime(const Clock &) = 0;

			// Funzione atta ad aggiornare il consumo/produzione complessivo del dispositivo all'orario passato come parametro
			void refreshDevice(const Clock &);

			// Funzione di reset degli orari di accensione e spegnimento impostati
			void resetTime();

			// Funzione di reset dell'energia consumata del dispositivo
			void resetTotalEnergy();

			// Funzioni per accesso ai dati del dispositivo
			std::string get_name() const;
			int get_id() const;
			bool get_status() const;
			double get_energy() const;
			double get_totalEnergy() const;
			Clock get_onTime() const;
			Clock get_offTime() const;

			// Funzione per ottenere una stringa contenente i dati del Dispositivo
			std::string toString() const;
	};

	std::ostream &operator<<(std::ostream &, const Device &);
}

#endif // DEVICE_H
