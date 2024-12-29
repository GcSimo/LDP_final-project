/*
    FILE HEADER DEVICE.CPP
    Autore:     Giovanni Bordignon
*/

#include "Device.h"

void Device::turnOn(const my_clock::Clock &t) {
	// se prima il dispositivo prima era spento, aggiorno l'orario dell'ultima accensione
	if (!status)
		lastOn = t;
	status = 1;
}

void Device::turnOff(const my_clock::Clock &t) {
	// se il dispositivo prima era acceso, aggiorno il consumo complessivo
	if (status)
		totalEnergy += (t - lastOn).toSeconds() * energy;
    status = 0;
}

void Device::changeStatus(const my_clock::Clock &t) {
	if (status)
		this->turnOff(t);
	else
		this->turnOn(t);
}

void Device::set_onTime(int h, int m) {
    onTime = my_clock::Clock(h, m);
}

void Device::set_onTime(const my_clock::Clock &t) {
    onTime = t;
}

std::string Device::get_name() const {
    return name;
}

int Device::get_id() const {
    return id;
}

bool Device::get_status() const {
    return status;
}

double Device::get_energy() const {
    return energy;
}

my_clock::Clock Device::get_onTime() const {
    return onTime;
}

double Device::get_totalEnergy(const my_clock::Clock &t) {
	// energia consumata nelle vecchie accensioni + quella consumata dall'ultima accensione
	// NB: se il dispositivo è spento, l'energia consumata dall'ultima accensione è 0 perché
	//     moltiplico per status che è per l'appunto 0
	return totalEnergy + (t - lastOn).toSeconds() * energy * status;
}
