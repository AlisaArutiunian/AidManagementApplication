#include <iostream>
#include <iomanip>
#include "Date.h"

using namespace aid;
using namespace std;

namespace aid {


	int Date::dateCulc() const {

		return YEAR * 372 + MONTH * 31 + DAY;
	}

	int Date::mday(int year, int mon) const {

		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int err) {

		errState = err;
	}

	int Date::errCode() const {
		return errState;
	}

	bool Date::minDate(int year, int mon, int day) const {

	return	((year * 372 + mon * 31 + day) >= min_date) ? true : false;
	}

	bool Date::bad() const {
		return	(errCode() != NO_ERROR) ? true : false;
	}

	bool Date::validYear(int y) const {

		return (y >= min_year && y <= max_year) ? true : false;
	}

	bool Date::validMonth(int m) const {

		return (m >= 1 && m <= 12) ? true : false;
	}

	

	Date::Date() {

		YEAR = 0;
		MONTH = 0;
		DAY = 0;
		compare = 0; 
		errState = NO_ERROR;
	}


	Date::Date(int y, int m, int d) {

		if (!validYear(y)) {

			errCode(YEAR_ERROR);
			*this = Date();
		}
		else if (!validMonth(m)) {
			errCode(MON_ERROR);
			*this = Date();
		}
		else if (d < 1 || d > mday(y, m)) {
			errCode(DAY_ERROR);
			*this = Date();
		}
		else {
			YEAR = y;
			MONTH = m;
			DAY = d;
			dateCulc();
			errCode(NO_ERROR);
		}
	}


	bool Date::operator==(const Date& rhs) const {

		return	this->dateCulc() == rhs.dateCulc() ? true : false;

	}
	bool Date::operator!=(const Date& rhs) const {

		return	this->dateCulc() != rhs.dateCulc() ? true : false;
	}
	bool Date::operator<(const Date& rhs) const {

		return	this->dateCulc() < rhs.dateCulc() ? true : false;
	}
	bool Date::operator>(const Date& rhs) const {

		return	this->dateCulc() > rhs.dateCulc() ? true : false;
	}
	bool Date::operator<=(const Date& rhs) const {

		return	this->dateCulc() <= rhs.dateCulc() ? true : false;
	}
	bool Date::operator>=(const Date& rhs) const {

		return	this->dateCulc() >= rhs.dateCulc() ? true : false;
	}

	std::istream& Date::read(std::istream& istr) {

		char fslash;
		istr.clear();

		istr >> YEAR >> fslash >> MONTH >> fslash >> DAY;

		if (istr.fail()) {
			*this = Date();
			errCode(CIN_FAILED);
		}
		else if (!validYear(YEAR)) {
			*this = Date();
			errCode(YEAR_ERROR);
			return istr;
		}
		else if (!validMonth(MONTH)) {
			*this = Date();
			errCode(MON_ERROR);
			return istr;
		}
		else if (DAY < 1 ||DAY > mday(YEAR, MONTH)) {
			*this = Date();
			errCode(DAY_ERROR);
			return istr;

		}
		else if(!minDate(YEAR, MONTH, DAY)) {
			*this = Date();
			errCode(PAST_ERROR);
			return istr;
		}

	}
	std::ostream& Date::write(std::ostream& ostr) const {

		ostr << YEAR << '/';
		ostr.width(2);
		ostr.fill('0');
		ostr << MONTH << '/';
		ostr.width(2);
		ostr.fill('0');
		ostr <<DAY;

		return ostr;
	}


	std::ostream& operator<<(std::ostream& ostr, const Date& w) {

		return w.write(ostr);

	}

	std::istream& operator>>(std::istream& istr, Date& r) {

		return r.read(istr);

	}
}
