#ifndef NETWORKFACADE_H
#define NETWORKFACADE_H

#include "interfaces/IChatNetworkManager.h"
#include "interfaces/IMessageNetworkManager.h"
#include "interfaces/IUserNetworkManager.h"

/// @brief Фасад для доступу до мережевих менеджерів сервісів
class INetworkFacade {
public:
    /// @brief Доступ до користувацького API
    virtual IUserNetworkManager& users() = 0;

    /// @brief Доступ до API повідомлень
    virtual IMessageNetworkManager& messages() = 0;

    /// @brief Доступ до API чатів
    virtual IChatNetworkManager& chats() = 0;

    virtual ~INetworkFacade() = default;
};

/// @brief Реалізація фасаду мережевих сервісів
class NetworkFacade : public INetworkFacade {
public:
    explicit NetworkFacade(ProxyClient* proxy)
        : users_(proxy),
        messages_(proxy),
        chats_(proxy) {}

    IUserNetworkManager& users() override { return users_; }
    IMessageNetworkManager& messages() override { return messages_; }
    IChatNetworkManager& chats() override { return chats_; }

private:
    UserNetworkManager users_;        ///< Мережевий менеджер користувачів
    MessageNetworkManager messages_;  ///< Мережевий менеджер повідомлень
    ChatNetworkManager chats_;        ///< Мережевий менеджер чатів
};

#endif  // NETWORKFACADE_H
