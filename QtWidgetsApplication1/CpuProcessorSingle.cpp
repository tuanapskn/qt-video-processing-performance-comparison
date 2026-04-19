#include "CpuProcessorSingle.h"

namespace MOOP {

    void CpuProcessorSingle::grayscale(const std::string& videoPath) {
        cv::VideoCapture cap(videoPath);
        if (!cap.isOpened()) return;
        cv::Mat frame, gray;
        while (cap.read(frame)) {
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            // Ýsterseniz sonucu kaydedebilir veya gösterebilirsiniz
        }
    }

    void CpuProcessorSingle::blending(const std::string& videoPath, const std::string& imagePath) {
        cv::VideoCapture cap(videoPath);
        if (!cap.isOpened()) return;
        cv::Mat img = cv::imread(imagePath);
        if (img.empty()) return;
        cv::Mat frame, imgResized, blended;

        double alpha = 0.0;
        double step = 0.01;
        bool increasing = true;

        while (cap.read(frame)) {
            if (frame.size() != img.size()) {
                cv::resize(img, imgResized, frame.size());
            }
            else {
                imgResized = img;
            }
            cv::addWeighted(frame, 1.0 - alpha, imgResized, alpha, 0.0, blended);

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
            // Ýsterseniz sonucu kaydedebilir veya gösterebilirsiniz
        }
    }

}
