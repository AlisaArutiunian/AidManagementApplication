// Final Project Milestone 5
// Perishable.h
// 2019/07/31
// Name: Alisa Arutiunian
// Student ID: 149965170
///////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include<iomanip>
#include "Perishable.h"

using namespace aid;
using namespace std;

namespace aid {

	Perishable::Perishable() : Good('P') 
	{

		Date();
	}

	//public member functions

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Good::store(file, false);
		file << ',' << EXPIRY;
		if (newLine) {

			file << endl;
		}
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file)
	{
		Good::load(file);
		EXPIRY.read(file);	
		file.ignore();
		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		Good::write(os, linear);
		if (isClear() && !isEmpty()) 
		{
			if (linear)
			{
				EXPIRY.write(os);  
			}
			else {

				os << "\nExpiry date: ";
				EXPIRY.write(os);
			}
		}
		return os;
	}
	std::istream& Perishable::read(std::istream& is)
	{
		Date t;

		Good::read(is);

		if (isClear())
		{
			cout << "Expiry date (YYYY/MM/DD): ";
			t.read(is);


		if (t.bad())
		{
			is.setstate(std::ios::failbit);
			switch (t.errCode())
			{
			case 1 :
				message("Invalid Date Entry");
				break;
			case 2 :
				message("Invalid Day in Date Entry");
				break;
			case 3 :
				message("Invalid Month in Date Entry");
				break;
			case 4 :
				message("Invalid Year in Date Entry");
				break;
			case 5:
				message("Invalid Expiry in Date Entry");
				break;
			}
			is.setstate(std::ios::failbit);
		}
		else
		{
			EXPIRY = t;
		}

		}
		return is;
	}
	const Date& Perishable::expiry() const
	{
		return EXPIRY;
	}

	//free helper func

	iGood* CreateProduct(char tag) 
	{
		if (tag == 'N' || tag == 'n') 
		{
			Good* g = nullptr;
			g = new Good();

			return g;
		}
		else if (tag == 'P' || tag == 'p')
		{
			
			Perishable* p = nullptr;
			p = new Perishable;
			return p;
		}
		else 
		{
			return nullptr;
		}
		
	}
}