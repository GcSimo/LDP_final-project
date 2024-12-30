/*
	FILE HEADER CLOCK.CPP
	Autore:     Giovanni Bordignon
*/

#include <algorithm>

#include "Clock.h"

namespace my_clock {
	Clock::Clock(int h, int m) : hour { h }, minute { m } {
		if (h < DEFAULT_VALUE || h > MAX_HOUR) throw HourRangeError(); // Viene resa disponibile un'ora fuori range, come valore non valido.
		if (m < DEFAULT_VALUE || m > MAX_MINUTE) throw MinuteRangeError();

		//hour = h;
		//minute = m;
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
