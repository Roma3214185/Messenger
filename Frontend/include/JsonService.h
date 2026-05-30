#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "dto/ChatBase.h"

class MessageStatus;
class TokenManager;
class User;
class ReactionInfo;
class Reaction;
class Message;
class ChatBase;

/// @brief JSON-сервіс користувача
class IUserJsonService {
public:
    /// @brief Десеріалізація User з JSON відповіді
    virtual User getUserFromResponse(const QJsonObject &res) = 0;

    virtual ~IUserJsonService() = default;
};

/// @brief JSON-сервіс статусу повідомлення
class IMessageStatusJsonService {
public:
    /// @brief Отримання MessageStatus з JSON
    virtual std::optional<MessageStatus> getMessageStatus(const QJsonObject &res) = 0;

    virtual ~IMessageStatusJsonService() = default;
};

/// @brief JSON-сервіс повідомлень
class IMessageJsonService {
public:
    using MessageServerJsonAnswer = std::pair<Message, std::vector<ReactionInfo>>;

    /// @brief Парсинг повідомлення та реакцій з JSON
    virtual MessageServerJsonAnswer getMessageFromJson(const QJsonObject &obj) = 0;

    /// @brief Серіалізація Message у JSON
    virtual QJsonObject toJson(const Message &msg) = 0;

    virtual ~IMessageJsonService() = default;
};

/// @brief JSON-сервіс реакцій
class IReactionJsonService {
public:
    /// @brief Парсинг Reaction з JSON
    virtual Reaction getReaction(const QJsonObject &obj) = 0;

    virtual ~IReactionJsonService() = default;
};

/// @brief JSON-сервіс інформації про реакції
class IReactionInfoJsonService {
public:
    /// @brief Парсинг ReactionInfo з JSON значення
    virtual std::optional<ReactionInfo> getReactionInfo(const QJsonValue &value) = 0;

    virtual ~IReactionInfoJsonService() = default;
};

/// @brief JSON-сервіс чатів
class IChatJsonService {
public:
    /// @brief Парсинг Chat з JSON
    virtual ChatPtr getChatFromJson(const QJsonObject &obj) = 0;

    virtual ~IChatJsonService() = default;
};

/// @brief Фабрика створення Message
class MessageFactory {
public:
    /// @brief Створення Message з токенів та метаданих
    static Message createMessage(long long current_user_id,
                                 long long chat_id,
                                 long long sender_id,
                                 std::vector<MessageToken> tokens,
                                 const QString &local_id,
                                 std::optional<long long> answer_on = std::nullopt,
                                 QDateTime timestamp = QDateTime::currentDateTime());
};

/// @brief Реалізація JSON-сервісів (уніфікований парсер/серіалізатор)
class JsonService : public IUserJsonService,
                    public IMessageJsonService,
                    public IReactionJsonService,
                    public IReactionInfoJsonService,
                    public IChatJsonService,
                    public IMessageStatusJsonService {
    TokenManager *token_manager_;

public:
    explicit JsonService(TokenManager *token_manager);

    User getUserFromResponse(const QJsonObject &res) override;
    MessageServerJsonAnswer getMessageFromJson(const QJsonObject &obj) override;
    QJsonObject toJson(const Message &msg) override;
    ChatPtr getChatFromJson(const QJsonObject &obj) override;
    Reaction getReaction(const QJsonObject &obj) override;
    std::optional<ReactionInfo> getReactionInfo(const QJsonValue &value) override;
    std::optional<MessageStatus> getMessageStatus(const QJsonObject &res) override;
};

#endif  // ENTITY_FACTORY_H
