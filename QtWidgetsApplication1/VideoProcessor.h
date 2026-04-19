#pragma once
#include <QString>
#include <memory>

namespace MOOP {

    class IProcessor {
    public:
        virtual ~IProcessor() = default;
        virtual void grayscale(const std::string& videoPath) = 0;
        virtual void blending(const std::string& videoPath, const std::string& imagePath) = 0;
    };

    class VideoProcessor {
    public:
        void processGrayscale(const QString& videoPath, int method, double& elapsed);
        void processBlending(const QString& videoPath, const QString& imagePath, int method, double& elapsed);

    private:
        std::unique_ptr<IProcessor> createProcessor(int method);
    };

} // namespace MOOP
