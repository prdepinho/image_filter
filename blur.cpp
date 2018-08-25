
#include "blur.h"

// The image has to have at least three channels.
bool BlurFilter::IsApplicable() const {
	switch(image.type()){
		case CV_16SC3: case CV_16SC4:
		case CV_16UC3: case CV_16UC4:
		case CV_32FC3: case CV_32FC4:
		case CV_32SC3: case CV_32SC4:
		case CV_64FC3: case CV_64FC4:
		case CV_8SC3: case CV_8SC4:
		case CV_8UC3: case CV_8UC4:
			return true;
	}
	return false;
}

bool BlurFilter::Apply() {
	result = image.clone();

	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){
			std::vector<cv::Vec3b> neighbors = GetNeighbors(i, j);

			cv::Vec3b blurredPixel = result.at<cv::Vec3b>(i, j);
			float b = blurredPixel[0] * weight;
			float g = blurredPixel[1] * weight;
			float r = blurredPixel[2] * weight;
			for(cv::Vec3b neighbor : neighbors){
				b += neighbor[0];
				g += neighbor[1];
				r += neighbor[2];
			}
			blurredPixel[0] = b / (neighbors.size() + weight);
			blurredPixel[1] = g / (neighbors.size() + weight);
			blurredPixel[2] = r / (neighbors.size() + weight);
			result.at<cv::Vec3b>(i, j) = blurredPixel;
		}
	}

	return true;
}

std::vector<cv::Vec3b> BlurFilter::GetNeighbors(int y, int x) const{
	std::vector<cv::Vec3b> neighbors;
	for(int i = y - radius; i <= y + radius; i++){
		for(int j = x - radius; j <= x + radius; j++){
			if(!(i < 0 || i >= image.rows || j < 0 || j >= image.cols || (i == x && j == y))){
				neighbors.push_back(image.at<cv::Vec3b>(i, j));
			}
		}
	}
	return neighbors;
}

