#ifndef SESSIONUSERCASE_H
#define SESSIONUSERCASE_H

#include <QObject>
#include <QString>

#include "managers/sessionmanager.h"

struct LogInRequest;
struct SignUpRequest;
struct User;

/// @brief Use case для керування сесією користувача (автентифікація/реєстрація)
class SessionUseCase : public QObject {
    Q_OBJECT
public:
    /// @brief Ініціалізація SessionUseCase
    explicit SessionUseCase(std::unique_ptr<SessionManager> session_manager);

    /// @brief Авторизація за токеном
    void authentificatesWithToken(const QString &token);

    /// @brief Вхід користувача
    void signIn(const LogInRequest &login_request);

    /// @brief Реєстрація користувача
    void signUp(const SignUpRequest &signup_request);

Q_SIGNALS:
    /// @brief Сигнал створення користувача та видачі токена
    void userCreated(const User &, const QString &token);

private:
    std::unique_ptr<SessionManager> session_manager_;
};

#endif  // SESSIONUSERCASE_H
