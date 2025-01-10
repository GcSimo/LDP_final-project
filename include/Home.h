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

namespace domotic_home {
	class Home {
		private:
			// costanti private
			static constexpr double DEFAULT_POWER_ABSORPTION = 0;
			static constexpr double MAX_POWER_ABSORPTION = 3.5;
			
			// variabili membro private
			Clock time;
			double power_absorption;
			std::map<std::string, Device*> devices;

			// member function private
			std::string set(Device *, bool, const Clock &); // funzione ausiliaria per on/off dispositivi
		public:
			// costruttore
			Home();

			// member function pubbliche
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

			// classi per lancio di eccezioni
			// se il dispositivo non è presente nella casa
			class InvalidDeviceName : public std::logic_error {
				public:
					InvalidDeviceName() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: il dispositivo non è presente nella casa!"; }
			};

			// se si tenta di impostare un orario di spegnimento programmato ad un dispositivo CP
			class InvalidDeviceType : public std::logic_error {
				public:
					InvalidDeviceType() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: non è possiblie impostare un orario di spegnimento programmato ad un dispositivo CP!"; }
			};

			// quando si inserisce un orario nel passato
			class TimeRangeError : public std::logic_error {
				public:
					TimeRangeError() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: l'ora passata come parametro non rientra nell'intervallo corretto [0:00,23:59]!"; }
			};

	};

	// struct evento da memorizzare nella priority queue per funzione set_time()
	struct event {
		Clock time; // orario dell'evento
		Device *dev; // puntatore al dispositivo su cui agire
		bool command; // true -> turnOn, false -> turnOff
	};

	// funciton object per ordinamento eventi nella priority queue per funzione set_time()
	// l'orario minore è quello con priorità più alta
	struct eventCompare {
		bool operator()(const event &e1, const event &e2) const { return e1.time > e2.time; }
	};
}

#endif // HOME_H
