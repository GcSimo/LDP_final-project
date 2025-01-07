/*
	FILE HEADER DEVICEM.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICEM_H
#define DEVICEM_H

#include "Device.h"

namespace robotic_home {
	class DeviceM : public Device {
		private:
			// Nulla
		public:
			// Costruttore
			DeviceM(std::string, double); // string --> name, double --> energy
		
			// Funzione per l'accensione del Dispositivo
			bool turnOn(const Clock &) override;
		
			// Funzione per il settaggio dell'ora di accensione del Dispositivo
			void set_onTime(const Clock &) override;
		
			// Funzione per il settaggio dell'ora di spegnimento
			void set_offTime(const Clock&);

			// Funzione per ottenere una stringa contenente i dati del Dispositivo
			std::string toString() const override;
	};
}
#endif // DEVICEM_H
