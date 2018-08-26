
#include "blur_view.h"

void BlurFilterView::ProcessArgs(std::vector<std::string> arguments){
	int radius;
	float weight;
	if(arguments.size() < 2){
		throw std::invalid_argument("Wrong number of arguments. Expected radius and weight for blur operation");
	}
	try{
		radius = std::stoi(arguments[0]);
		weight = std::stof(arguments[1]);
	}catch(std::exception &e){
		throw std::invalid_argument("Expected an int and a float");
	}

	if(radius < 1){
		throw std::invalid_argument("Radius < 1");
	}
	if(weight <= 0.0f){
		throw std::invalid_argument("Weight <= 0");
	}

	filter->SetRadius(radius);
	filter->SetWeight(weight);
}

void BlurFilterView::Output(){
	cv::imwrite(("blurred_" + filter->GetName()).c_str(), filter->GetResult());
}

