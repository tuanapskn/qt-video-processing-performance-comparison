#pragma once
#include <string>
#include <opencv2/opencv.hpp>

namespace MOOP {

    class CpuProcessorMulti {
    public:
        void grayscale(const std::string& videoPath);
        void blending(const std::string& videoPath, const std::string& imagePath);
    };

}
