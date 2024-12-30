/*
	FILE HEADER CLOCK.CPP
	Autore:     Giovanni Bordignon
*/

#include "Clock.h"

namespace my_clock {
	Clock::Clock(int h, int m) : hour { h }, minute { m } {
		if (h < DEFAULT_VALUE || h > MAX_HOUR) throw HourRangeError(); // Viene resa disponibile un'ora fuori range, come valore non valido.
		if (m < DEFAULT_VALUE || m > MAX_MINUTE) throw MinuteRangeError();
	}

	Clock::Clock(std::string str) {
        	if (str.length() < MIN_LENGTH || str.length() > MAX_LENGTH) throw StringFormatError();
        
       		// Verifica del numero del separatore ":" presente nella stringa

        	/*int numOfColons = 0;
        	for (int i = 0; i < str.length(); i++) {
            		if (str[i] == ':') numOfColons++;
        	}
        	if (numOfColons != 1) throw StringFormatError();*/

        	// Il precedente blocco di istruzioni può essere sostiuito con:
        	if (std::count(str.begin(), str.end(), ':') != MAX_COLONS) throw StringFormatError();

        	// Setto l'ora e i minuti ricevuti con le apposite funzioni
        	set_hour(stoi(str.substr(0, str.find(":"))));   // 0 magic number? Da mettere costante?
        	set_minute(stoi(str.substr(str.find(":") + 1)));
    	}

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

	int Clock::toSeconds() {
		return hour * 3600 + minute * 60;
	}

	void Clock::set24() {
		hour = INVALID_HOUR;
		minute = DEFAULT_VALUE;
	}

	Clock Clock::operator+(const Clock &t) const {
		int h = this->hour + t.hour;
		int m = this->minute + t.minute;
		if (m > 59) {
			h++;
			m -= 60;
		}

		if (h >= 24) {
            		Clock temp;
            		temp.set24();
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
		
		return Clock(h, m);
	}

	bool operator==(const Clock &t1, const Clock &t2) {
		if (t1.get_hour() == t2.get_hour() && t1.get_minute() == t2.get_minute()) return true;
		/*else*/ return false;
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
