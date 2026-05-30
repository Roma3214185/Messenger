#ifndef CROWSOCKET_H
#define CROWSOCKET_H

#include <crow.h>

#include "interfaces/ISocket.h"

/// @brief WebSocket обгортка над Crow connection
class CrowSocket final : public ISocket {
public:
    /// @brief Створює сокет-обгортку
    explicit CrowSocket(crow::websocket::connection *conn);

    /// @brief Перевірка відповідності WebSocket з’єднання
    bool isSameAs(crow::websocket::connection *other);

    /// @brief Надсилання текстового повідомлення
    void send_text(const std::string &text) override;

private:
    crow::websocket::connection *conn_; ///< WebSocket з’єднання
    std::mutex conn_mutex_;             ///< Захист доступу до send
};

#endif  // CROWSOCKET_H
