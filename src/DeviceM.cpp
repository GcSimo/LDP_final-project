/*
	FILE HEADER DEVICEM.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceM.h"

/*DeviceM::DeviceM() {
	name = DEFAULT_NAME;
	id = ID_Counter++;
	status = DEFAULT_STATUS;
	energy = DEFAULT_ENERGY;
	totalEnergy = DEFAULT_ENERGY;	// Uso la medesima costante di energy anche per totalEnergy
	lastOn.set24();
	onTime.set24();
    	offTime.set24();
}*/

DeviceM::DeviceM(std::string name, double energy) {
	this->name = name;
	id = ID_Counter++;
	status = DEFAULT_STATUS;
	this->energy = energy;
	totalEnergy = DEFAULT_ENERGY;	// Uso la medesima costante di energy anche per totalEnergy
	lastOn.set24();
	onTime.set24();
    	offTime.set24();
}

void DeviceM::set_offTime(int h, int m) {
	offTime = my_clock::Clock(h, m);
}

void DeviceM::set_offTime(const my_clock::Clock& t) {
	offTime = t;
}

my_clock::Clock DeviceM::get_offTime() const {
	return offTime;
}
