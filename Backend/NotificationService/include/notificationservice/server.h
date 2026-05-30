#ifndef BACKEND_NOTIFICATIONSERVICE_SERVER_SERVER_H_
#define BACKEND_NOTIFICATIONSERVICE_SERVER_SERVER_H_

#include <crow.h>

class ISocket;
class SocketHandlersRepository;
class IActiveSocketRepository;
class ISubscriber;

using SocketPtr = std::shared_ptr<ISocket>;

/// @brief HTTP/WebSocket сервер Notification Service
class Server {
public:
    Server(int port,
           IActiveSocketRepository* active_socket_repository,
           SocketHandlersRepository* socket_handlers_repository,
           ISubscriber* subscriber);

    /// @brief Запуск сервера
    void run();

protected:
    /// @brief Обробка повідомлення від WebSocket
    void handleSocketOnMessage(const SocketPtr& socket, const std::string& data);

private:
    /// @brief Ініціалізація HTTP маршрутів
    void initRoutes();

    /// @brief Реєстрація WebSocket маршрутів
    void handleSocketRoutes();

    crow::SimpleApp app_;
    ISubscriber* subscriber_;
    IActiveSocketRepository* active_sockets_;
    SocketHandlersRepository* socket_handlers_repository_;
    const int notification_port_;
};

#endif  // BACKEND_NOTIFICATIONSERVICE_SERVER_SERVER_H_
