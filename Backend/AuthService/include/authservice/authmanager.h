#ifndef BACKEND_AUTHSERVICE_SRC_AUTHMANAGER_AUTHMANAGER_H_
#define BACKEND_AUTHSERVICE_SRC_AUTHMANAGER_AUTHMANAGER_H_

#include <optional>
#include <string>

#include "GenericRepository.h"
#include "authservice/interfaces/IAuthManager.h"
#include "entities/AuthResponce.h"

struct RegisterRequest;
struct LoginRequest;
struct AuthResponce;
struct UserCredentials;
class IIdGenerator;

using OptionalUser = std::optional<User>;

/// @brief Реалізація логіки автентифікації та керування користувачами
class AuthManager : public IAuthManager {
public:
    /// @brief Створює менеджер автентифікації
    AuthManager(GenericRepository &repository, IIdGenerator *generator);

    /// @brief Отримання користувача за ID
    OptionalUser getUser(long long user_id) override;

    /// @brief Логін користувача
    OptionalUser loginUser(const LoginRequest &login_request) override;

    /// @brief Реєстрація користувача
    OptionalUser registerUser(const RegisterRequest &req) override;

    /// @brief Пошук користувачів за тегом
    std::vector<User> findUsersByTag(const std::string &tag) override;

protected:
    /// @brief Пошук користувача за email
    virtual OptionalUser findUserByEmail(const std::string &email);

    /// @brief Отримання облікових даних користувача
    virtual std::optional<UserCredentials> findUserCredentials(long long user_id);

    /// @brief Перевірка пароля
    virtual bool passwordIsValid(const std::string &password_to_check,
                                 const std::string &hash_password);

    /// @brief Хешування пароля
    virtual std::string getHashPassword(const std::string &raw_passport);

    /// @brief Перевірка унікальності тегу
    virtual std::optional<User> findUserWithSameTag(const std::string &tag);

private:
    GenericRepository &rep_;     ///< Репозиторій даних
    IIdGenerator *generator_;    ///< Генератор ID
};

#endif  // BACKEND_AUTHSERVICE_SRC_AUTHMANAGER_AUTHMANAGER_H_
