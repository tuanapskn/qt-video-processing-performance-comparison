// mycode.cu
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
#include <iostream>

int main() {
    cv::cuda::GpuMat gpuMat(100, 100, CV_8UC1);
    gpuMat.setTo(cv::Scalar(128));
    std::cout << "GPU mat created and initialized!" << std::endl;
    return 0;
}
