#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractItemModel>

#include "dto/Message.h"
#include "model.h"
#include "models/UserModel.h"

using ListOfMessages = QList<Message>;
using MessageId = long long;
using ChatId = long long;
using UsersByMessageId = std::unordered_map<MessageId, User>;
using MessagesByChatId = std::unordered_map<ChatId, ListOfMessages>;

/// @brief Qt модель списку повідомлень
class MessageModel : public QAbstractListModel {
    Q_OBJECT

public:
    /// @brief Ролі даних повідомлення для UI
    enum Roles : std::uint16_t {
        MessageIdRole = Qt::UserRole + 1,
        TextRole,
        TimestampRole,
        SenderIdRole,
        SendedStatusRole,
        ReadedStatusRole,
        FullMessage
    };

    /// @brief Ініціалізація моделі повідомлень
    explicit MessageModel(QObject *parent = nullptr);

    /// @brief Кількість повідомлень у моделі
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// @brief Отримання даних повідомлення за роллю
    QVariant data(const QModelIndex &index, int role) const override;

    /// @brief Отримання індексу повідомлення за ID
    QModelIndex indexFromId(MessageId) const;

    /// @brief Імена ролей для UI
    QHash<int, QByteArray> roleNames() const override;

    /// @brief Збереження повідомлення
    void saveMessage(const Message &msg);

    /// @brief Видалення повідомлення
    void deleteMessage(const Message &msg);

    /// @brief Очищення моделі
    void clear();

    /// @brief Отримання останнього повідомлення
    std::optional<Message> getLastMessage() const;

    /// @brief Отримання найстарішого повідомлення
    std::optional<Message> getOldestMessage() const;

    /// @brief Отримання всіх повідомлень
    [[nodiscard]] ListOfMessages messages() const noexcept;

private:
    /// @brief Сортування повідомлень за часом
    void sortMessagesByTimestamp();

    std::mutex messages_mutex_;  ///< Захист доступу до списку повідомлень
    ListOfMessages messages_;    ///< Список повідомлень
};

#endif  // MESSAGEMODEL_H
