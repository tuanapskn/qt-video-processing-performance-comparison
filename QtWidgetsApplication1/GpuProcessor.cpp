#include "GpuProcessor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <cmath> 

namespace MOOP {

    void GpuProcessor::grayscale(const std::string& videoPath) {
        cv::Ptr<cv::cudacodec::VideoReader> reader = cv::cudacodec::createVideoReader(videoPath);
        cv::cuda::GpuMat gpuFrame, gpuGray;
        while (reader->nextFrame(gpuFrame)) {
            cv::cuda::cvtColor(gpuFrame, gpuGray, cv::COLOR_BGR2GRAY);
        }
    }

    void GpuProcessor::blending(const std::string& videoPath, const std::string& imagePath) {
        cv::Ptr<cv::cudacodec::VideoReader> reader = cv::cudacodec::createVideoReader(videoPath);
        cv::Mat img = cv::imread(imagePath);
        if (img.empty()) return;
        cv::cuda::GpuMat gpuImg, gpuFrame, gpuBlended;
        gpuImg.upload(img);

        double alpha = 0.0;
        double step = 0.01;
        bool increasing = true;

        while (reader->nextFrame(gpuFrame)) {
            if (gpuFrame.size() != gpuImg.size()) {
                cv::cuda::resize(gpuImg, gpuImg, gpuFrame.size());
            }
            cv::cuda::addWeighted(gpuFrame, 1.0 - alpha, gpuImg, alpha, 0.0, gpuBlended);

            // Alpha güncelle
            if (increasing) {
                alpha += step;
                if (alpha >= 1.0) {
                    alpha = 1.0;
                    increasing = false;
                }
            }
            else {
                alpha -= step;
                if (alpha <= 0.0) {
                    alpha = 0.0;
                    increasing = true;
                }
            }
        }
    }

    }

} // namespace MOOP
