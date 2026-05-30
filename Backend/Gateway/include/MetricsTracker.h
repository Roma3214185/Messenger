#ifndef METRICSTRACKER_H
#define METRICSTRACKER_H

#include <chrono>

#include "interfaces/IMetrics.h"

/// @brief RAII трекер метрик часу виконання
struct MetricsTracker {
    IMetrics* metrics_ = nullptr;  ///< Інтерфейс метрик
    std::chrono::steady_clock::time_point start; ///< Час старту

    MetricsTracker() = default;

    /// @brief Запуск таймера та прив’язка метрик
    void startTimer(IMetrics* metrics);

    MetricsTracker(const MetricsTracker&) = delete;
    MetricsTracker& operator=(const MetricsTracker&) = delete;

    MetricsTracker(MetricsTracker&& other) noexcept;
    MetricsTracker& operator=(MetricsTracker&& other) noexcept;

    /// @brief Фіксація часу та відправка метрики
    ~MetricsTracker();
};

#endif  // METRICSTRACKER_H
