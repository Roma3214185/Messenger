#ifndef SIGNUPREQUEST_H
#define SIGNUPREQUEST_H

#include <QString>

/// @brief Запит на реєстрацію користувача
struct SignUpRequest {
    QString email;     ///< Email користувача
    QString password;  ///< Пароль
    QString tag;      ///< Унікальний тег
    QString name;     ///< Ім'я
};

/// @brief Запит на авторизацію користувача
struct LogInRequest {  // todo: make immutable
    QString email;     ///< Email користувача
    QString password;  ///< Пароль
};

#endif  // SIGNUPREQUEST_H
