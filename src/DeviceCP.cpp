/*
	FILE HEADER DEVICECP.CPP
	Autore:     Giovanni Bordignon
*/

#include "DeviceCP.h"

DeviceCP::DeviceCP(std::string name, double energy, const my_clock::Clock& cycle) {
	this->name = name;
	id = ID_Counter++;;
	this->energy = energy;
	totalEnergy = DEFAULT_TOTALT_ENERGY;
	status = DEFAULT_STATUS;
	onTime.set24();
	lastOn.set24();
	this->cycle = cycle;
}

void DeviceCP::turnOn(const my_clock::Clock & t) {
	// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultima accensione
	if (!status)
		lastOn = t;
	status = 1;
	offTime = onTime + cycle;
}

void DeviceCP::set_onTime(const my_clock::Clock & onTime) /*override*/ {
    this->onTime = onTime;
	offTime = onTime + cycle;
}

my_clock::Clock DeviceCP::get_cycle() const {
	return cycle;
}

std::string DeviceCP::toString() const {
	std::string str = "Dispositivo: " + name + "\nID: " + std::to_string(id) + "\nStato attuale: Dispositivo ";
	if (status) str += "acceso\n";
	else str += "spento\n";
	if (energy > 0) str += "Produzione: " + std::to_string(energy) + "kW\nTot. produzione: " + std::to_string(totalEnergy) + " kWh\n";
	else str += "Consumo: " + std::to_string(energy) + "kW\nTot. consumo: " + std::to_string(totalEnergy) + " kWh\n";
	str += "Ultima accensione: " + lastOn.toString() + "\nAccensione programmata: " + onTime.toString() + "\nCiclo funzionamento: " + cycle.toString() + "\nSpegnimento programmato: " + offTime.toString() + "\n";
	return str;
	// Togliere ultima accensione ore 24:00
}

std::ostream &operator<<(std::ostream &os, const DeviceCP &t) {
		return os << t.toString();
}
