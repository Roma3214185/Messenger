#ifndef REACTION_H
#define REACTION_H

#include <crow.h>
#include <crow/json.h>
#include <nlohmann/json.hpp>
#include <optional>

#include "Debug_profiling.h"

/// @brief Реакція користувача на повідомлення
struct Reaction final {
    long long message_id{0};    ///< ID повідомлення
    long long receiver_id{0};   ///< ID користувача, який поставив реакцію
    long long reaction_id{0};   ///< Тип реакції (1-like, 2-dislike, 3-smile, 4-heart)

    Reaction() = default;

    Reaction(long long p_message_id,
             long long p_receiver_id,
             long long p_reaction_id)
        : message_id(p_message_id),
        receiver_id(p_receiver_id),
        reaction_id(p_reaction_id) {
        DBC_REQUIRE(checkInvariants());
        LOG_INFO("Reaction {} from {}, type {}", message_id, receiver_id, reaction_id);
    }

    /// @brief Перевірка коректності об’єкта
    bool checkInvariants() const {
        return message_id > 0 && receiver_id > 0 && reaction_id > 0;
    }
};

namespace utils::entities {

/// @brief Парсинг Reaction з Crow JSON
inline std::optional<Reaction> parseReaction(const crow::json::rvalue &json) {
    Reaction reaction;

    if (json.has("message_id")) reaction.message_id = json["message_id"].i();
    if (json.has("receiver_id")) reaction.receiver_id = json["receiver_id"].i();
    if (json.has("reaction_id")) reaction.reaction_id = json["reaction_id"].i();

    return reaction.checkInvariants() ? std::make_optional(reaction) : std::nullopt;
}

/// @brief (Некоректна/дублююча функція парсингу Reaction)
inline std::optional<Reaction> parseLongLong(const crow::json::rvalue &json,
                                             const std::string &field) {
    Reaction reaction;

    if (json.has("message_id")) reaction.message_id = json["message_id"].i();
    if (json.has("receiver_id")) reaction.receiver_id = json["receiver_id"].i();
    if (json.has("reaction_id")) reaction.reaction_id = json["reaction_id"].i();

    return reaction.checkInvariants() ? std::make_optional(reaction) : std::nullopt;
}

}  // namespace utils::entities

namespace nlohmann {

/// @brief JSON (de)serialization для Reaction
template <>
struct adl_serializer<Reaction> {
    static void to_json(nlohmann::json &json_message, const Reaction &user_reaction) {
        json_message = nlohmann::json{
            {"message_id", user_reaction.message_id},
            {"receiver_id", user_reaction.receiver_id},
            {"reaction_id", user_reaction.reaction_id}
        };
    }

    static void from_json(const nlohmann::json &json_message, Reaction &user_reaction) {
        json_message.at("message_id").get_to(user_reaction.message_id);
        json_message.at("receiver_id").get_to(user_reaction.receiver_id);
        json_message.at("reaction_id").get_to(user_reaction.reaction_id);
    }
};

}  // namespace nlohmann

#endif  // REACTION_H
