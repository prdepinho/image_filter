
#include "blur.h"

// Works with any image.
bool BlurFilter::IsApplicable() const {
	return true;
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

