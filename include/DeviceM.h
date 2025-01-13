/*
	FILE HEADER DEVICEM.H
	Autore:     Giovanni Bordignon

	La sottoclasse DeviceM permette l'uso di dispositivi manuali, ove dunque è
	possibile programmare un orario di accensione e un orario di spegnimento,
	senza alcun vincolo di funzionamento a ciclo prefissato.
	Nella sottoclasse viene eseguito l'override delle funzioni "turnOn(...)" e
	"set_onTime(...)" e viene resa disponibile la funzione "set_offTime(...)",
	indispensabile per l'uso con i dispositivi manuali.
*/

#ifndef DEVICEM_H
#define DEVICEM_H

#include "Device.h"

namespace domotic_home {
	class DeviceM : public Device {
		public:
			// Costruttore
			DeviceM(std::string, double); // Costruttore con nome (string) e consumo / produzione energetica istantanea (double) come parametri
		
			// Funzione deputata all'accensione del Dispositivo
			void turnOn(const Clock &) override;
		
			// Funzione atta al settaggio dell'orario di accensione del dispositivo
			void set_onTime(const Clock &) override;
		
			// Funzione atta al settaggio dell'orario di spegnimento del dispositivo
			void set_offTime(const Clock &);
	};
}
#endif // DEVICEM_H
