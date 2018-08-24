
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
std::vector<cv::Mat> images;

int ProcessArgs(int argc, char **argv);
void ProcessInput();
void Execute(Filter *filter, FilterView *view);

int main(int argc, char **argv){

	Global::Set();	

	try{
		int index = ProcessArgs(argc, argv);

		if(interactive){
			ProcessInput();
		}
		else{
			Global::views[index]->ProcessArgs(argc, argv);
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
	interactive = false;

	std::string flag(argv[1]);
	for(int i = 0; i < Global::views.size(); i++){
		if(flag.compare(Global::views[i]->GetFlag()) == 0){
			return i;
		}
	}
	// if could not find a filter, then it is interactive: get images from the arguments
	for(int i = 1; i < argc; i++){
		cv::Mat image = cv::imread(argv[i], cv::IMREAD_COLOR);
		if(!image.data){
			throw std::invalid_argument("Could not open the image file.");
		}
		images.push_back(image);
	}
	if(images.empty()){
		throw std::invalid_argument("No image file has been loaded");
	}
	interactive = true;
	return -1;
}


void ProcessInput(){
	std::cout << "Interactive mode" << std::endl;
	std::cout << "Available filters: " << std::endl;

	// set applicable filter views that are shown on screen
	std::vector<FilterView*> shown_views;
	std::vector<Filter*> shown_filters;
	for(int i = 0; i < Global::views.size(); i++){
		for(cv::Mat image : images){
			Global::filters[i]->AddImage(image);
		}
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

