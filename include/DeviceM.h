/*
	FILE HEADER DEVICEM.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICEM_H
#define DEVICEM_H

#include "Device.h"

namespace domotic_home {
	class DeviceM : public Device {
		private:
			// Nulla
		public:
			// Costruttore
			DeviceM(std::string, double); // string --> name, double --> energy
		
			// Funzione per l'accensione del Dispositivo
			void turnOn(const Clock &) override;
		
			// Funzione per il settaggio dell'ora di accensione del Dispositivo
			void set_onTime(const Clock &) override;
		
			// Funzione per il settaggio dell'ora di spegnimento
			void set_offTime(const Clock&);
	};
}
#endif // DEVICEM_H
