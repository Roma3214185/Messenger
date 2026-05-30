#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include <optional>

#include "Message.h"
#include "ReactionInfo.h"

/// @brief Розширене повідомлення користувача (з реакціями та статусом прочитання)
struct UserMessage {
    Message message;  ///< Базове повідомлення

    /// @brief Дані про прочитання
    struct {
        int count{0};        ///< Кількість прочитань
        bool read_by_me;     ///< Чи прочитано мною
    } read;

    /// @brief Дані про реакції
    struct {
        std::unordered_map<ReactionInfo, int> counts;  ///< Кількість реакцій по типах
        std::optional<long long> my_reaction;          ///< Моя реакція (якщо є)
    } reactions;
};

namespace nlohmann {

/// @brief JSON (de)serialization для UserMessage
template <>
struct adl_serializer<UserMessage> {
    static void to_json(nlohmann::json &j, const UserMessage &m) {
        j = nlohmann::json(m.message);

        j["read"] = {
            {"count", m.read.count},
            {"receiver_read_status", m.read.read_by_me}
        };

        j["reactions"]["counts"] = m.reactions.counts;

        if (m.reactions.my_reaction.has_value()) {
            j["reactions"]["receiver_reaction"] = *m.reactions.my_reaction;
        } else {
            j["reactions"]["receiver_reaction"] = nullptr;
        }
    }

    static void from_json(const nlohmann::json &j, UserMessage &m) {
        j.at("message").get_to(m.message);

        if (j.contains("read")) {
            if (j["read"].contains("receiver_read_status"))
                j["read"].at("receiver_read_status").get_to(m.read.read_by_me);

            if (j["read"].contains("count"))
                j["read"].at("count").get_to(m.read.count);
        }

        if (j.contains("reactions")) {
            if (j["reactions"].contains("counts"))
                j["reactions"].at("counts").get_to(m.reactions.counts);

            if (j["reactions"].contains("receiver_reaction") &&
                !j["reactions"]["receiver_reaction"].is_null()) {
                m.reactions.my_reaction = j["reactions"]["receiver_reaction"].get<int>();
            } else {
                m.reactions.my_reaction.reset();
            }
        }
    }
};

}  // namespace nlohmann

#endif  // USERMESSAGE_H
