
#include "blur_view.h"

void BlurFilterView::ProcessArgs(int argc, char **argv){
	int radius;
	float weight;
	cv::Mat image = cv::imread(argv[2], cv::IMREAD_COLOR);
	if(!image.data){
		throw std::invalid_argument("Could not open the image file.");
	}
	if(argc != 5){
		throw std::invalid_argument("Wrong number of arguments. Expected radius and weight for blur operation");
	}
	try{
		radius = std::stoi(std::string(argv[3]));
		weight = std::stof(std::string(argv[4]));
	}catch(std::exception &e){
		throw std::invalid_argument("Expected an int and a float");
	}
	if(radius < 1){
		throw std::invalid_argument("Radius < 1");
	}
	if(weight <= 0.0f){
		throw std::invalid_argument("Weight <= 0");
	}

	if(filter == nullptr){
		throw FilterException("Filter is nullptr");
	}
	filter->AddImage(image);
	filter->SetRadius(radius);
	filter->SetWeight(weight);
}

int BlurFilterView::ProcessInput(){
	int radius;
	float weight;
	try{
		std::cout << "Radius: ";
		std::cin >> radius;
		std::cout << "Weight: ";
		std::cin >> weight;
	}catch(std::exception &e){
		throw std::invalid_argument("Expected an int and a float");
	}

	if(radius < 1){
		throw std::invalid_argument("Radius < 1");
	}
	if(weight <= 0.0f){
		throw std::invalid_argument("Weight <= 0");
	}

	if(filter == nullptr){
		throw FilterException("Filter is nullptr");
	}
	filter->SetRadius(radius);
	filter->SetWeight(weight);
	return 0;
}

void BlurFilterView::Output(){
	cv::imwrite("blurred.png", filter->GetResult());
}
