#include "VideoProcessor.h"
#include "CpuProcessorSingle.h"
#include "CpuProcessorMulti.h"
#include "GpuProcessor.h"
#include "TimerRecorder.h"
#include <memory>

namespace MOOP {

    class CpuSingleAdapter : public IProcessor {
    public:
        void grayscale(const std::string& videoPath) override {
            CpuProcessorSingle().grayscale(videoPath);
        }
        void blending(const std::string& videoPath, const std::string& imagePath) override {
            CpuProcessorSingle().blending(videoPath, imagePath);
        }
    };

    class CpuMultiAdapter : public IProcessor {
    public:
        void grayscale(const std::string& videoPath) override {
            CpuProcessorMulti().grayscale(videoPath);
        }
        void blending(const std::string& videoPath, const std::string& imagePath) override {
            CpuProcessorMulti().blending(videoPath, imagePath);
        }
    };

    class GpuAdapter : public IProcessor {
    public:
        void grayscale(const std::string& videoPath) override {
            GpuProcessor().grayscale(videoPath);
        }
        void blending(const std::string& videoPath, const std::string& imagePath) override {
            GpuProcessor().blending(videoPath, imagePath);
        }
    };

    std::unique_ptr<IProcessor> VideoProcessor::createProcessor(int method) {
        if (method == 0)
            return std::make_unique<CpuSingleAdapter>();
        else if (method == 1)
            return std::make_unique<CpuMultiAdapter>();
        else
            return std::make_unique<GpuAdapter>();
    }

    void VideoProcessor::processGrayscale(const QString& videoPath, int method, double& elapsed) {
        TimerRecorder timer;
        timer.start();

        auto processor = createProcessor(method);
        processor->grayscale(videoPath.toStdString());

        elapsed = timer.elapsed();
    }

    void VideoProcessor::processBlending(const QString& videoPath, const QString& imagePath, int method, double& elapsed) {
        TimerRecorder timer;
        timer.start();

        auto processor = createProcessor(method);
        processor->blending(videoPath.toStdString(), imagePath.toStdString());

        elapsed = timer.elapsed();
    }

} // namespace MOOP
