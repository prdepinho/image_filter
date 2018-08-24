#pragma once

#include <exception>

class FilterException : public std::exception {
public:
	explicit FilterException(const char* msg) : msg(msg) {}
	virtual const char* what() const throw(){ return msg; }
private:
	const char* msg;
};
