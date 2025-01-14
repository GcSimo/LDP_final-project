/*
	FILE HEADER CLOCK.H
	Autore:     Giovanni Bordignon

	Nel progettare la classe "Device", si è valutata la realizzazione di una classe, appositamente
	studiata per le esigenze del progetto, atta ad astrarre il concetto di orologio. Sono state dunque
	previste tutte le opportune operazioni, resesi necessarie in un'ottica della massima semplificazione
	della gestione di orari e timer nella restante implementazione del progetto.

	--- FUNZIONAMENTO ---
	La classe può conservare degli orari nel formato hh:mm (hh --> ore, mm --> minuti), con il formato
	standard a 24 ore. Sono dunque leciti gli orari fra le 0:00 e le 23:59; per utilità è possibile inoltre
	settare gli orologi fuori range, all'orario "24:00", possibilità però permessa solo tramite l'ausilio
	dell'apposita funzione setInvalid(). Questa funzionalità risulta particolarmente utile per esplicitare
	orari privi di significato o orari che eccedono alla normale scansione oraria giornaliera.
*/

#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <string>

namespace domotic_home {
	class Clock {
		private:
			// Costanti private per i valori di default
			static constexpr int DEFAULT_VALUE = 0;		// Valore di default per ORA e MINUTI
			static constexpr int MAX_HOUR = 23;		// Valore massimo dell'ORA ammesso
			static constexpr int MAX_MINUTE = 59;		// Valore massimo dei MINUTI ammesso
			static constexpr int INVALID_HOUR = 24;		// Ora invalida

			// Variabili membro
			int hour;	// Variabile per l'ORA
			int minute;	// Variabile per i MINUTI

		public:
			// Costruttori
			Clock();		// Costruttore di default
			Clock(int, int);	// Costruttore con ORE e MINUTI
			Clock(std::string);	// Costruttore con orario fornito tramite stringa formattata
			Clock(const char *);	// Costruttore con orario fornito tramite const char (utile in alcuni contesti)

			// Accessors / get functions
			int get_hour() const { return hour; }		// Funzione per ottenere l'ora
			int get_minute() const { return minute; }	// Funzione per ottenere i minuti

			// Ritorno stringa formattata dell'orario
			std::string toString() const;

			// Conversione in ore (utile per il calcolo della energia consumata)
			double toHours() const;

			// Imposta l'ora invalida 24:00 all'oggetto
			void setInvalid();
			// Controllo validità della funzione
			bool isValid() const;

			// Ridefinizione operatore + e -
			Clock operator+(const Clock &) const;
			Clock operator-(const Clock &) const;

			// Classi interne per le eccezioni disponibili:
			// Eccezione da lanciare se l'ora fornita è fuori dal range (0 - 23)
			class HourRangeError : public std::logic_error {
				public:
					HourRangeError() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: l'ora passata come parametro non rientra nell'intervallo corretto!"; }
			};

			// Eccezione da lanciare se i minuti forniti sono fuori dal range (0 - 59)
			class MinuteRangeError : public std::logic_error {
				public:
					MinuteRangeError() : std::logic_error("") {}
					const char *what() const noexcept override { return "Errore: i minuti passati come parametro non rientrano nell'intervallo corretto!"; }
			};

			// Eccezione da lanciare se stringa fornita non è formattata correttamente
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
