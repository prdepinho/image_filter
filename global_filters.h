#pragma once

#include "filter.h"
#include "filter_view.h"
#include "filter_exception.h"
#include "blur.h"
#include "blur_view.h"
#include "rgbsplit.h"
#include "rgbsplit_view.h"

namespace Global{

std::vector<Filter*> filters;
std::vector<FilterView*> views;

// add filters here

BlurFilter blur;
BlurFilterView blur_view(&blur);
RGBSplitFilter rgb;
RGBSplitFilterView rgb_view(&rgb);

void Set(){
	filters = {&blur, &rgb};
	views = {&blur_view, &rgb_view};
}

}
