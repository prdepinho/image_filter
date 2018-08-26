
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "filter.h"
#include "global_filters.h"

#define SHOW_INPUT_TYPE false

bool interactive;
std::string filename;
std::vector<std::string> arguments;


int ProcessArgs(int argc, char **argv);
void SetImageToFilters();
void ProcessInteraction();
void ExecuteFilter(Filter *filter);
inline void ShowType(cv::Mat image);

int main(int argc, char **argv){

	Global::SetFilters();

	try{

		int index = ProcessArgs(argc, argv);
		SetImageToFilters();

		if(interactive){
			ProcessInteraction();
		}
		else{
			Global::filters[index]->SetParameters(arguments);
			ExecuteFilter(Global::filters[index]);
		}

		

	}catch(const FilterException &e){
		std::cout << "Filter exception: " << e.what() << std::endl;
		return 1;
	}catch(const std::invalid_argument &e){
		std::cout << "Invalid argument: " << e.what() << std::endl;
		return 2;
	}catch(const std::out_of_range &e){
		std::cout << "Index out of range: " << e.what() << std::endl;
		return 3;
	}catch(const std::exception &e){
		std::cout << "Error: " << e.what() << std::endl;
		return 4;
	}

	return 0;
}

int ProcessArgs(int argc, char **argv){
	if (argc < 2){
		throw std::invalid_argument("Expected a flag or a list of filenames");
	}

	// check if there is a flag
	std::string flag(argv[1]);
	int filter_index = -1;
	for(int i = 0; i < Global::filters.size(); i++){
		if(flag.compare(Global::filters[i]->GetFlag()) == 0){
			filter_index = i;
		}
	}

	// get input filename
	int index = (filter_index >= 0) ? 2 : 1;
	filename = std::string(argv[index]);

	if(filter_index < 0){
		interactive = true;
		return -1;
	}

	// if it is non interactive: get arguments
	for(index += 1; index < argc; index++){
		arguments.push_back(std::string(argv[index]));
	}

	interactive = false;
	return filter_index;
}

void SetImageToFilters(){
	cv::Mat image = cv::imread(filename, cv::IMREAD_UNCHANGED);
	if(!image.data){
		throw std::invalid_argument("Could not open the image file.");
	}
	ShowType(image);
	for(Filter *filter : Global::filters){
		filter->SetImage(image);
		filter->SetFileName(filename);
	}
}

void ProcessInteraction(){
	std::cout << "Interactive mode" << std::endl;

	// set applicable filter filters that are shown on screen
	std::vector<Filter*> shown_filters;
	for(int i = 0; i < Global::filters.size(); i++){
		if (Global::filters[i]->IsApplicable()){
			shown_filters.push_back(Global::filters[i]);
		}
	}
	if(shown_filters.empty()){
		std::cout << "No filters available for input images" << std::endl;
		return;
	}
	std::cout << "Available filters: " << std::endl;
	for(int i = 0; i < shown_filters.size(); i++){
		std::cout << i + 1 << ": " << shown_filters[i]->GetFilterName() << std::endl;
	}
	std::cout << "0: Exit." << std::endl;

	// read selected filter
	int index = 0;
	std::cin >> index;
	if(index == 0){
		return;
	}
	index -= 1;
	if(index < 0 || index >= shown_filters.size()){
		throw std::out_of_range("No filter selected");
	}
	std::cout << shown_filters[index]->GetFlag() << " chosen" << std::endl;

	// read parameters
	std::vector<std::string> parameter_names = shown_filters[index]->GetParameterNames();
	if(!parameter_names.empty()){
		std::cout << "Input parameters. To quit input 'q'." << std::endl;
		std::vector<std::string> parameter_values;
		for(std::string name : parameter_names){
			std::cout << name << ": ";
			std::string input;
			std::cin >> input;
			if(input.compare("q") == 0){
				return;
			}
			parameter_values.push_back(input);
		}
		shown_filters[index]->SetParameters(parameter_values); 
	}

	ExecuteFilter(shown_filters[index]);
}

void ExecuteFilter(Filter *filter){
	if(!filter->IsApplicable()){
		throw FilterException("Filter is not applicable to input");
	}
	std::cout << "Working..." << std::endl;
	filter->Apply();
	filter->Output();
	std::cout << "Finished." << std::endl;
}

inline void ShowType(cv::Mat image){
#if SHOW_INPUT_TYPE
	std::cout << "input type: " << image.type() << std::endl;

	std::cout << "CV_16SC1: " << CV_16SC1 << std::endl;
	std::cout << "CV_16SC2: " << CV_16SC2 << std::endl;
	std::cout << "CV_16SC3: " << CV_16SC3 << std::endl;
	std::cout << "CV_16SC4: " << CV_16SC4 << std::endl;

	std::cout << "CV_16UC1: " << CV_16UC1 << std::endl;
	std::cout << "CV_16UC2: " << CV_16UC2 << std::endl;
	std::cout << "CV_16UC3: " << CV_16UC3 << std::endl;
	std::cout << "CV_16UC4: " << CV_16UC4 << std::endl;

	std::cout << "CV_32FC1: " << CV_32FC1 << std::endl;
	std::cout << "CV_32FC2: " << CV_32FC2 << std::endl;
	std::cout << "CV_32FC3: " << CV_32FC3 << std::endl;
	std::cout << "CV_32FC4: " << CV_32FC4 << std::endl;

	std::cout << "CV_32SC1: " << CV_32SC1 << std::endl;
	std::cout << "CV_32SC2: " << CV_32SC2 << std::endl;
	std::cout << "CV_32SC3: " << CV_32SC3 << std::endl;
	std::cout << "CV_32SC4: " << CV_32SC4 << std::endl;

	std::cout << "CV_64FC1: " << CV_64FC1 << std::endl;
	std::cout << "CV_64FC2: " << CV_64FC2 << std::endl;
	std::cout << "CV_64FC3: " << CV_64FC3 << std::endl;
	std::cout << "CV_64FC4: " << CV_64FC4 << std::endl;

	std::cout << "CV_8SC1: " << CV_8SC1 << std::endl;
	std::cout << "CV_8SC2: " << CV_8SC2 << std::endl;
	std::cout << "CV_8SC3: " << CV_8SC3 << std::endl;
	std::cout << "CV_8SC4: " << CV_8SC4 << std::endl;

	std::cout << "CV_8UC1: " << CV_8UC1 << std::endl;
	std::cout << "CV_8UC2: " << CV_8UC2 << std::endl;
	std::cout << "CV_8UC3: " << CV_8UC3 << std::endl;
	std::cout << "CV_8UC4: " << CV_8UC4 << std::endl;
#endif
}

