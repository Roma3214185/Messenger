#ifndef SOCKETREPOSITORY_H
#define SOCKETREPOSITORY_H

#include <crow.h>
#include <unordered_set>

#include "interfaces/ISocket.h"

using SocketPtr = std::shared_ptr<ISocket>;
using UserId = long long;
using UserSocketsMap = std::unordered_map<UserId, SocketPtr>;
using AvtiveSockets = std::unordered_set<SocketPtr>;

/// @brief Репозиторій активних WebSocket-з’єднань
class IActiveSocketRepository {
public:
    virtual ~IActiveSocketRepository() = default;

    /// @brief Пошук сокета за Crow connection
    virtual SocketPtr findSocket(crow::websocket::connection *conn) = 0;

    /// @brief Додавання нового з’єднання
    virtual void addConnection(const SocketPtr &socket) = 0;

    /// @brief Видалення з’єднання
    virtual void deleteConnection(const SocketPtr &socket) = 0;
};

/// @brief Репозиторій сокетів користувачів
class IUserSocketRepository {
public:
    virtual ~IUserSocketRepository() = default;

    /// @brief Збереження сокета для користувача
    virtual void saveConnections(UserId, SocketPtr socket) = 0;

    /// @brief Отримання сокета користувача
    virtual SocketPtr getUserSocket(UserId) = 0;

    /// @brief Перевірка чи користувач онлайн
    virtual bool userOnline(UserId) = 0;
};

/// @brief Реалізація зберігання WebSocket-з’єднань
class SocketRepository : public IActiveSocketRepository,
                         public IUserSocketRepository {
public:
    SocketPtr findSocket(crow::websocket::connection *conn) override;
    void addConnection(const SocketPtr &socket) override;
    void deleteConnection(const SocketPtr &socket) override;

    /// @brief Потокобезпечне видалення з’єднання
    void deleteConnectionSync(const SocketPtr &conn_to_delete);

    void saveConnections(UserId, SocketPtr socket) override;
    SocketPtr getUserSocket(UserId) override;
    bool userOnline(UserId) override;

private:
    /// @brief Видалення з активних з’єднань
    void deleteFromActiveConnections(const SocketPtr &conn_to_delete);

    /// @brief Видалення з мапи користувачів
    void deleteFromUserSocketsMap(const SocketPtr &conn_to_delete);

private:
    AvtiveSockets active_sockets_;        ///< Активні з’єднання
    UserSocketsMap user_sockets_;         ///< Сокети користувачів
    std::mutex ws_active_mutex_;          ///< Mutex для active_sockets_
    std::mutex ws_user_mutex_;            ///< Mutex для user_sockets_
};

#endif  // SOCKETREPOSITORY_H
