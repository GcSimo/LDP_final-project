/*
	FILE HEADER PARSER.CPP
	Autore:     Andrea Visonà
*/

#include "Parser.h"
#include <vector>
#include <sstream>

namespace domotic_home {
	const std::string DEVICE_NAME_SEPARATOR = "_";
	void parser(const std::string &s, domotic_home::Home &h) {
		std::vector<std::string> commandLines;
		std::istringstream stream(s);
		std::string line;

		// separa il comando ricevuto come stringa in un vettore di stringhe
		while (std::getline(stream, line, ' ')) {
			commandLines.push_back(line);
		}
		// stringa per messaggio di output
		std::string out = "";

		// comando set
		if (commandLines[0] == "set") {
			// -- set time ...
			if (commandLines[1] == "time") {
				out = h.set_time(commandLines[2]);
			}
		
			// --- set devicename on
			else if (commandLines[commandLines.size()-1] == "on") {
				std::string devname = "";
				for (int i=1 ; i<commandLines.size()-1 ; i++){
					if(i != 1)
						devname += DEVICE_NAME_SEPARATOR;
					devname += commandLines[i];
				}
				out = h.set(devname, true);
			}
			
			// --- set devicename off
			else if (commandLines[commandLines.size()-1] == "off") {
				std::string devname = "";
				for (int i=1 ; i<commandLines.size()-1 ; i++){
					if(i != 1)
						devname += DEVICE_NAME_SEPARATOR;
					devname += commandLines[i];
				}
				out = h.set(devname, false);
			}

			// --- set devicename start [stop]
			else {
				std::string sv = commandLines[commandLines.size()-2];
				bool ifOnlyStart = !sv.empty() && std::find_if(sv.begin(), 
					sv.end(), [](unsigned char c) { return !std::isdigit(c); }) == sv.end();
				if (!ifOnlyStart){ // solo start
					std::string devname = "";
					for (int i=1 ; i<commandLines.size()-1 ; i++){
						if(i != 1)
							devname += DEVICE_NAME_SEPARATOR;
						devname += commandLines[i];
					}
					out = h.set(devname, commandLines[commandLines.size()-1]);
				}else{ // start e stop
					std::string devname = "";
					for (int i=1 ; i<commandLines.size()-1 ; i++){
						if(i != 1)
							devname += DEVICE_NAME_SEPARATOR;
						devname += commandLines[i];
					}
					out = h.set(commandLines[1], commandLines[commandLines.size()-2], commandLines[commandLines.size()-1]);
				}
			}
		}

		// comando rm
		else if (commandLines[0] == "rm") {
			std::string devname = "";
			for (int i=1 ; i<commandLines.size()-1 ; i++){
				if(i != 1)
					devname += DEVICE_NAME_SEPARATOR;
				devname += commandLines[i];
			}
			out = h.rm(devname);
		}

		// comando show
		else if (commandLines[0] == "show") {
			if (commandLines.size() == 1) // show
				out = h.show();
			else // show devicename
				out = h.show(commandLines[1]);
		}

		// comando reset
		else if (commandLines[0] == "reset") {
			if(commandLines[1] == "time"){
				out = h.reset_time();
			}
			else if(commandLines[1] == "timers"){
				out = h.reset_timers();
			}
			else {
				out = h.reset_all();
			}
		}

		std::cout << out << std::endl;
	}
}
