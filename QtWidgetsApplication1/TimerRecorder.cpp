#include "TimerRecorder.h"

namespace MOOP {

    void TimerRecorder::start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    double TimerRecorder::elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - startTime).count();
    }

} // namespace MOOP
