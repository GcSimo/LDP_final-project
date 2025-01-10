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

namespace robotic_home{
	class Home {
		private:
			static constexpr double DEFAULT_POWER_ABSORPTION = 0;
			static constexpr double MAX_POWER_ABSORPTION = 3.5;
			
			Clock time;
			double power_absorption;
			std::map<std::string, Device*> devices;
		public:
			Home();
			std::string set(const std::string &, bool); // set devicename on/off
			std::string set(const std::string &, const Clock &); // set devicename start
			std::string set(const std::string &, const Clock &, const Clock &); // set devicename start stop
			std::string rm(const std::string &); // rm devicename
			std::string show(); // show
			std::string show(const std::string &); // show devicename
			std::string set_time(const Clock &); // set time
			std::string reset_time(); // reset time
			std::string reset_timers(); // reset timers
			std::string reset_all(); // reset all

			class InvalidDeviceName {};
			class InvalidDeviceType {};
			class ParserError {};
	};
}

#endif // HOME_H
