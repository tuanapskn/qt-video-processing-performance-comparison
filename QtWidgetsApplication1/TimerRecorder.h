#pragma once
#include <chrono>

namespace MOOP {

    class TimerRecorder {
    public:
        TimerRecorder() = default;
        void start();
        double elapsed() const;
    private:
        std::chrono::high_resolution_clock::time_point startTime;
    };

} // namespace MOOP
