#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include <QPixmap>

#include "dto/ChatBase.h"
#include "dto/Message.h"

using ChatPtr = std::shared_ptr<ChatBase>;
using ListOfChats = QList<ChatPtr>;
using ChatIndex = long long;
using OptionalChatIndex = std::optional<ChatIndex>;

/// @brief Модель списку чатів для Qt UI (MVC)
class ChatModel : public QAbstractListModel {
    Q_OBJECT

public:
    /// @brief Ролі даних для UI
    enum Roles : std::uint16_t {
        ChatIdRole = Qt::UserRole + 1,
        TitleRole,
        LastMessageRole,
        UnreadRole,
        AvatarRole
    };

    /// @brief Ініціалізація моделі чатів
    explicit ChatModel(QObject *parent = nullptr);

    /// @brief Кількість рядків у моделі
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// @brief Отримання даних за роллю
    QVariant data(const QModelIndex &index, int role) const override;

    /// @brief Імена ролей для QML/UI
    QHash<int, QByteArray> roleNames() const override;

    /// @brief Додавання чату
    void addChat(const ChatPtr &chat);

    /// @brief Оновлення інформації про чат
    void updateChatInfo(long long chat_id, const std::optional<Message> &last_message);

    /// @brief Очищення моделі
    void clear();

    /// @brief Сортування чатів
    void sortChats();

    /// @brief Пошук індексу чату за ID
    [[nodiscard]] OptionalChatIndex findIndexByChatId(long long chat_id) const;

Q_SIGNALS:
    /// @brief Сигнал оновлення чату
    void chatUpdated(const long long chat_id);

private:
    ListOfChats chats_;  ///< Список чатів
};

#endif  // CHATMODEL_H
