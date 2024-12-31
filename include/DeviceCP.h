/*
	FILE HEADER DEVICECP.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICECP_H
#define DEVICECP_H

#include "Device.h"

namespace device {
	class DeviceCP : public Device {
		private:
			my_clock::Clock cycle;
		public:
			// Costruttore
			DeviceCP(std::string, double, const my_clock::Clock& cycle);

			// Funzione per l'accensione del Dispositivo
			void turnOn(const my_clock::Clock &) override;

			// Funzione per il settaggio dell'ora di accensione del Dispositivo
			void set_onTime(const my_clock::Clock &) override;

			// Funzione per ottenere il ciclo di funzionamento del dispositivo
			my_clock::Clock get_cycle() const;

			// Funzione per ottenere una stringa contenente i dati del Dispositivo
			std::string toString() const override;
	};

	std::ostream &operator<<(std::ostream &, const DeviceCP &);
}

#endif // DEVICECP_H
