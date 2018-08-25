#pragma once

#include "blur.h"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class BlurFilterView : public FilterView{
public:
	BlurFilterView(BlurFilter *filter = nullptr) : filter(filter) {}
	virtual std::string GetFlag() override { return "-blur"; }
	virtual std::string GetFilterName() const override { return "Blur"; }
	virtual void ProcessArgs(std::vector<std::string> arguments) override;
	virtual int ProcessInput() override;
	virtual void Output() override;
private:
	void CheckParameters(int radius, float weight);
	BlurFilter *filter;
};
