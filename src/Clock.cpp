/*
	FILE SORGENTE CLOCK.CPP
	Autore:     Andrea Visonà

	Implementazione delle funzioni della classe Clock e delle ridefinizioni degli operatori disponibili.
*/

#include "Clock.h"
#include <regex>

namespace domotic_home {
	/**
	 * @brief Costruttore vuoto della classe CLock
	 */
	Clock::Clock() : hour{ DEFAULT_VALUE }, minute{ DEFAULT_VALUE } { }

	/**
	 * @brief Costruttore della classe Clock con parametri interi h (--> ORA) e m (--> MINUTI)
	 * 
	 * @param h ora
	 * @param m minuti
	 * @throw HourRangeError se l'ora fornita eccede il range ammesso (0 - 23)
	 * @throw MinuteRangeError se il minutaggio fornito eccede il range ammesso (0 - 59)
	 */
	Clock::Clock(int h, int m) : hour{ h }, minute{ m } {
		if (h < DEFAULT_VALUE || h > MAX_HOUR) throw HourRangeError();
		if (m < DEFAULT_VALUE || m > MAX_MINUTE) throw MinuteRangeError();
	}

	/**
	 * @brief Costruttore della classe Clock con parametro stringa, rappresentante un orario opportunamente formattato.
	 * Il costruttore procede alla verifica della stringa fornita come parametro, verificando la corretta formattazione
	 * e la presenza del carattere ' : ', necessario come separatore fra ore e minuti.
	 * 
	 * @param str stringa formattata rappresentante l'orario
	 * @throw StringFormatError se la stringa fornita non rispetta la formattazione ammessa
	 */
	Clock::Clock(std::string str) {
		// Verifica della corretta formattazione della stringa
		if (!std::regex_match(str,std::regex("^([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])$")))
			throw StringFormatError();
		
		// Settaggio dell'ora e dei minuti
		hour = stoi(str.substr(0, str.find(":")));
		minute = stoi(str.substr(str.find(":") + 1));
	}

	/**
	 * @brief Costruttore della classe Clock con parametro const char *s, utile in alcuni casi insieme al costruttore con parametro stringa.
	 * 
	 * @param s char rappresentante l'orario
	 */
	Clock::Clock(const char *s) : Clock(std::string(s)) { }

	/**
	 * @brief Funzione per stampare l'orario opportunamente formattato ("hh:mm")
	 * 
	 * @return std::string orario formattato
	 */
	std::string Clock::toString() const {
		std::string str;
		if (hour < 10) str = "0";
		str += std::to_string(hour) + ":";
		if (minute < 10) str += "0";
		str += std::to_string(minute);
		return str;
	}

	/**
	 * @brief Funzione per il calcolo del tempo espresso in sole ORE.
	 * 
	 * @return double tempo espresso in ore
	 */
	double Clock::toHours() const {
		return static_cast<double>(hour) + static_cast<double>(minute) / 60;
	}

	/**
	 * @brief Funzione per il settaggio dell'ora invalida "24:00".
	 * @return Clock oggetto appena modificato -> così si può fare t = Clock().setInvalid();
	 */
	Clock Clock::setInvalid() {
		hour = INVALID_HOUR;
		minute = DEFAULT_VALUE;

		return *this;
	}

	/**
	 * @brief Funzione per il la verifica se l'ora impostata è valida, cioè se è diversa dall'orario "24:00".
	 * 
	 * @return bool true se hour è diverso da 24 (ora invalida)
	 * @return bool false se hour è uguale a 24 (ora invalida)
	 */
	bool Clock::isValid() const {
		return hour != INVALID_HOUR;
	}

	/**
	 * @brief Ridefinizione operatore somma
	 * 
	 * @param t oggetto Clock da sommare
	 * @return Clock rappresentate il risultato della somma dei due orari
	 */
	Clock Clock::operator+(const Clock &t) const {
		int h = this->hour + t.hour;
		int m = this->minute + t.minute;
		
		// se c'è riporto
		if (m > 59) {
			h++;
			m -= 60;
		}

		// se c'è overflow
		if (h > MAX_HOUR)
			return Clock().setInvalid();
		
		return Clock(h, m);
	}

	/**
	 * @brief Ridefinizione operatore sottrazione
	 * 
	 * @param t oggetto Clock da sottrarre
	 * @return Clock rappresentate il risultato della differenza dei due orari
	 */
	Clock Clock::operator-(const Clock &t) const {
		int h = this->hour - t.hour;
		int m = this->minute - t.minute;
		
		// se c'è riporto
		if (m < 0) {
			h--;
			m += 60;
		}
		
		// se c'è underflow
		if (h < DEFAULT_VALUE)
			return Clock().setInvalid();
		
		return Clock(h, m);
	}

	/**
	 * @brief Ridefinizione operatore uguaglianza
	 * 
	 * @param t1 primo oggetto Clock
	 * @param t2 secondo oggetto Clock
	 * @return true se i due orari sono uguali
	 * @return false se i due orari sono diversi
	 */
	bool operator==(const Clock &t1, const Clock &t2) {
		if (t1.get_hour() == t2.get_hour() && t1.get_minute() == t2.get_minute()) return true;
		return false;
	}

	/**
	 * @brief Ridefinizione operatore maggiore
	 * 
	 * @param t1 primo oggetto Clock
	 * @param t2 secondo oggetto Clock
	 * @return true se t1 è maggiore di t2
	 * @return false se t1 non è maggiore di t2
	 */
	bool operator>(const Clock &t1, const Clock &t2) {
		return !operator<=(t1, t2);
	}

	/**
	 * @brief Ridefinizione operatore minore
	 * 
	 * @param t1 primo oggetto Clock
	 * @param t2 secondo oggetto Clock
	 * @return true se t1 è minore di t2
	 * @return false se t1 non è minore di t2
	 */
	bool operator<(const Clock &t1, const Clock &t2) {
		if (t1.get_hour() < t2.get_hour()) return true;
		if (t1.get_hour() > t2.get_hour()) return false;
		if (t1.get_minute() < t2.get_minute()) return true;
		return false;
	}

	/**
	 * @brief Ridefinizione operatore minore - uguale
	 * 
	 * @param t1 primo oggetto Clock
	 * @param t2 secondo oggetto Clock
	 * @return true se t1 è minore o uguale a t2
	 * @return false se t1 non è minore o uguale a t2
	 */
	bool operator<=(const Clock &t1, const Clock &t2) {
		return operator<(t1, t2) || operator==(t1, t2);
	}

	/**
	 * @brief Ridefinizione operatore maggiore - uguale
	 * 
	 * @param t1 primo oggetto Clock
	 * @param t2 secondo oggetto Clock
	 * @return true se t1 è maggiore o uguale a t2
	 * @return false se t1 non è maggiore o uguale a t2
	 */
	bool operator>=(const Clock &t1, const Clock &t2) {
		return !operator<(t1, t2);
	}

	/**
	 * @brief Ridefinizione operatore <<: passa allo stram di output la stringa formattata dell'orario
	 * 
	 * @param os stream di output del sistema
	 * @param t oggetto Clock
	 * @return ostream
	 */
	std::ostream &operator<<(std::ostream &os, const Clock &t) {
		return os << t.toString();
	}
}
