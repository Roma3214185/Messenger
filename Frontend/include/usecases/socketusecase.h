#ifndef SOCKETUSECASE_H
#define SOCKETUSECASE_H

#include <QObject>

#include "managers/socketmanager.h"

struct Message;
struct Reaction;
struct MessageStatus;

/// @brief Use case для роботи з WebSocket та подіями реального часу
class SocketUseCase : public QObject {
    Q_OBJECT
public:
    /// @brief Ініціалізація SocketUseCase
    explicit SocketUseCase(std::unique_ptr<SocketManager> socket_manager);

    /// @brief Ініціалізація сокета для користувача
    void initSocket(long long user_id);

    /// @brief Підключення до WebSocket
    void connectSocket();

    /// @brief Відправка повідомлення через сокет
    void sendMessage(const Message &msg);

    /// @brief Подія прочитання повідомлення
    void sendReadMessageEvent(const MessageStatus &message_status);

    /// @brief Закриття з'єднання
    void close();

    /// @brief Надсилання реакції (створення)
    void saveReaction(const Reaction &reaction);

    /// @brief Видалення реакції
    void deleteReaction(const Reaction &reaction);

    /// @brief Надсилання сирого тексту в сокет
    void sendInSocket(const QString &text);

    /// @brief Надсилання JSON у сокет
    void sendInSocket(const QJsonObject &text);

Q_SIGNALS:
    /// @brief Сигнал помилки
    void errorOccurred(const QString &error);

    /// @brief Отримання нової відповіді від сервера
    void newResponce(QJsonObject &message);

private:
    /// @brief Обробка вхідного повідомлення
    void onMessageReceived(const QString &msg);

    std::unique_ptr<SocketManager> socket_manager_;
};

#endif  // SOCKETUSECASE_H
