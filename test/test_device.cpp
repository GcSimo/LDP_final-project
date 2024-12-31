#include <iostream>
#include "DeviceM.h"
#include "DeviceCP.h"

using namespace std;

int main () {
	my_clock::Clock time;

	std::vector<device::Device *> deviceList = {
		new device::DeviceM("Impianto_Fotovoltaico", 1.5),
		new device::DeviceCP("Lavatrice", -2, "1:50"),
		new device::DeviceCP("Lavastoviglie", -1.5, "3:15"),
		new device::DeviceM("Pompa di calore + termostato", -2),
		new device::DeviceCP("Tapparelle elettriche", -0.3, "0:01"),
		new device::DeviceM("Scaldabagno", -1),
		new device::DeviceM("Frigorifero", -0.4),
		new device::DeviceCP("Forno a microonde", -0.8, "0:02"),
		new device::DeviceCP("Asciugatrice", -0.5, "1:00"),
		new device::DeviceCP("Televisore", -0.2, "1:00"),
	};

	// ore 0:00
	cout << " -------------------- ORE: " << time << " -------------------- " << endl;
	for (device::Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;

	// ore 8:00
	time = "8:00";
	cout << " -------------------- ORE: " << time << " -------------------- " << endl;
	for (device::Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;

	// ore 8:00
	cout << " ---------- accensione dispositivi ------------------ " << endl;
	for (device::Device *d : deviceList)
		d->turnOn(time);
	for (device::Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;

	// ore 12:00
	time = "12:00";
	cout << " -------------------- ORE: " << time << " -------------------- " << endl;
	for (device::Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;
}
