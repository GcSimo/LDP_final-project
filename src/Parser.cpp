/*
	FILE SORGENTE PARSER.CPP
	Autore:     Andrea Visonà

	Implementazione delle funzioni della libreria Parser e delle ridefinizione degli operatori disponibili.
*/

#include "Parser.h"
#include <vector>
#include <sstream>

namespace domotic_home {

	/**
	 * @brief funzione ausiliaria per estrarre i nomi dei dipositivi dal comando
	 * il nome si trova in commandLines[start, end)
	 * 
	 * @param commandLines comando sottoforma di vettori di stringhe
	 * @param start indice da cui inizia il nome del dispositivo
	 * @param end indice appena successivo alla fine del nome del dispositivo
	 * @return std::string nome del dispositivo
	 */
	std::string getDevName(const std::vector<std::string>& commandLines, size_t start, size_t end) {
        std::ostringstream devname;
        for (int i=start; i<end; ++i) {
            if (i != start)
                devname << " ";
            devname << commandLines[i];
        }
        return devname.str();
    }

	/**
	 * @brief Funzione che interpreta i comandi inseriti dall'utente e invoca le
	 * corrispettive funzioni sull'oggetto casa
	 * 
	 * @param s stringa con comando inserito dall'utente
	 * @param h oggetto casa su cui invocare i comandi
	 * @return std::string 
	 * @throw ParserError se il comando inserito è errato
	 */
	std::string parser(const std::string &s, domotic_home::Home &h) {
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
		if (commandLines[0] == "set" && commandLines.size() > 2) {
			// -- set time ...
			if (commandLines[1] == "time" && commandLines.size() == 3) {
				out = h.set_time(commandLines[2]);
			}
		
			// --- set devicename on
			else if (commandLines[commandLines.size()-1] == "on") {
				out = h.set(getDevName(commandLines,1,commandLines.size()-1), true);
			}
			
			// --- set devicename off
			else if (commandLines[commandLines.size()-1] == "off") {
				out = h.set(getDevName(commandLines,1,commandLines.size()-1), false);
			}

			// --- set devicename start [stop]
			else if (commandLines.size() >= 3){
				std::string sv = commandLines[commandLines.size()-2];
				bool ifOnlyStart = !std::isdigit(commandLines[commandLines.size()-2][0]);
				if (ifOnlyStart) { // solo start
					out = h.set(getDevName(commandLines,1,commandLines.size()-1), commandLines[commandLines.size()-1]);
				} else { // start e stop
					out = h.set(getDevName(commandLines,1,commandLines.size()-2), commandLines[commandLines.size()-2], commandLines[commandLines.size()-1]);
				}
			}
		}

		// comando rm
		else if (commandLines[0] == "rm" && commandLines.size() > 1) {
			out = h.rm(getDevName(commandLines,1,commandLines.size()));
		}

		// comando show
		else if (commandLines[0] == "show") {
			if (commandLines.size() == 1) // show
				out = h.show();
			else // show devicename
				out = h.show(getDevName(commandLines,1,commandLines.size()));
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

		// comando non valido
		else
			throw ParserError();

		// restituisco output delle invocazioni effettuate
		return out;
	}
}
