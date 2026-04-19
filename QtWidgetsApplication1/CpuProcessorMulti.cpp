#include "CpuProcessorMulti.h"
#include <omp.h>

namespace MOOP {

    void CpuProcessorMulti::grayscale(const std::string& videoPath) {
        cv::VideoCapture cap(videoPath);
        if (!cap.isOpened()) return;
        std::vector<cv::Mat> frames;
        cv::Mat frame;
        while (cap.read(frame)) {
            frames.push_back(frame.clone());
        }
        std::vector<cv::Mat> grays(frames.size());

#pragma omp parallel for
        for (int i = 0; i < static_cast<int>(frames.size()); ++i) {
            cv::cvtColor(frames[i], grays[i], cv::COLOR_BGR2GRAY);
        }
      
    }

    void CpuProcessorMulti::blending(const std::string& videoPath, const std::string& imagePath) {
        cv::VideoCapture cap(videoPath);
        if (!cap.isOpened()) return;
        cv::Mat img = cv::imread(imagePath);
        if (img.empty()) return;
        std::vector<cv::Mat> frames;
        cv::Mat frame;
        while (cap.read(frame)) {
            frames.push_back(frame.clone());
        }
        std::vector<cv::Mat> blended(frames.size());

        double alpha = 0.0;
        double step = 0.01;
        bool increasing = true;
        std::vector<double> alphas(frames.size());

        for (size_t i = 0; i < frames.size(); ++i) {
            alphas[i] = alpha;
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

#pragma omp parallel for
        for (int i = 0; i < static_cast<int>(frames.size()); ++i) {
            cv::Mat imgResized;
            if (frames[i].size() != img.size()) {
                cv::resize(img, imgResized, frames[i].size());
            }
            else {
                imgResized = img;
            }
            cv::addWeighted(frames[i], 1.0 - alphas[i], imgResized, alphas[i], 0.0, blended[i]);
        }
     
    }

}
