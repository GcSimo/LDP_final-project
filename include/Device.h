/*
	FILE HEADER DEVICE.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICE_H
#define DEVICE_H

#include "Clock.h"

class Device {
	protected:
		// Costruttore protected per non rendere istanziabile la classe
		Device() {};

		// Costanti per i valori di default
		static constexpr int DEFAULT_ENERGY = 0;
		static constexpr int DEFAULT_STATUS = 0;

		// Contatore per assegnare gli ID ai dispositivi
		/*static*/ int ID_Counter;

		// Variabili membro
		std::string name;         // Nome del dispositivo
		static int id;            // Codice ID del dispositivo
		bool status;              // Stato del dispositivo: 1 --> ON, 0 --> OFF
		double energy;            // Valore di consumo / produzione energetica istantanea del dispositivo
		double totalEnergy;       // Valore di consumo / produzione energetica complessiva del dispositivo
		my_clock::Clock lastOn;   // Orario dell'ultima accensione
		my_clock::Clock onTime;   // Orario di accensione del dispositivo

	public:
		// Funzioni deputate all'accensione e allo spegnimento del dispositivo (--> viene modificata variabile booleana "status")
		void turnOn(const my_clock::Clock &);
		void turnOff(const my_clock::Clock &);
		void changeStatus(const my_clock::Clock &);

		// Funzioni atte al settaggio dell'orario di accensione del dispositivo.
		void set_onTime(int, int);
		void set_onTime(const my_clock::Clock &);

		// Funzioni per accesso ai dati del dispositivo
		std::string get_name() const;
		int get_id() const;
		bool get_status() const;
		double get_energy() const;
		my_clock::Clock get_onTime() const;

		// Funzione per ottenere il consumo energetico complessivo ad un orario specifico
		double get_totalEnergy(const my_clock::Clock &);
};

#endif // DEVICE_H
