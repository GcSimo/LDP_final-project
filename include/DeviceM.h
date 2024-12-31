/*
	FILE HEADER DEVICEM.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICEM_H
#define DEVICEM_H

#include "Device.h"

namespace device {
	class DeviceM : public Device {
		private:
			// Nulla
		public:
			// Costruttore
			DeviceM(std::string, double); // string --> name, double --> energy
		
			// Funzione per l'accensione del Dispositivo
			void turnOn(const my_clock::Clock &) override;
		
			// Funzione per il settaggio dell'ora di accensione del Dispositivo
			void set_onTime(const my_clock::Clock &) override;
		
			// Funzione per il settaggio dell'ora di spegnimento
			void set_offTime(const my_clock::Clock&);

			// Funzione per ottenere una stringa contenente i dati del Dispositivo
			std::string toString() const override;
	};

	std::ostream &operator<<(std::ostream &, const DeviceM &);
}
#endif // DEVICEM_H
