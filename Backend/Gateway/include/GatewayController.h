#ifndef GATEWAYCONTROLLER_H
#define GATEWAYCONTROLLER_H

#include <crow.h>

#include "proxyclient.h"

class IEventBus;
class ICacheService;
class IThreadPool;
class IClient;

/// @brief Контролер API Gateway (маршрутизація запитів між сервісами)
class GatewayController {
public:
    GatewayController(IClient *client,
                      ICacheService *cache,
                      IThreadPool *pool,
                      IEventBus *queue);

    /// @brief Обробка проксі-запиту
    void handleProxyRequest(const crow::request &req,
                            crow::response &res,
                            const int port,
                            const std::string &path);

    /// @brief Обробка POST-запиту через gateway
    void handlePostRequest(const crow::request &req,
                           crow::response &res,
                           const int port,
                           const std::string &path);

    /// @brief Обробка маршрутизації task_id
    void handleRequestRoute(crow::response &res, std::string task_id);

    /// @brief Підписка на нові запити через чергу
    void subscribeOnNewRequest();

private:
    ProxyClient proxy_;          ///< HTTP proxy клієнт
    ICacheService *cache_;       ///< Кеш сервіс
    IThreadPool *pool_;         ///< Пул потоків
    IEventBus *queue_;          ///< Event bus / черга
};

#endif  // GATEWAYCONTROLLER_H
