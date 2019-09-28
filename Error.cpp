// Final Project Milestone 2
// Error.cpp
// 2019/07/17
// Name: Alisa Arutiunian
// Student ID: 149965170
///////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Error.h"

using namespace aid;
using namespace std;

namespace aid {

	 Error::Error(const char* errorMessage) {

		if ((errorMessage != nullptr) && (*errorMessage != '\0'))
		{

			MESSAGE_ADDRESS = new char[strlen(errorMessage) + 1];
			strncpy(MESSAGE_ADDRESS, errorMessage, strlen(errorMessage));
			MESSAGE_ADDRESS[strlen(errorMessage)] = '\0';

		}
		else {

			
			MESSAGE_ADDRESS = nullptr;

		}

	}


	Error::~Error(){

		delete[] MESSAGE_ADDRESS;
		MESSAGE_ADDRESS = nullptr;
	}

	void Error::clear() {

		delete[] MESSAGE_ADDRESS;
		MESSAGE_ADDRESS = nullptr;

	}

	bool Error::isClear() const{

		return (MESSAGE_ADDRESS == '\0') ? true : false;
	}
	
		void Error::message(const char* str) {

			delete[] MESSAGE_ADDRESS;
			MESSAGE_ADDRESS = nullptr;

			if (*str != '\0')
			{
				MESSAGE_ADDRESS = new char[strlen(str) + 1];
				strncpy(MESSAGE_ADDRESS, str, strlen(str));
				MESSAGE_ADDRESS[strlen(str)] = '\0';

			}
			else {

				MESSAGE_ADDRESS = nullptr;
			}

	}
		const char* Error::message() const {

			if (MESSAGE_ADDRESS != nullptr) {

				return MESSAGE_ADDRESS;
			}
			else {
				return nullptr;
			}
		}

		std::ostream& operator<<(std::ostream& os, const Error& er) {

			if (!er.isClear()) {
				os << er.message();
				return os;
			}

			return os;
		}

};

