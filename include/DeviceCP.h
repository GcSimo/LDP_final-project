/*
	FILE HEADER DEVICECP.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICECP_H
#define DEVICECP_H

#include "Device.h"

class DeviceCP : public Device {
	private:
		static constexpr char DEFAULT_NAME[] = "DispositivoCP";
		my_clock::Clock cycle;
	public:
		// Costruttori
		//DeviceCP();
		//DeviceCP(std::string, double);
		DeviceCP(std::string name = DEFAULT_NAME, double  energy = DEFAULT_ENERGY);
		DeviceCP(std::string, double, const my_clock::Clock&);

		// Funzioni per il settaggio del ciclo di funzionamento
		void set_cycle(int);                        // Setta ciclo fornendo i minuti di funzionamento
		void set_cycle(int, int);                   // Setta ciclo fornendo ore e minuti di funzionamento
		void set_cycle(const my_clock::Clock&);     // Setta ciclo fornendo un oggetto Clock

		my_clock::Clock get_cycle() const;          // Ritorna l'oggetto Clock del ciclo di funzionamento
		my_clock::Clock get_offTime() const;        // Calcola l'ora di spegnimento del dispositivo
};

#endif // DEVICECP_H
