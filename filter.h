#pragma once

#include <string>
#include <exception>
#include <opencv2/opencv.hpp>

class Filter {
public:
	virtual std::string GetFilterName() const = 0;
	virtual bool IsApplicable() const = 0;
	virtual bool Apply() = 0;
	virtual void SetImage(cv::Mat image) = 0;
	virtual void SetFileName(std::string name) {}
};


class FilterView{
public:
	FilterView(std::string flag = "") : flag(flag) {}
	std::string GetFlag() { return flag; }
	virtual void ProcessArgs(std::vector<std::string> arguments) = 0;
	virtual int ProcessInput() = 0;
	virtual void Output() = 0;
protected:
	std::string flag;
};


class FilterException : public std::exception {
public:
	explicit FilterException(const char* msg) : msg(msg) {}
	virtual const char* what() const throw(){ return msg; }
private:
	const char* msg;
};

