
#include "greyscale.h"


// The image has to have at least three channels.
bool GreyscaleFilter::IsApplicable() const {
	switch(image.type()){
		case CV_8UC3: case CV_8UC4:
			return true;
	}
	return false;
}

bool GreyscaleFilter::Apply() {
	cv::Mat channels[3];
	result.create(image.rows, image.cols, CV_8UC1);
	cv::split(image, channels);

	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){
			int pix = 0;
			for(int c = 0; c < 3; c++){
				pix += channels[c].at<uchar>(i, j);
			}
			pix /= 3;
			result.at<uchar>(i, j) = pix;
		}
	}
}

void GreyscaleFilter::Output(){
	cv::imwrite(("grey_" + name).c_str(), result);
	std::cout << "output type: " << result.type() << std::endl;
}
