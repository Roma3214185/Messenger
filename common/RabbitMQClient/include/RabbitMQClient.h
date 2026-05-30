#ifndef RABBITMQCLIENT
#define RABBITMQCLIENT

#include <SimpleAmqpClient/SimpleAmqpClient.h>

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#include "Debug_profiling.h"
#include "interfaces/IRabitMQClient.h"
#include "threadpool.h"

/// @brief Конфігурація підключення до RabbitMQ
struct RabbitMQConfig {
    std::string host;
    int port;
    std::string user;
    std::string password;
};

struct IThreadPool;

/// @brief Клієнт RabbitMQ (Event Bus поверх AMQP)
class RabbitMQClient : public IEventBus, public IEventBusLifecycle {
public:
    RabbitMQClient(const RabbitMQConfig &rabbitmq_config, IThreadPool *thread_pool);
    ~RabbitMQClient();

    RabbitMQClient(const RabbitMQClient &) = delete;
    RabbitMQClient &operator=(const RabbitMQClient &) = delete;
    RabbitMQClient(RabbitMQClient &&) = delete;
    RabbitMQClient &operator=(RabbitMQClient &&) = delete;

    /// @brief Публікація повідомлення
    void publish(const PublishRequest &publish_request) override;

    /// @brief Підписка на події
    void subscribe(const SubscribeRequest &subscribe_request,
                   const EventCallback &callback) override;

    /// @brief Зупинка клієнта
    void stop() override;

private:
    /// @brief Оголошення exchange
    void declareExchange(const std::string &exchange,
                         const std::string &type,
                         bool durable);

    std::atomic<bool> running_{false};                ///< Стан роботи
    IThreadPool *pool_;                               ///< Thread pool
    std::vector<std::thread> consumer_threads_;      ///< Consumer threads
    std::mutex consumer_threads_mutex_;              ///< Mutex for consumers
    std::unordered_set<std::string> declared_exchanges_; ///< Cache exchanges
    const RabbitMQConfig &rabit_mq_config_;          ///< RabbitMQ config
};

#endif  // RABBITMQCLIENT
