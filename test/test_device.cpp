#include <iostream>
#include "DeviceM.h"
#include "DeviceCP.h"

using namespace std;

int main () {
	my_clock::Clock time;

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

	for (Device *d : deviceList) {
		cout << d->get_name() << endl
			 << " - id: " << d->get_id() << endl
			 << " - en: " << d->get_energy() << endl
			 << " - st: " << d->get_status() << endl
			 << " - oT: " << d->get_onTime() << endl;
			// << " - tE: " << d->get_totalEnergy(time) << endl;
	}
}
