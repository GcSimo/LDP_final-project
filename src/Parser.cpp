/*
	FILE HEADER PARSER.CPP
	Autore:     Andrea Visonà
*/

#include "Parser.h"
#include <vector>
#include <sstream>

namespace domotic_home {
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
			else if (commandLines[2] == "on") {
				out = h.set(commandLines[1], true);
			}
			
			// --- set devicename off
			else if (commandLines[2] == "off") {
				out = h.set(commandLines[1], false);
			}

			// --- set devicename start [stop]
			else {
				if (commandLines.size() == 3) // solo start
					out = h.set(commandLines[1], commandLines[2]);
				else // start e stop
					out = h.set(commandLines[1], commandLines[2], commandLines[3]);
			}
		}

		// comando rm
		else if (commandLines[0] == "rm") {
			out = h.rm(commandLines[1]);
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
