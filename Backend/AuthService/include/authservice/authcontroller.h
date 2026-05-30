#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <string>

class IAuthManager;
class AuthResponce;
class IAuthoritizer;
class IGenerator;
class RequestDTO;

using StatusCode = int;
using ResponseBody = std::string;
using Response = std::pair<StatusCode, ResponseBody>;

/// @brief Контролер автентифікації користувачів
class AuthController {
public:
    using OptionalId = std::optional<long long>;
    using Token = std::string;

    /// @brief Створює AuthController
    AuthController(IAuthManager *manager,
                   IAuthoritizer *authoritizer,
                   IGenerator *generator);

    /// @brief Пошук користувача за ID
    Response findById(const RequestDTO &req, const std::string &user_id_str);

    /// @brief Пошук користувача за тегом
    Response findByTag(const RequestDTO &req);

    /// @brief Реєстрація нового користувача
    Response registerUser(const RequestDTO &req);

    /// @brief Отримання даних поточного користувача
    Response handleMe(const RequestDTO &req);

    /// @brief Логін користувача
    Response loginUser(const RequestDTO &req);

    /// @brief Генерація ключів (JWT/crypto)
    bool generateKeys();

private:
    /// @brief Перевірка токена та отримання user id
    OptionalId verifyToken(const std::string &token);

    IAuthManager *manager_;
    IAuthoritizer *authoritizer_;
    IGenerator *generator_;
};

#endif  // AUTHCONTROLLER_H
