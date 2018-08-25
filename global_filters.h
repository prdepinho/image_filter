#pragma once

#include "filter.h"
#include "blur.h"
#include "blur_view.h"
#include "rgbsplit.h"
#include "greyscale.h"

namespace Global{

std::vector<Filter*> filters;
std::vector<FilterView*> views;

// add filters here

BlurFilter blur;
BlurFilterView blur_view(&blur);
RGBSplitFilter rgb;
GreyscaleFilter gray;

void SetFilters(){
	filters = {&blur, &rgb, &gray};
	views = {&blur_view, &rgb, &gray};
}

}
