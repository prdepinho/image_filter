
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

	CheckParameters(radius, weight);

	filter->SetRadius(radius);
	filter->SetWeight(weight);
}

int BlurFilterView::ProcessInput(){
	int radius = -1;
	float weight = -1;
	try{
		std::cout << "Radius: ";
		std::cin >> radius;
		std::cout << "Weight: ";
		std::cin >> weight;
	}catch(std::exception &e){
		throw std::invalid_argument("Expected an int and a float");
	}

	CheckParameters(radius, weight);

	filter->SetRadius(radius);
	filter->SetWeight(weight);
	return 0;
}

void BlurFilterView::Output(){
	cv::imwrite(("blurred_" + filter->GetName()).c_str(), filter->GetResult());
}

void BlurFilterView::CheckParameters(int radius, float weight){
	if(radius < 1){
		throw std::invalid_argument("Radius < 1");
	}
	if(weight <= 0.0f){
		throw std::invalid_argument("Weight <= 0");
	}
}
