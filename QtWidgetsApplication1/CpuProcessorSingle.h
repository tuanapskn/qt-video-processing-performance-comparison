#pragma once
#include <string>
#include <opencv2/opencv.hpp>

namespace MOOP {

    class CpuProcessorSingle {
    public:
        void grayscale(const std::string& videoPath);
        void blending(const std::string& videoPath, const std::string& imagePath);
    };

}
