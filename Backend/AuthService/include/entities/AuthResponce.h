#ifndef BACKEND_AUTHSERVICE_SRC_HEADERS_AUTHRESPONCE_H_
#define BACKEND_AUTHSERVICE_SRC_HEADERS_AUTHRESPONCE_H_

#include <optional>
#include <string>

#include "entities/User.h"

/// @brief Результат авторизації користувача
struct AuthResponce {
    std::string token;          ///< JWT токен
    std::optional<User> user;   ///< Дані користувача (якщо доступні)
};

#endif  // BACKEND_AUTHSERVICE_SRC_HEADERS_AUTHRESPONCE_H_
