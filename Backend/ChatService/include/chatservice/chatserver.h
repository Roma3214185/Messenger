#ifndef BACKEND_CHATSERVICE_SRC_SERVER_SERVER_H_
#define BACKEND_CHATSERVICE_SRC_SERVER_SERVER_H_

#include <crow.h>

#include <memory>

class ChatController;
class NetworkManager;

/// @brief HTTP сервер Chat Service (Crow framework)
class ChatServer {
public:
    ChatServer(crow::SimpleApp &app, int port, ChatController *controller);

    /// @brief Запуск сервера
    void run();

private:
    /// @brief Ініціалізація HTTP маршрутів
    void initRoutes();

    /// @brief Обробка створення приватного чату
    void handleCreatingPrivateChat();

    /// @brief Обробка отримання всіх чатів
    void handleGetAllChats();

    /// @brief Обробка отримання конкретного чату
    void handleGetChat();

    /// @brief Обробка отримання учасників чатів
    void handleGetAllChatsMembers();

    crow::SimpleApp &app_;
    int port_;
    ChatController *controller_;
};

#endif  // BACKEND_CHATSERVICE_SRC_SERVER_SERVER_H_
