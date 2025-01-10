/*
	FILE HEADER CLOCK.H
	Autore:     Giovanni Bordignon

	Nel progettare la classe "Dispositivo", si è valutata la realizzazione di una classe, appositamente
	studiata per le esigenze del progetto, atta ad astrarre il concetto di orologio. Sono state dunque
	previste tutte le opportune operazioni, resesi necessarie in un'ottica della massima semplificazione
	della gestione di orari e timer nel restante codice del progetto.

	--- FUNZIONAMENTO ---
	La classe può conservare degli orari nel formato hh:mm (hh --> ore, mm --> minuti), con il formato
	standard a 24 ore. Sono dunque leciti gli orari fra le 0:00 e le 23:59, per esigenze di codifica,
	è resa disponibile l'inserimento di orari nel range 24:00 - 24:59, utile per indicare orari privi
	di significato o per indicare orari che eccedono alla normale scansione oraria giornaliera.

	Funzioni disponibili:
	- hour()      --> ritorna l'ora;
	- minute()    --> ritorna i minuti;
	- toString()  --> ritorna l'ora in forma di stringa "hh:mm";
	- set24()     --> permette di settare l'orologio all'ora invalida (24:00)

	Sono inoltre disponibile le opportune ridefinizioni degli operatori, permettendo di compiere
	l'operazione aritmetica somma, oltre ai diversi confronti possibili, fra due oggetti orologio.
*/

#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <string>
//#include <exception>

namespace domotic_home {
	class Clock {
		private:
			static constexpr int DEFAULT_VALUE = 0;
			static constexpr int MAX_HOUR = 23;
			static constexpr int MAX_MINUTE = 59;
			static constexpr int INVALID_HOUR = 24;

			int hour;
			int minute;

		public:
			// Costruttori
			Clock();
			Clock(int, int);
			Clock(std::string);
			Clock(const char *);

			// Accessors / get functions
			int get_hour() const { return hour; }
			int get_minute() const { return minute; }

			// Mutators / set functions
			void set_hour(int);
			void set_minute(int);

			// Ritorno stringa formattata dell'orario
			std::string toString() const;

			// Conversione in ore (usato per il calcolo della energia consumata)
			double toHours() const;

			// Imposta l'ora invalida 24:00 all'oggetto
			void setInvalid();
			// Controllo validità della funzione
			bool isValid() const;

			// Ridefinizione operatore + e -
			Clock operator+(const Clock &) const;
			Clock operator-(const Clock &) const;

			// Eccezioni disponibili
			class HourRangeError : public std::logic_error {
				public:
					HourRangeError() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: l'ora passata come parametro non rientra nell'intervallo corretto!"; }
			};

			class MinuteRangeError : public std::logic_error {
				public:
					MinuteRangeError() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: i minuti passati come parametro non rientrano nell'intervallo corretto!"; }
			};

			class StringFormatError : public std::logic_error {
				public:
					StringFormatError() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: la stringa non e' formattata correttamente!"; }
			};
	};

	// Ridefinizioni operatori
	bool operator==(const Clock &, const Clock &);
	bool operator>(const Clock &, const Clock &);
	bool operator>=(const Clock &, const Clock &);
	bool operator<(const Clock &, const Clock &);
	bool operator<=(const Clock &, const Clock &);
	std::ostream &operator<<(std::ostream &, const Clock &);
}

#endif // CLOCK_H
