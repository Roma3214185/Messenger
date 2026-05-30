#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <string>
#include <vector>

class INetworkFacade;
class IConfigProvider;
class IChatManager;
class User;
class Chat;
class RequestDTO;
struct ReactionInfo;
class IAuthoritizer;

using StatusCode = int;
using ResponceBody = std::string;
using Response = std::pair<StatusCode, ResponceBody>;

/// @brief Контролер для роботи з чатами
class ChatController {
public:
    ChatController(IChatManager *manager,
                   INetworkFacade *network_facade,
                   IAuthoritizer *authritizer);

    /// @brief Створення приватного чату
    Response createPrivateChat(const RequestDTO &req);

    /// @brief Отримання всіх чатів користувача
    Response getAllChats(const RequestDTO &req);

    /// @brief Отримання конкретного чату
    Response getChat(const RequestDTO &req, const std::string &chat_id_str);

    /// @brief Отримання учасників чату
    Response getAllChatMembers(const RequestDTO &req, const std::string &chat_id_str);

private:
    /// @brief Авторизація користувача з request
    std::optional<long long> authorizeUser(const RequestDTO &req);

    /// @brief Отримання користувача за ID
    virtual std::optional<User> getUserById(long long id);

    /// @brief Авторизація по токену
    std::optional<long long> autoritize(const std::string &token);

    /// @brief Отримання реакцій чату
    std::vector<ReactionInfo> getReactionOfChat(long long chat_id);

    IChatManager *manager_;
    INetworkFacade *network_facade_;
    IAuthoritizer *authoritizer_;
};

#endif  // CHATCONTROLLER_H
