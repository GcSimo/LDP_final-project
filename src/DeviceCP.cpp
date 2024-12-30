/*
	FILE HEADER DEVICECP.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceCP.h"

DeviceCP::DeviceCP() {
	name = DEFAULT_NAME;
	id = ID_Counter++;
	status = DEFAULT_STATUS;
	energy = DEFAULT_ENERGY;
	totalEnergy = 0;
	lastOn = onTime = my_clock::Clock(24, 0);
	cycle = my_clock::Clock(0, 0);
}

DeviceCP::DeviceCP(std::string name, double energy) {
	this->name = name;
	id = ID_Counter++;
	status = 0;
	this->energy = energy;
	totalEnergy = 0;
	lastOn = onTime = my_clock::Clock(24, 0);
	cycle = my_clock::Clock(0, 0);
}

DeviceCP::DeviceCP(std::string name, double energy, const my_clock::Clock& cycle) {
	this->name = name;
	id++;
	this->energy = energy;
	status = 0;
	onTime = my_clock::Clock(24, 0);
	this->cycle = cycle;
}

void DeviceCP::set_cycle(int m) {
	//cycle = Clock(0, m);
	set_cycle(0, m);
}

void DeviceCP::set_cycle(int h, int m) {
	cycle = my_clock::Clock(h, m);
}

void DeviceCP::set_cycle(const my_clock::Clock& cycle) {
	this->cycle = cycle;
}

my_clock::Clock DeviceCP::get_cycle() const {
	return cycle;
}

my_clock::Clock DeviceCP::get_offTime() const {
	return onTime + cycle;
}
