#pragma once

#include <string>
#include <exception>
#include <opencv2/opencv.hpp>

/*
 * Class Filter has to be implemented by all filters.
 *
 * The main program calls these methods either to start the filter processing, or to give it information.
 * The implemented filter should keep a member for the input image that is set in the method SetImage. This
 * image should be used by IsApplicable and Apply in order to check if the filter works on it and to execute it,
 * respectively. It is also useful to keep a result image attribute to store the output of the filter.
 */
class Filter {
public:
	/* Returns true if the filter is applicable with the input image. */
	virtual bool IsApplicable() const = 0;

	/* The implementation of the filter code that should operate over the input image. */
	virtual bool Apply() = 0;

	/* The input image that should be processed by the filter. */
	virtual void SetImage(cv::Mat image) = 0;

	/* The input image's file name. Implementing this method is not necessary, but useful for naming
	 * the output file, for example. */
	virtual void SetFileName(std::string name) {}
};


/*
 * Class FilterView represents the input and output of information for a filter. 
 *
 * The main program calls these methods in order to pass command line arguments for either interaction mode
 * or to output the result.
 */
class FilterView{
public:
	/* Returns the flag of the filter. It is used to chose the filter in non interactive mode. */
	virtual std::string GetFlag() = 0;

	/* Returns the name of the filter. It appears in the filter options in interactive mode. */
	virtual std::string GetFilterName() const = 0;

	/* This method is called by the program while in interactive mode in order to ask the user which values
	 * should be input to execute the filter. */
	virtual std::vector<std::string> GetParameterNames() const = 0;

	/* This method is called in order to pass the filter its parameters, either
	 * input from command line arguments or obtained interactively. There will
	 * be one parameter value for each parameter name returned by
	 * GetParameterNames. The method should check the validity of each
	 * parameter and throw an exception for any error.  */
	virtual void ProcessArgs(std::vector<std::string> arguments) = 0;

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

