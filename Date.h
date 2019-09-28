// Final Project Milestone 1
// Date.h
// 2019/07/11
// Name: Alisa Arutiunian
// Student ID: 149965170
///////////////////////////////////////////////////////////
#ifndef AID_DATE_H
#define AID_DATE_H

#include <iostream>
namespace aid {

	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	const int NO_ERROR = 0;
	const int CIN_FAILED = 1;
	const int DAY_ERROR = 2;
	const int MON_ERROR = 3;
	const int YEAR_ERROR = 4;
	const int PAST_ERROR = 5;


	class Date {

		int YEAR, MONTH, DAY, compare, errState;
		int mday(int y, int d) const;
		void errCode(int);
		bool minDate(int, int, int) const;
		int dateCulc() const;
		bool validYear(int) const;
		bool validMonth(int) const;
		


	public:

		Date();
		Date(int y, int m, int d);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	std::istream& operator>>(std::istream& is, Date&);
	std::ostream& operator<<(std::ostream& os, const Date&);

}
#endif 
