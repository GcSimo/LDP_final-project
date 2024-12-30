/*
	FILE HEADER HOME.H
	Autore:     Andrea Visonà
*/

#ifndef HOME_H
#define HOME_H

#include "Clock.h"
#include "DeviceM.h"
#include "DeviceCP.h"
#include <map>
#include <string>

class Home{
	private:
		my_clock::Clock time;
		std::map<std::string, Device*> devices;
	public:
		Home();
		void listen(std::string);
		void goForward(short);

		class ParserError {};
};

#endif // HOME_H
