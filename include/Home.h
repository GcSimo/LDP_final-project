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
		void listen(const std::string &);
		void goForward(const my_clock::Clock&);

		class ParserError {};
};

#endif // HOME_H
