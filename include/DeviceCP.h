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
			void turnOn(const Clock &) override;

			// Funzione per il settaggio dell'ora di accensione del Dispositivo
			void set_onTime(const Clock &) override;

			// Funzione per ottenere il ciclo di funzionamento del dispositivo
			Clock get_cycle() const;
	};
}
#endif // DEVICECP_H
