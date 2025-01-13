/*
	FILE HEADER DEVICECP.H
	Autore:     Giovanni Bordignon

	La sottoclasse DeviceCP consente l'uso e la gestione di dispositivi a
	ciclo prefissato, dove la durata di funzionamento di un dato dispositivo
	risulta essere già prefissata. Le funzioni "turnOn(...)" e "set_turnOn(...)",
	agiscono di conseguenza, impostando automaticamente l'orario di spegnimento
	in funzione del ciclo prefissato di funzionamento. È inoltre presente la
	funzione "get_cycle()" la quale permette di ottenere il ciclo stesso di
	funzionamento, nella forma di oggetto della classe di Clock.
*/

#ifndef DEVICECP_H
#define DEVICECP_H

#include "Device.h"

namespace domotic_home {
	class DeviceCP : public Device {
		private:
			// Variabile membro
			Clock cycle;	// Variabile per il salvataggio della durata del ciclo di funzionamento
		public:
			// Costruttore
			// Costruttore con nome (string), consumo / produzione energetica istantanea (double) e ciclo di funzionamento (Clock) come parametri
			DeviceCP(std::string, double, const Clock &);

			// Funzione deputata all'accensione del Dispositivo
			void turnOn(const Clock &) override;

			// Funzione atta al settaggio dell'orario di accensione del dispositivo
			void set_onTime(const Clock &) override;

			// Funzione per ottenere il ciclo di funzionamento del dispositivo
			Clock get_cycle() const { return cycle; }
	};
}
#endif // DEVICECP_H
