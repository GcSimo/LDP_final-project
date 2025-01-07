/*
	FILE HEADER CLOCK.CPP
	Autore:     Giovanni Bordignon
*/

#include "Clock.h"
#include <algorithm>
#include <regex>

namespace robotic_home {
	Clock::Clock() : hour{DEFAULT_VALUE}, minute{DEFAULT_VALUE} { }

	Clock::Clock(int h, int m) : hour{h}, minute { m } {
		if (h < DEFAULT_VALUE || h > MAX_HOUR) throw HourRangeError(); // Viene resa disponibile un'ora fuori range, come valore non valido.
		if (m < DEFAULT_VALUE || m > MAX_MINUTE) throw MinuteRangeError();
	}

	Clock::Clock(std::string str) {
		// controllo che la stringa sia formattata correttamente
		if (!std::regex_match(str,std::regex("^([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])$")))
			throw StringFormatError();
	
		// Setto l'ora e i minuti ricevuti con le apposite funzioni
		set_hour(stoi(str.substr(0, str.find(":"))));
		set_minute(stoi(str.substr(str.find(":") + 1)));
	}

	Clock::Clock(const char *s) : Clock(std::string(s)) { }

	void Clock::set_hour(int h) {
		if (h < DEFAULT_VALUE || h > MAX_HOUR) throw HourRangeError();
		hour = h;
	}

	void Clock::set_minute(int m) {
		if (m < DEFAULT_VALUE || m > MAX_MINUTE) throw MinuteRangeError();
		minute = m;
	}

	std::string Clock::toString() const {
		std::string str = std::to_string(hour) + ":";
		if (minute < 10) str += "0";
		str += std::to_string(minute);
		return str;
	}

	double Clock::toHours() const {
		return static_cast<double>(hour) + static_cast<double>(minute)/60;
	}

	void Clock::setInvalid() {
		hour = INVALID_HOUR;
		minute = DEFAULT_VALUE;
	}

	bool Clock::isValid() const {
		return hour != INVALID_HOUR;
	}

	Clock Clock::operator+(const Clock &t) const {
		int h = this->hour + t.hour;
		int m = this->minute + t.minute;
		if (m > 59) {
			h++;
			m -= 60;
		}

		if (h > MAX_HOUR) {
			Clock temp;
			temp.setInvalid();
			return temp;
		}
		return Clock(h, m);
	}

	Clock Clock::operator-(const Clock &t) const {
		int h = this->hour - t.hour;
		int m = this->minute - t.minute;
		if (m < 0) {
			h--;
			m += 60;
		}
		
		if (h < DEFAULT_VALUE) {
			Clock temp;
			temp.setInvalid();
			return temp;
		}
		return Clock(h, m);
	}

	bool operator==(const Clock &t1, const Clock &t2) {
		if (t1.get_hour() == t2.get_hour() && t1.get_minute() == t2.get_minute()) return true;
		return false;
	}

	bool operator>(const Clock &t1, const Clock &t2) {
		return !operator<=(t1, t2);
	}

	bool operator<(const Clock &t1, const Clock &t2) {
		if (t1.get_hour() < t2.get_hour()) return true;
		if (t1.get_hour() > t2.get_hour()) return false;
		if (t1.get_minute() < t2.get_minute()) return true;
		return false;
	}

	bool operator<=(const Clock &t1, const Clock &t2) {
		return operator<(t1, t2) || operator==(t1, t2);
	}

	bool operator>=(const Clock &t1, const Clock &t2) {
		return !operator<(t1, t2);
	}

	std::ostream &operator<<(std::ostream &os, const Clock &t) {
		return os << t.toString();
	}
}
