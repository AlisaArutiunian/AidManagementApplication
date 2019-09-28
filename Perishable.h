// Final Project Milestone 5
// Perishable.h
// 2019/07/31
// Name: Alisa Arutiunian
// Student ID: 149965170
///////////////////////////////////////////////////////////


#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H
#include <iostream>
#include <cstring>
#include "Date.h"
#include "Good.h"
#include "iGood.h"

namespace aid {

	class Perishable : public Good
	{

	private:
		Date EXPIRY;

	public:

		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};

	iGood* CreateProduct(char tag);
}

#endif 
