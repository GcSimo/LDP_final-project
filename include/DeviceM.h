/*
	FILE HEADER DEVICEM.H
	Autore:     Giovanni Bordignon
*/

#ifndef DEVICEM_H
#define DEVICEM_H

#include "Device.h"

class DeviceM : public Device {
	private:
		static constexpr char DEFAULT_NAME[] = "DispositivoM";
		my_clock::Clock offTime;
	public:
		// Costruttori
		//DeviceM();
		DeviceM(std::string name = DEFAULT_NAME, double energy = DEFAULT_ENERGY); // string --> name, double --> energy
		
		// Funzioni per il settaggio dell'ora di spegnimento
		void set_offTime(int, int);
		void set_offTime(const my_clock::Clock&);

		my_clock::Clock get_offTime() const;
};

#endif // DEVICEM_H
