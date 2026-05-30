#ifndef BACKEND_APIGATEWAY_SRC_GATEWAYSERVER_GATEWAYSERVER_H_
#define BACKEND_APIGATEWAY_SRC_GATEWAYSERVER_GATEWAYSERVER_H_

#include <crow.h>
#include <string>

#include "middlewares/Middlewares.h"

class GatewayController;

/// @brief Типізований Crow застосунок з middleware стеком
using GatewayApp =
    crow::App<LoggingMiddleware, RateLimitMiddleware, MetricsMiddleware, AuthMiddleware, CacheMiddleware>;

/// @brief HTTP сервер API Gateway
class GatewayServer {
public:
    GatewayServer(GatewayApp &app, GatewayController *controller);

    /// @brief Запуск сервера
    void run();

    /// @brief Реєстрація всіх маршрутів
    void registerRoutes();

private:
    GatewayApp &app_;
    GatewayController *controller_;

    /// @brief Реєстрація маршруту обробки запитів
    void registerRequestRoute();

    /// @brief Реєстрація проксі-маршруту
    void registerRoute(const std::string &basePath, int proxy);

    /// @brief Реєстрація health-check endpoint
    void registerHealthCheck();

    /// @brief Реєстрація WebSocket маршрутів
    void registerWebSocketRoutes();
};

#endif  // BACKEND_APIGATEWAY_SRC_GATEWAYSERVER_GATEWAYSERVER_H_
