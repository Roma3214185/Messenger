#ifndef DRAWDATA_H
#define DRAWDATA_H

#include <QDateTime>
#include <QRect>
#include <QString>

#include <dto/Message.h>

/// @brief UI-дані користувача для відображення
struct UserDrawData {
    QString name;     ///< Ім'я користувача
    QPixmap avatar;   ///< Аватар
    QString tag;      ///< Унікальний тег
};

/// @brief UI-дані чату для відображення
struct ChatDrawData {
    QString title;                 ///< Назва чату
    std::optional<Message> last_message; ///< Останнє повідомлення
    QString avatar_path;           ///< Шлях до аватара чату
    int unread;                    ///< Кількість непрочитаних
};

#endif  // DRAWDATA_H
