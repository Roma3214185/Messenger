#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QList>
#include <optional>
#include <vector>

#include "GenericRepository.h"
#include "chatservice/interfaces/IChatManager.h"
#include "entities/Chat.h"

class IIdGenerator;

using ID = long long;

/// @brief Менеджер чатів (логіка створення та керування чатами)
class ChatManager : public IChatManager {
public:
    ChatManager(GenericRepository *repository, IIdGenerator *generator);

    /// @brief Створення приватного чату між двома користувачами
    std::optional<ID> createPrivateChat(ID first_member, ID second_user) override;

    /// @brief Додавання учасників до чату
    bool addMembersToChat(ID chat_id, const std::vector<ID> &members_id) override;

    /// @brief Отримання списку ID учасників чату
    std::vector<ID> getMembersOfChat(ID chat_id) override;

    /// @brief Отримання списку чатів користувача
    std::vector<ID> getChatsIdOfUser(ID user_id) override;

    /// @brief Кількість учасників у чаті
    int getMembersCount(ID chat_id) override;

    /// @brief Отримання другого учасника приватного чату
    std::optional<ID> getOtherMemberId(ID chat_id, ID user_id) override;

    /// @brief Отримання чату за ID
    std::optional<Chat> getChatById(ID chat_id) override;

    /// @brief Отримання приватного чату між двома користувачами
    std::optional<PrivateChat> getPrivateChat(ID first_user_id, ID second_user_id) override;

private:
    GenericRepository *repository_;  ///< Репозиторій даних
    IIdGenerator *generator_;        ///< Генератор ID
};

#endif  // CHATMANAGER_H
