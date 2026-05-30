#ifndef USERMODEL_H
#define USERMODEL_H

#include <QAbstractListModel>

#include "dto/User.h"

/// @brief Qt модель списку користувачів
class UserModel : public QAbstractListModel {
    Q_OBJECT
public:
    using ListOfUsers = QVector<User>;

    /// @brief Ролі даних користувача для UI
    enum Roles : std::uint16_t {
        UserIdRole = Qt::UserRole + 1,
        NameRole,
        TagRole,
        EmailRole,
        AvatarRole
    };

    /// @brief Ініціалізація моделі користувачів
    explicit UserModel(QObject *parent = nullptr);

    /// @brief Кількість користувачів
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// @brief Отримання даних користувача за роллю
    QVariant data(const QModelIndex &index, int role) const override;

    /// @brief Імена ролей для UI
    QHash<int, QByteArray> roleNames() const override;

    /// @brief Додавання користувача
    void addUser(const User &user);

    /// @brief Очищення моделі
    void clear();

private:
    ListOfUsers users_;  ///< Список користувачів
};

#endif  // USERMODEL_H
