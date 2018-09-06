
# How to use this program.


The following line applies the RGB Split (specified by the flag -rgb) filter on
the input file lena.png:

```
./main -rgb lena.png
```

If a filter requires flags, they should be put after the input filename, as the
follows:

```
./main -blur lena.png 5 1
```

These lines execute the program in non-interactive mode. If no flag is
specified, the program enters interactive mode, as the following:

```
./main lena.png
```

Then the program will show a list of available filters to choose from, and 
request the user to input any necessary parameters.



The current implemented filters are the following:

RGB Split: -rgb

- Splits the color channels of an 8 bit image and saves one image for
	each.

Blur: -blur radius weght

- Blurs an 8 bit image of any number of channls by setting each pixel as
	the weighted mean of all its neighbors in its radius.

  - radius: a positive integer

  - weight: a float greater than zero.

Greyscale: -grey

- Creates a single channel black and white version of an 8 bit color
	image.



# How to implement new filters.


Filter is the interface used by the program to interact with filters and to
deal with input and output of data to it. 

Once implemented an instance of the interface must be added to
global_filters.h, and a reference of the object should be put into the
vector set to FilterFramework in main.cpp.

Problems are treated by throwing exceptions, which the main program catches and
exits gracefully.

In order to know more about the interface and their functions, view the
documentation in filter.h.


## An example: A Greyscale filter. 

This filter should receive an 8 bit colored image and return a black and white
single channel image as output.

What follows is the header file greyscale.h:


```
#pragma once

#include "filter.h"
#include <opencv2/opencv.hpp>

class GreyscaleFilter : public Filter {
public:
	virtual bool IsApplicable() const override;
	virtual bool Apply() override;
	virtual void SetImage(cv::Mat image) override { this->image = image; }
	virtual void SetFileName(std::string name) override { this->name = name; }
	virtual std::string GetFlag() override { return "-grey"; }
	virtual std::string GetFilterName() const override { return "Greyscale"; }
	virtual std::vector<std::string> GetParameterNames() const { return {}; }
	virtual void SetParameters(std::vector<std::string> arguments) override {};
	virtual void Output() override;
private:
	std::string name;
	cv::Mat image;
	cv::Mat result;
};
```

Some of these functions are simple eneugh to be implemented in the header
itself. SetImage and SetFileName are called by the program to set the input file
and its filename for the filter.

Among GreyscaleFilter's member variables are the input image, which is set by
SetImage; name, which is set by SetFileName; and result, which is produced by
Apply.

The function IsApplicable should check whether the input file can be processed
by the filter or not. It should take into consideration its image type. As
illustrated below, GreyscaleFilter only accepts images of 3 or 4 channels of 8
bits. Only applicable filters are shown as options in interactive mode.

```
bool GreyscaleFilter::IsApplicable() const {
	switch(image.type()){
		case CV_8UC3: case CV_8UC4:
			return true;
	}
	return false;
}
```

GetFlag should return the flag used in non-interactive command line, while
GetFilterName is the name that appears in the filter list in interactive mode.

SetParameters is called in both modes and passes the filter arguments in
a vector. This method should check and store all necessary parameters.

The Apply method is the implementation of the filter itself. This method is
called after SetImage and SetParameters, so the input image and
the necessary parameters should be available now. The result of the processing
is stored in the result member variable.

The next code snippet shows how GreyscaleFilter creates a single channel 8 bit
image as output and copies to it the avarage values of each pixel from each
channel of the input image.


```
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
```

Finally, the last function to be called is Output, which can be used to save
the result image into a file, as is shown below.

```
void GreyscaleFilter::Output(){
	cv::imwrite(("grey_" + name).c_str(), result);
}
```


When the filter is ready, you must create a variable of GreyscaleFilter in
global_filters.h and add a reference to it to FilterFramework as so:


```
int main(int argc, char **argv){

	FilterFramework framework;

	BlurFilter blur;
	RGBSplitFilter rgb;
	GreyscaleFilter gray;

	framework.SetFilters({&blur, &rgb, &gray});

	return framework.Execute(argc, argv);
}
```

At last, do not forget to update the Makefile to include greyscale.o to the
OBJS macro:


```
OBJS=blur.o rgbsplit.o greyscale.o main.o
```

That should be every thing necessary to implement a new filter.

