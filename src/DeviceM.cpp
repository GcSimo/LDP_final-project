/*
	FILE HEADER DEVICEM.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceM.h"

DeviceM::DeviceM() {
	name = DEFAULT_NAME;
	id = ID_Counter++;
	status = DEFAULT_STATUS;
	energy = DEFAULT_ENERGY;
	totalEnergy = 0;
	lastOn = onTime = offTime = my_clock::Clock(24, 0);
}

DeviceM::DeviceM(std::string name, double energy) {
	this->name = name;
	id = ID_Counter++;
	status = 0;
	this->energy = energy;
	totalEnergy = 0;
	lastOn = onTime = offTime = my_clock::Clock(24, 0);
}

void DeviceM::set_offTime(int h, int m) {
	offTime = my_clock::Clock(h, m);
}

void DeviceM::set_offTime(const my_clock::Clock& t1) {
	offTime = t1;
}

my_clock::Clock DeviceM::get_offTime() const {
	return offTime;
}
