

#include "filter.h"
#include "filter_framework.h"
#include "blur.h"
#include "rgbsplit.h"
#include "greyscale.h"

int main(int argc, char **argv){

	FilterFramework framework;

	BlurFilter blur;
	RGBSplitFilter rgb;
	GreyscaleFilter gray;

	framework.SetFilters({&blur, &rgb, &gray});

	return framework.Execute(argc, argv);
}

