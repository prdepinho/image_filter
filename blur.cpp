
#include "blur.h"

// The image may have any number of channels.
bool BlurFilter::IsApplicable() const {
	switch(image.type()){
		case CV_8UC1: case CV_8UC2:
		case CV_8UC3: case CV_8UC4:
			return true;
	}
	return false;
}

bool BlurFilter::Apply(){
	result = image.clone();

	const int no_channels = image.channels();
	float pix[no_channels];
	cv::Mat channels[no_channels];
	cv::split(image, channels);

	std::vector<cv::Mat> result_channels(no_channels);
	for(int c = 0; c < no_channels; c++){
		result_channels[c] = channels[c].clone();
	}

	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){
			for(int c = 0; c < no_channels; c++){
				std::vector<uchar> neighbors = GetNeighbors(channels[c], i, j);
				uchar blurredPixel = channels[c].at<uchar>(i, j);
				pix[c] = blurredPixel * weight;
				for(uchar neighbor : neighbors){
					pix[c] += neighbor;
				}
				blurredPixel = pix[c] / (neighbors.size() + weight);
				result_channels[c].at<uchar>(i, j) = blurredPixel;
			}
		}
	}
	cv::merge(result_channels, result);

	return true;
}

std::vector<uchar> BlurFilter::GetNeighbors(cv::Mat &channel, int y, int x) const{
	std::vector<uchar> neighbors;
	for(int i = y - radius; i <= y + radius; i++){
		for(int j = x - radius; j <= x + radius; j++){
			if(!(i < 0 || i >= channel.rows || j < 0 || j >= channel.cols || (i == x && j == y))){
				neighbors.push_back(channel.at<uchar>(i, j));
			}
		}
	}
	return neighbors;
}

