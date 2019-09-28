// Final Project Milestone 3
// Good.cpp
// 2019/07/28
// Name: Alisa Arutiunian
// Student ID: 149965170
///////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include "Good.h"
#include "Error.h"

using namespace aid;
using namespace std;

namespace aid {

	//constructors, destructor, assignemt operator
	Good::Good(char type) 
	{
		G_TYPE = type;
		G_SKU[0] = '\0';
		G_UNIT[0] = '\0';
		G_NAME = nullptr;
		G_ONHAND = 0;
		G_NEEDED = 0;
		G_PRICE = 0.0;
		G_TAX_STATUS = false;
	}

	Good::Good(const char* sku, const char* g_name, const char* unit, int onHand, bool taxStatus,
		double itemPrice, int needed)
	{
		strncpy(G_SKU, sku, strlen(sku));
		G_SKU[strlen(sku)] = '\0';

		name(g_name);

		strncpy(G_UNIT, unit, strlen(unit));
		G_UNIT[strlen(unit)] = '\0';

		G_ONHAND = onHand;

		G_TAX_STATUS = taxStatus;

		G_PRICE = itemPrice;

		G_NEEDED = needed;
	}


	Good::Good(const Good& g) 
	{
		G_TYPE = g.G_TYPE;
		strncpy(G_SKU, g.G_SKU, strlen(g.G_SKU));
		G_SKU[strlen(g.G_SKU)] = '\0';

		name(g.G_NAME); 

		strncpy(G_UNIT, g.G_UNIT, strlen(g.G_UNIT));
		G_UNIT[strlen(g.G_UNIT)] = '\0';

		G_ONHAND = g.G_ONHAND;

		G_TAX_STATUS = g.G_TAX_STATUS;

		G_PRICE = g.G_PRICE;

		G_NEEDED = g.G_NEEDED;

	}
	Good& Good::operator= (const Good& rhs)
	{
		if (this == &rhs) 
		{
			return *this;
		}

		delete[] this->G_NAME;

		name(rhs.G_NAME); 
		G_TYPE = rhs.G_TYPE;
		strncpy(G_SKU, rhs.G_SKU, strlen(rhs.G_SKU));
		G_SKU[strlen(rhs.G_SKU)] = '\0';


		strncpy(G_UNIT, rhs.G_UNIT, strlen(rhs.G_UNIT));
		G_UNIT[strlen(rhs.G_UNIT)] = '\0';

		G_ONHAND = rhs.G_ONHAND;

		G_TAX_STATUS = rhs.G_TAX_STATUS;

		G_PRICE = rhs.G_PRICE;

		G_NEEDED = rhs.G_NEEDED;

		return *this;
	}

	Good::~Good()
	{
		delete[] G_NAME;
	}

	// protected member functions
	void Good::name(const char* g_name)
	{
		G_NAME = nullptr; 
		G_NAME = new char[strlen(g_name) + 1];

		if (g_name != nullptr)
		{
			strncpy(G_NAME, g_name, strlen(g_name)); 
			G_NAME[strlen(g_name)] = '\0';

		}
	}

	const char* Good::name() const
	{
		if (G_NAME == '\0') {

			return nullptr;
		}
		else {
			return G_NAME;
		}
	}

	const char* Good::sku() const
	{
		return G_SKU;
	}

	const char* Good::unit() const
	{
		return G_UNIT;
	}

	bool Good::taxed() const
	{
		return G_TAX_STATUS;
	}
	double Good::itemPrice() const
	{
		return G_PRICE;
	}
	double Good::itemCost() const
	{
		return G_TAX_STATUS ? itemPrice() * tax_rate : itemPrice(); //return price+tax unless taxes aren't applicable
	}
	void Good::message(const char* error)
	{
		return ERROR_STATE.message(error); 
	}
	bool Good::isClear() const
	{
		return ERROR_STATE.isClear();
	}

	//stream insertion and extraction operators

