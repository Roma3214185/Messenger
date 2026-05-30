#ifndef AUTH_SERVICE_SERVER_H
#define AUTH_SERVICE_SERVER_H

#include <crow.h>

class AuthController;

/// @brief HTTP сервер для Auth Service (Crow framework)
class Server {
public:
    /// @brief Створює сервер
    Server(crow::SimpleApp &app, int port, AuthController *controller);

    /// @brief Ініціалізація HTTP маршрутів
    void initRoutes();

    /// @brief Запуск сервера
    void run();

    /// @brief Генерація криптографічних ключів
    [[nodiscard]] bool generateKeys();

private:
    /// @brief Обробник GET /findById
    void handleFindById();

    /// @brief Обробник GET /findByTag
    void handleFindByTag();

    /// @brief Обробник POST /register
    void handleRegister();

    /// @brief Обробник GET /me
    void handleMe();

    /// @brief Обробник POST /login
    void handleLogin();

    crow::SimpleApp &app_;
    int port_;
    AuthController *controller_;
};

#endif  // AUTH_SERVICE_SERVER_H
