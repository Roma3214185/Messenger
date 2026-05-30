#ifndef BACKEND_MESSAGESERVICE_HEADERS_MESSAGESTATUS_H_
#define BACKEND_MESSAGESERVICE_HEADERS_MESSAGESTATUS_H_

#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>
#include <tuple>

#include "Debug_profiling.h"
#include "Fields.h"
#include "TimestampService.h"

/// @brief Статус повідомлення (прочитано/доставлено)
struct MessageStatus final {
    long long message_id{0};     ///< ID повідомлення
    long long receiver_id{0};    ///< ID отримувача
    long long read_at{0};        ///< Час прочитання
    bool is_read{false};         ///< Ознака прочитання

    MessageStatus() = default;

    MessageStatus(long long message_id,
                  long long receiver_id,
                  bool is_read = false,
                  long long read_at = utils::time::getCurrentTime())
        : message_id(message_id),
        receiver_id(receiver_id),
        read_at(read_at),
        is_read(is_read) {
        DBC_REQUIRE(checkInvariants());
    }

    /// @brief Перевірка коректності стану об’єкта
    bool checkInvariants() const { return message_id > 0 && receiver_id > 0; }
};

namespace nlohmann {

/// @brief JSON (de)serialization для MessageStatus
template <>
struct adl_serializer<MessageStatus> {
    static void to_json(nlohmann::json &json_message_status, const MessageStatus &message_status) {
        json_message_status = nlohmann::json{
            {MessageStatusTable::MessageId, message_status.message_id},
            {MessageStatusTable::ReceiverId, message_status.receiver_id},
            {MessageStatusTable::IsRead, message_status.is_read},
            {MessageStatusTable::ReatAt, message_status.read_at}
        };
    }

    static void from_json(const nlohmann::json &json_message_status, MessageStatus &message_status) {
        json_message_status.at(MessageStatusTable::MessageId).get_to(message_status.message_id);
        json_message_status.at(MessageStatusTable::ReceiverId).get_to(message_status.receiver_id);
        json_message_status.at(MessageStatusTable::IsRead).get_to(message_status.is_read);
        json_message_status.at(MessageStatusTable::ReatAt).get_to(message_status.read_at);
    }
};

}  // namespace nlohmann

#endif  // BACKEND_MESSAGESERVICE_HEADERS_MESSAGESTATUS_H_
