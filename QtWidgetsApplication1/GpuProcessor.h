// GpuProcessor.h
#pragma once
#include <string>
namespace MOOP {
    class GpuProcessor {
    public:
        void grayscale(const std::string& videoPath);
        void blending(const std::string& videoPath, const std::string& imagePath);
    };
}
