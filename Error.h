// Final Project Milestone 2
// Error.h
// 2019/07/17
// Name: Alisa Arutiunian
// Student ID: 149965170
///////////////////////////////////////////////////////////

#ifndef AID_ERROR_H
#define AID_ERROR_H
#include <iostream>

namespace aid {
	class Error {

		 char* MESSAGE_ADDRESS;

	public:
		explicit Error(const char* errorMessage = nullptr);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream& os, const Error& er);
}


#endif 
