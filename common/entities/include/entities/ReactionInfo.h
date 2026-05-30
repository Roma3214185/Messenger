#ifndef REACTIONINFO_H
#define REACTIONINFO_H

#include <nlohmann/json.hpp>
#include <string>

/// @brief Інформація про тип реакції
struct ReactionInfo {
    long long id{0};     ///< ID реакції
    std::string image;   ///< Іконка/зображення реакції

    /// @brief Перевірка коректності об’єкта
    bool checkInvariants() const { return id > 0 && !image.empty(); }
};

/// @brief Порівняння ReactionInfo
inline bool operator==(const ReactionInfo &a, const ReactionInfo &b) {
    return a.id == b.id && a.image == b.image;
}

namespace nlohmann {

/// @brief JSON (de)serialization для ReactionInfo
template <>
struct adl_serializer<ReactionInfo> {
    static void to_json(nlohmann::json &json_message, const ReactionInfo &user_reaction) {
        json_message["image"] = user_reaction.image;
        json_message["id"] = user_reaction.id;
    }

    static void from_json(const nlohmann::json &json_message, ReactionInfo &user_reaction) {
        user_reaction.image = json_message["image"];
        user_reaction.id = json_message["id"];
    }
};

}  // namespace nlohmann

namespace std {

/// @brief Hash спеціалізація для використання в unordered_set/map
template <>
struct hash<ReactionInfo> {
    size_t operator()(const ReactionInfo &r) const noexcept {
        return std::hash<long long>{}(r.id);
    }
};

}  // namespace std

#endif  // REACTIONINFO_H
