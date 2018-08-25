#pragma once

#include <string>
#include <exception>
#include <opencv2/opencv.hpp>

/*
 * Class Filter has to be implemented by all filters.
 *
 * The main program calls these methods or in order to call a service of the filter, or to give it information.
 * The implemented filter should keep a member for the input image that is set in the SetImage method. This
 * image should be used by IsApplicable and Apply in order to check if the filter works on it and to apply it
 * respectively.
 */
class Filter {
public:
	/* Returns true if the filter is applicable with the input image. */
	virtual bool IsApplicable() const = 0;

	/* This function must implement the code of the filter that should operate over the input image. */
	virtual bool Apply() = 0;

	/* Sets the input image that should be processed by the filter. */
	virtual void SetImage(cv::Mat image) = 0;

	/* Sets the input image's file name. Implementing this method is not necessary, but useful for naming
	 * the output file, for example. */
	virtual void SetFileName(std::string name) {}
};


/*
 * Class FilterView represents the input and output of information for a filter. 
 *
 * The main program calls these methods in order to pass command line arguments for the non interactive mode 
 * or to call input from the user in the interactive mode.
 */
class FilterView{
public:
	/* Returns the flag of the filter. It is used to chose the filter in non interactive mode. */
	virtual std::string GetFlag() = 0;

	/* Returns the name of the filter. It appears in the filter options in interactive mode. */
	virtual std::string GetFilterName() const = 0;

	/* This method is called to pass command line arguments to the filter. The method should check if
	 * all the parameters necessary for the filter are present and throw an exception otherwise. */
	virtual void ProcessArgs(std::vector<std::string> arguments) = 0;

	/* This method is called in interactive mode and should ask the user for the necessary parameter for
	 * the filter by means of standard input. This method should return zero in order to execute the filter. */
	virtual int ProcessInput() = 0;

	/* This method is called after the execution of the filter and can be used to save the output file. */
	virtual void Output() = 0;
};


class FilterException : public std::exception {
public:
	explicit FilterException(const char* msg) : msg(msg) {}
	virtual const char* what() const throw(){ return msg; }
private:
	const char* msg;
};

