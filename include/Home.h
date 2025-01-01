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
		static constexpr double DEFAULT_POWER_ABSORPTION = 0;
		static constexpr double MAX_POWER_ABSORPTION = 3.5;
		
		double power_absorption;
		my_clock::Clock time;
		std::map<std::string, device::Device*> devices;
	public:
		Home();
		void listen(const std::string &);
		void goForward(const my_clock::Clock&);

		class ParserError {};
};

#endif // HOME_H
