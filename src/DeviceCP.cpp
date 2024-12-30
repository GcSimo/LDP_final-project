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
	totalEnergy = DEFAULT_ENERGY;	// Uso la medesima costante di energy anche per totalEnergy
	lastOn.set24();
	onTime.set24();
	//cycle = my_clock::Clock(0, 0);	--> NON Necessario --> Costruttore default
}

DeviceCP::DeviceCP(std::string name, double energy) {
	this->name = name;
	id = ID_Counter++;
	status = DEFAULT_STATUS;
	this->energy = energy;
	totalEnergy = DEFAULT_ENERGY;	// Uso la medesima costante di energy anche per totalEnergy
	lastOn.set24();
	onTime.set24();
	//cycle = my_clock::Clock(0, 0);	--> NON Necessario --> Costruttore default
}

DeviceCP::DeviceCP(std::string name, double energy, const my_clock::Clock& cycle) {
	this->name = name;
	id++;
	this->energy = energy;
	status = DEFAULT_STATUS;
	onTime.set24();
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
