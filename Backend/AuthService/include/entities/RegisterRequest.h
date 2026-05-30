#ifndef BACKEND_AUTHSERVICE_SRC_HEADERS_REGISTERREQUEST_H_
#define BACKEND_AUTHSERVICE_SRC_HEADERS_REGISTERREQUEST_H_

#include <string>

/// @brief Запит на реєстрацію користувача
struct RegisterRequest {
    std::string email;     ///< Email користувача
    std::string password;  ///< Пароль
    std::string name;      ///< Ім'я користувача
    std::string tag;       ///< Унікальний тег (username)
};

/// @brief Запит на логін користувача
struct LoginRequest {
    std::string email;     ///< Email користувача
    std::string password;  ///< Пароль
};

#endif  // BACKEND_AUTHSERVICE_SRC_HEADERS_REGISTERREQUEST_H_
