/*
	FILE HEADER DEVICECP.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICECP_H
#define DEVICECP_H

#include "Device.h"

namespace domotic_home {
	class DeviceCP : public Device {
		private:
			Clock cycle;
		public:
			// Costruttore
			DeviceCP(std::string, double, const Clock &);

			// Funzione per l'accensione del Dispositivo
			bool turnOn(const Clock &) override;

			// Funzione per il settaggio dell'ora di accensione del Dispositivo
			void set_onTime(const Clock &) override;

			// Funzione per ottenere il ciclo di funzionamento del dispositivo
			Clock get_cycle() const;

			// Funzione per ottenere una stringa contenente i dati del Dispositivo
			std::string toString() const override;
	};
}
#endif // DEVICECP_H
