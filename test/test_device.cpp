#include <iostream>
#include "DeviceM.h"
#include "DeviceCP.h"

using namespace std;
using namespace domotic_home;

int main () {
	Clock time;

	std::vector<Device *> deviceList = {
		new DeviceM("Impianto_Fotovoltaico", 1.5),
		new DeviceCP("Lavatrice", -2, "1:50"),
		new DeviceCP("Lavastoviglie", -1.5, "3:15"),
		new DeviceM("Pompa di calore + termostato", -2),
		new DeviceCP("Tapparelle elettriche", -0.3, "0:01"),
		new DeviceM("Scaldabagno", -1),
		new DeviceM("Frigorifero", -0.4),
		new DeviceCP("Forno a microonde", -0.8, "0:02"),
		new DeviceCP("Asciugatrice", -0.5, "1:00"),
		new DeviceCP("Televisore", -0.2, "1:00"),
	};

	// ore 0:00
	cout << " -------------------- ORE: " << time << " -------------------- " << endl;
	for (Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;

	// ore 8:00
	time = "8:00";
	cout << " -------------------- ORE: " << time << " -------------------- " << endl;
	for (Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;

	// ore 8:00
	cout << " ---------- accensione dispositivi ------------------ " << endl;
	for (Device *d : deviceList)
		d->turnOn(time);
	for (Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;

	// ore 12:00
	time = "12:00";
	cout << " -------------------- ORE: " << time << " -------------------- " << endl;
	for (Device *d : deviceList)
		cout << *d << endl;
	cout << endl << endl;
}
