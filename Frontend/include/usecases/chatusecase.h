#ifndef CHATUSECASE_H
#define CHATUSECASE_H

#include <QObject>

#include "dto/ChatBase.h"
#include "managers/chatmanager.h"

class ChatModel;
class TokenManager;
class IChatDataManager;

using Token = QString;
using ChatId = long long;
using UserId = long long;
using ChatPtr = std::shared_ptr<ChatBase>;

/// @brief Use case шар для роботи з чатами (логіка рівня застосунку)
class ChatUseCase : public QObject {
    Q_OBJECT
public:
    using Token = QString;
    using ChatId = long long;
    using UserId = long long;
    using ChatPtr = std::shared_ptr<ChatBase>;

    /// @brief Ініціалізація ChatUseCase
    ChatUseCase(std::unique_ptr<ChatManager>, IChatDataManager *, TokenManager *);

    /// @brief Завантаження одного чату
    [[nodiscard]] ChatPtr loadChat(ChatId);

    /// @brief Завантаження всіх чатів
    QList<ChatPtr> loadChats();

    /// @brief Асинхронне завантаження чатів
    void loadChatsAsync();

    /// @brief Створення приватного чату з користувачем
    ChatPtr createPrivateChat(UserId);

    /// @brief Отримання приватного чату з користувачем
    ChatPtr getPrivateChatWithUser(UserId);

    /// @brief Створення нового чату
    void createChat(ChatId);

    /// @brief Кількість існуючих чатів
    int getNumberOfExistingChats() const;

    /// @brief Отримання чату за ID
    [[nodiscard]] ChatPtr getChat(ChatId);

    /// @brief Очищення всіх чатів
    void clearAllChats();

    /// @brief Logout користувача
    void logout();

private:
    std::unique_ptr<ChatManager> chat_manager_;
    IChatDataManager *data_manager_;
    TokenManager *token_manager_;
};

#endif  // CHATUSECASE_H
