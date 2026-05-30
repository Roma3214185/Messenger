#ifndef USECASEREPOSITORY_H
#define USECASEREPOSITORY_H

#include "chatusecase.h"
#include "messageusecase.h"
#include "sessionusecase.h"
#include "socketusecase.h"
#include "userusecase.h"

/// @brief Контейнер для всіх use case сервісів
class UseCaseRepository {
public:
    /// @brief Ініціалізація всіх use case компонентів
    UseCaseRepository(std::unique_ptr<ChatUseCase> chat,
                      std::unique_ptr<MessageUseCase> message,
                      std::unique_ptr<UserUseCase> user,
                      std::unique_ptr<SessionUseCase> session,
                      std::unique_ptr<SocketUseCase> socket);

    /// @brief Доступ до Chat use case
    ChatUseCase* chat();

    /// @brief Доступ до Message use case
    MessageUseCase* message();

    /// @brief Доступ до User use case
    UserUseCase* user();

    /// @brief Доступ до Session use case
    SessionUseCase* session();

    /// @brief Доступ до Socket use case
    SocketUseCase* socket();

private:
    std::unique_ptr<ChatUseCase> chat_;
    std::unique_ptr<MessageUseCase> message_;
    std::unique_ptr<UserUseCase> user_;
    std::unique_ptr<SessionUseCase> session_;
    std::unique_ptr<SocketUseCase> socket_;
};

#endif  // USECASEREPOSITORY_H
