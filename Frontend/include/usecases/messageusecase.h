#ifndef MESSAGEUSECASE_H
#define MESSAGEUSECASE_H

#include <QObject>

#include "managers/messagemanager.h"

class MessageModel;
class IMessageDataManager;
class TokenManager;
struct Message;
struct User;
struct ReactionInfo;

using MessageModelPtr = std::shared_ptr<MessageModel>;
using Token = QString;

/// @brief Use case для роботи з повідомленнями (логіка рівня застосунку)
class MessageUseCase : public QObject {
    Q_OBJECT
public:
    using MessageModelPtr = std::shared_ptr<MessageModel>;
    using Token = QString;

    /// @brief Ініціалізація MessageUseCase
    MessageUseCase(IMessageDataManager *message_data_manager,
                   std::unique_ptr<MessageManager> message_manager,
                   TokenManager *token_manager);

    /// @brief Отримання моделі повідомлень для чату
    [[nodiscard]] MessageModel *getMessageModel(long long chat_id);

    /// @brief Синхронне отримання повідомлень чату
    [[nodiscard]] QList<Message> getChatMessages(long long chat_id, int limit = 20);

    /// @brief Асинхронне отримання повідомлень чату
    void getChatMessagesAsync(long long chat_id);

    /// @brief Видалення повідомлення
    void deleteMessage(const Message &msg);

Q_SIGNALS:
    /// @brief Сигнал додавання нового повідомлення
    void messageAdded(const Message &);

private:
    IMessageDataManager *data_manager_;
    std::unique_ptr<MessageManager> message_manager_;
    TokenManager *token_manager_;
};

#endif  // MESSAGEUSECASE_H
