#pragma once

#include <string>

class FilterView{
public:
	FilterView(std::string flag = "") : flag(flag) {}
	std::string GetFlag() { return flag; }
	virtual void ProcessArgs(int argc, char **argv) = 0;
	virtual int ProcessInput() = 0;
	virtual void Output() = 0;
protected:
	std::string flag;
};
