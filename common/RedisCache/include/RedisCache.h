#ifndef BACKEND_REDISCACHE_REDISCACHE_H_
#define BACKEND_REDISCACHE_REDISCACHE_H_

#include <sw/redis++/redis.h>

#include <chrono>
#include <memory>
#include <mutex>
#include <string>

#include "interfaces/ICacheService.h"

/// @brief Redis-based реалізація кешу (singleton)
class RedisCache : public ICacheService {
public:
    /// @brief Отримання singleton-інстансу кешу
    static RedisCache &instance();

    RedisCache(const RedisCache &) = delete;
    RedisCache &operator=(const RedisCache &) = delete;
    RedisCache(RedisCache &&) = delete;
    RedisCache &operator=(RedisCache &&) = delete;

    /// @brief Інкремент значення ключа
    void incr(const std::string &key) override;

    /// @brief Видалення ключа
    void remove(const std::string &key) override;

    /// @brief Очищення всього кешу
    void clearCache() override;

    /// @brief Масове встановлення значень з TTL
    void setPipelines(const std::vector<std::string> &keys,
                      const std::vector<std::string> &results,
                      std::chrono::seconds ttl = std::chrono::seconds{5}) override;

    /// @brief Встановлення значення з TTL
    void set(const std::string &key,
             const std::string &value,
             std::chrono::seconds ttl = std::chrono::seconds{5}) override;

    /// @brief Отримання значення за ключем
    std::optional<std::string> get(const std::string &key) override;

private:
    std::unique_ptr<sw::redis::Redis> redis_;  ///< Redis клієнт
    std::mutex init_mutex_;                    ///< Захист ініціалізації

    /// @brief Отримання Redis-інстансу
    sw::redis::Redis &getRedis();

    /// @brief TTL з випадковим jitter для уникнення cache stampede
    int getTtlWithJitter(std::chrono::seconds ttl);

    RedisCache() = default;
};

#endif  // BACKEND_REDISCACHE_REDISCACHE_H_
