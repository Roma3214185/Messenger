#ifndef PROXYCLIENT_H_
#define PROXYCLIENT_H_

#include <string>

class ForwardRequestDTO;
class RequestDTO;
class IClient;

/// @brief Результат мережевого запиту (HTTP status + body)
using NetworkResponse = std::pair<int, std::string>;

/// @brief Проксі-клієнт для маршрутизації запитів між сервісами
class ProxyClient {
    IClient *client_;

public:
    /// @brief Створення проксі над HTTP клієнтом
    explicit ProxyClient(IClient *client) : client_(client) {}

    /// @brief Пересилання запиту на інший сервіс (port-based routing)
    NetworkResponse forward(const RequestDTO &, const int port);

private:
    /// @brief Внутрішнє виконання HTTP-запиту
    NetworkResponse makeRequest(const ForwardRequestDTO &,
                                const std::string &method);
};

#endif  // ROXYCLIENT_H_
