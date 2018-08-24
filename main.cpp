
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "filter.h"
#include "filter_view.h"
#include "global_filters.h"

bool interactive;
std::vector<std::string> filenames;
std::vector<std::string> arguments;

int ProcessArgs(int argc, char **argv);
void SetImagesToFilters();
void ProcessInput();
void Execute(Filter *filter, FilterView *view);

int main(int argc, char **argv){

	Global::Set();	

	try{
		int index = ProcessArgs(argc, argv);
		SetImagesToFilters();

		if(interactive){
			ProcessInput();
		}
		else{
			Global::views[index]->ProcessArgs(arguments);
			Execute(Global::filters[index], Global::views[index]);
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
	int index = -1;
	for(int i = 0; i < Global::views.size(); i++){
		if(flag.compare(Global::views[i]->GetFlag()) == 0){
			index = i;
		}
	}

	// loop through argv
	int i = (index >= 0) ? 2 : 1;
	// get filenames 
	while(i < argc && std::string(argv[i]).compare("-args") != 0){
		filenames.push_back(std::string(argv[i]));
		i++;
	}
	if(filenames.empty()){
		throw std::invalid_argument("No image file has been loaded");
	}

	if(index < 0){
		interactive = true;
		return -1;
	}

	// it is non interactive: get arguments
	for(i += 1; i < argc; i++){
		arguments.push_back(std::string(argv[i]));
	}

	interactive = false;
	return index;
}

void SetImagesToFilters(){
	for(Filter *filter : Global::filters){
		for(std::string name : filenames){
			cv::Mat image = cv::imread(name.c_str(), cv::IMREAD_COLOR);
			if(!image.data){
				throw std::invalid_argument("Could not open the image file.");
			}
			filter->AddImage(image);
			filter->AddName(name);
		}
	}
}

void ProcessInput(){
	std::cout << "Interactive mode" << std::endl;
	std::cout << "Available filters: " << std::endl;

	// set applicable filter views that are shown on screen
	std::vector<FilterView*> shown_views;
	std::vector<Filter*> shown_filters;
	for(int i = 0; i < Global::views.size(); i++){
		if (Global::filters[i]->IsApplicable()){
			shown_views.push_back(Global::views[i]);
			shown_filters.push_back(Global::filters[i]);
		}
	}
	// show filter views
	for(int i = 0; i < shown_views.size(); i++){
		std::cout << i << ": " << shown_views[i]->GetFlag() << std::endl;
	}
	// get input
	int index;
	std::cin >> index;
	if(index < 0 || index >= shown_views.size()){
		throw std::out_of_range("No filter selected");
	}
	std::cout << shown_views[index]->GetFlag() << " chosen" << std::endl;
	if(shown_views[index]->ProcessInput() == 0){
		Execute(shown_filters[index], shown_views[index]);
	}
}

void Execute(Filter *filter, FilterView *view){
	if(!filter->IsApplicable()){
		throw FilterException("Filter is not applicable to input");
	}
	std::cout << "Working..." << std::endl;
	filter->Apply();
	view->Output();
	std::cout << "Finished." << std::endl;
}

