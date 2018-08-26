#pragma once

#include "filter.h"
#include "blur.h"
#include "rgbsplit.h"
#include "greyscale.h"

namespace Global{

std::vector<Filter*> filters;

// add filters here

BlurFilter blur;
RGBSplitFilter rgb;
GreyscaleFilter gray;

void SetFilters(){
	filters = {&blur, &rgb, &gray};
}

}