	std::fstream& Good::store(std::fstream& file, bool newLine) const
	{
		file << this->G_TYPE << ',' << this->G_SKU << ','
			<< this->G_NAME << ',' << this->G_UNIT << ','
			<< this->G_TAX_STATUS << ',' << this->G_PRICE
			<< ',' << this->G_ONHAND << ',' << this->G_NEEDED;
	
		if (newLine)
		{
			file << endl;
		}

		return file;
	}
	std::fstream& Good::load(std::fstream& file)
	{
		Good temp;
		temp.G_NAME = new char[max_unit_length + 1];
	
	
		file.getline(temp.G_SKU, max_sku_length, ',');
		file.getline(temp.G_NAME, max_unit_length, ',');
		file.getline(temp.G_UNIT, max_unit_length, ',');
		file >> temp.G_TAX_STATUS;
		file.ignore();
		file >> temp.G_PRICE;
		file.ignore();
		file >> temp.G_ONHAND;
		file.ignore();
		file >> temp.G_NEEDED;
		file.ignore();
		
	
		*this = temp;
		
		delete[] temp.G_NAME;
		temp.G_NAME = nullptr;

		return file;
	}
	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		if (!ERROR_STATE.isClear()) 
		{
			os << ERROR_STATE.message();
			return os;
		}
		else if (isEmpty())
		{
			return os;

		} else if (linear)
			{
				os << setfill(' ') << setw(max_sku_length) << left << G_SKU << "|"
					<< setfill(' ') << setw(20) << left << G_NAME << "|"
					<< setfill(' ') << setw(7) << right << fixed << setprecision(2) << itemCost() << "|"
					<< setfill(' ') << setw(4) << right << G_ONHAND << "|"
					<< setfill(' ') << setw(10) << left << G_UNIT << "|"
					<< setfill(' ') << setw(4) << right << G_NEEDED << "|";
			}
			else
			{
				os << " Sku: " << G_UNIT << endl
				<< " Name (no spaces): " << G_NAME << endl
				<< " Price: " << fixed << setprecision(2) << G_PRICE << endl;
					if (G_TAX_STATUS)
					{
						os << " Price after tax: " << fixed << setprecision(2) << itemCost() <<  endl;

					}
					else
					{
						os << " Price after tax: N/A" << endl;
					}

				os << " Quantity on hand: " << G_ONHAND << " " << G_UNIT << endl
				<< " Quantity needed: " << G_NEEDED;
			}
		
		return os;
		
	}
	std::istream& Good::read(std::istream& is)
	{

		char TAX_STATUS;
		char* NAME = new char[max_unit_length + 1];
		Good temp;
		char localType = this->G_TYPE;

	

		cout << "Sku: ";
		is >> temp.G_SKU;
		cin.ignore();

		cout << "Name (no spaces): ";
		is >> NAME;
		temp.name(NAME);

		cout << "Unit: ";
		is >> temp.G_UNIT;

		cout << "Taxed? (y/n): ";
		is >> TAX_STATUS;

		if (TAX_STATUS == 'y' || TAX_STATUS == 'Y')
		{
			temp.G_TAX_STATUS = true;
		} 
		else if (TAX_STATUS == 'n' || TAX_STATUS == 'N')
		{
			temp.G_TAX_STATUS = false;
		}
		else {
			this->ERROR_STATE.clear();
			is.setstate(ios::failbit);
			this->ERROR_STATE.message("Only(Y)es or (N)o are acceptable");
		}
		if (!is.fail())
		{
			cout << "Price: ";
			is >> temp.G_PRICE;
			
			
			if (is.fail())
			{
			this->ERROR_STATE.clear();
			is.setstate(ios::failbit);
			this->ERROR_STATE.message("Invalid Price Entry");
			}
		}

		if (!is.fail())
		{
			
			cout << "Quantity on hand: ";
			is >> temp.G_ONHAND;
			cin.ignore();

			if (is.fail())
			{
				this->ERROR_STATE.clear();
				is.setstate(ios::failbit);
				this->ERROR_STATE.message("Invalid Quantity Entry");
			
			}
		}

		if (!is.fail())
		{
			
			cout << "Quantity needed: ";
			is >> temp.G_NEEDED;

			if (is.fail())
			{
				this->ERROR_STATE.clear();
				is.setstate(ios::failbit);
				this->ERROR_STATE.message("Invalid Quantity Needed Entry");
				
			}
		}
		if (!is.fail()) {
			this->ERROR_STATE.clear();
			*this = temp;
			this->G_TYPE = localType;
		}
	
		
		delete[] NAME;
		NAME = nullptr;
	
		return is;

	}

	//public functions

	bool Good::operator==(const char* str) const
	{
		return (str == this->G_SKU) ? true : false;
	}
	double Good::total_cost() const
	{
		double total = 0.0;
		for (int i = 0; i < G_ONHAND; i++)
		{ 
			total += itemCost();
		}
		return total;  

	}
	void Good::quantity(int onHand)
	{
		if (onHand > 0)
		{
			G_ONHAND = onHand;
		}
	}
	bool Good::isEmpty() const
	{
		return (G_NAME == nullptr) ? true : false;
	}
	int Good::qtyNeeded() const
	{
		return G_NEEDED;
	}
	int Good::quantity() const
	{
		return G_ONHAND;
	}
	bool Good::operator>(const char* str) const
	{
		return (strcmp(G_SKU, str) > 0) ? true : false;
	}
	bool Good::operator>(const iGood& g) const 
	{
		return (strcmp(G_NAME, g.name()) > 0) ? true : false;
	}
	int Good::operator+=(int units) 
	{
		if (units > 0)
		{
			G_ONHAND += units;
			return  G_ONHAND;
		}
		else {
			return  G_ONHAND;
		}

	}

	//helper functions

	std::ostream& operator<<(std::ostream& os, const iGood& g)
	{
		return g.write(os, true);
	}

	std::istream& operator>>(std::istream& is, iGood& g)
	{
		return g.read(is);
		
	}
	double operator+=(double& sum, const iGood& g) 
	{
		return sum + g.total_cost();
	}

}