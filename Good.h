// Final Project Milestone 3
// Good.h
// 2019/07/28
// Name: Alisa Arutiunian
// Student ID: 149965170
///////////////////////////////////////////////////////////

#ifndef AID_GOOD_H
#define AID_GOOD_H
#include <iostream>
#include <cstring>
#include "Error.h"
#include "iGood.h"

namespace aid {

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 1.13; //changed tax rate to 1.13 to simplify further calculations
	
	class Good : public iGood {

		char G_TYPE; // char that indicates type of good
		char G_SKU[max_sku_length + 1]; // good's SKU
		char G_UNIT[max_unit_length + 1]; //good's unit
		char* G_NAME; //pointer that holds the address of dynamically allocated good's name
		int G_ONHAND; // goods on hand
		int G_NEEDED;// goods needed
		double G_PRICE; // goods price before tax
		bool G_TAX_STATUS;// taxable status of goods
		Error ERROR_STATE; // Error object that holds the error state of Good object

	protected:

		void name(const char*); // stores the name of Good in dynamically allocated memory, replaces previously stored name, 
								// if the incoming is null address removes the name of the Good
		const char* name() const; // returns the address of Good name
		const char* sku() const; //returns address of SKU
		const char* unit() const; //returns the address of unit
		bool taxed() const; // returns taxable status
		double itemPrice() const; // returns price of a single item of the Good w/o tax
		double itemCost() const; //price of Good+tax
		void message(const char*); //stores message in Error object of current object
		bool isClear() const; //true if Error is clear, false otherwise

	public:

		Good(char type = 'N'); 
		Good(const char* sku, const char* g_name, const char* unit, int onHand = 0, bool taxStatus = true,
			double itemPrice= 0.0, int needed =0); 
		Good(const Good& g); 
		Good& operator= (const Good& rhs); 
		~Good(); 
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int);

	};

	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);
	double operator+=(double&, const iGood&);
}


#endif 