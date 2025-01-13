/*
	FILE HEADER DEVICE.H
	Autore:     Giovanni Bordignon

	La classe base Device rappresenta il fondamento per la gestione dei dispositivi del progetto: essa presente
	le variabili e le funzioni necessarie per una gestione funzionale dei dispositivi. Dovendo interfacciarsi,
	all'interno del progetto, con dispositivi manuali e dispositivi a ciclo prefissato, è risultato necessario
	dichiarare alcune funzioni, quali "turnOn(...)" e "set_onTime(...)", virtuali pure, non risultando possibile
	individuare una base comune nella gestione di tali operazioni per le due diverse tipologie di dispositivo.
	Device sfrutta infine la classe Clock, rendendo più rapido e immediato l'uso e la gestione di orari,
	aspetto indispensabile nel progetto.
*/

#ifndef DEVICE_H
#define DEVICE_H

#include "Clock.h"
#include <iostream>

namespace domotic_home {
	class Device {
		protected:
			// Costanti private per i valori di default
			static constexpr int DEFAULT_TOTALT_ENERGY = 0;
			static constexpr int DEFAULT_STATUS = 0;

			// Contatore per l'assegnazione degli ID ai dispositivi
			static int ID_Counter;

			// Variabili membro private
			std::string name;		// Nome del dispositivo
			int id;					// Codice ID del dispositivo
			bool status;			// Stato del dispositivo: 1 --> ON, 0 --> OFF
			double energy;			// Valore di consumo / produzione energetica istantanea del dispositivo
			double totalEnergy;		// Valore di consumo / produzione energetica complessiva del dispositivo
			Clock onTime;			// Orario di accensione del dispositivo
			Clock offTime;			// Orario di spegnimento del dispositivo
			Clock lastEnergyUpdate;	// Orario dell'ultimo aggiornamento del consumo complessivo

		public:
			// Funzioni deputate all'accensione e allo spegnimento del dispositivo (--> viene modificata variabile booleana "status")
			virtual void turnOn(const Clock &) = 0;
			void turnOff(const Clock &);

			// Funzione atta al settaggio dell'orario di accensione del dispositivo
			virtual void set_onTime(const Clock &) = 0;

			// Funzione atta ad aggiornare il consumo / produzione complessivo del dispositivo all'orario passato come parametro
			void refreshDevice(const Clock &);

			// Funzione di reset degli orari di accensione e spegnimento impostati
			void resetTime();

			// Funzione di reset dell'energia consumata del dispositivo
			void resetTotalEnergy();

			// Funzioni per accesso ai dati del dispositivo
			std::string get_name() const { return name; }			// Funzione per ottenere il nome del dispositivo
			int get_id() const { return id; }						// Funzione per ottenere il codice ID del dispositivo
			bool get_status() const { return status; }				// Funzione per ottenere lo stato attuale del dispositivo
			double get_energy() const { return energy; }			// Funzione per ottenere il valore di consumo / produzione energetica istantanea del dispositivo 
			double get_totalEnergy() const { return totalEnergy; }	// Funzione per ottenere il valore di consumo / produzione energetica complessiva del dispositivo
			Clock get_onTime() const { return onTime; }				// Funzione per ottenere l'orario di accensione del dispositivo
			Clock get_offTime() const { return offTime; }			// Funzione per ottenere l'orario di spegnimento del dispositivo
	};
}

#endif // DEVICE_H
