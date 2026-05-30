#ifndef REQUESTDTO_H
#define REQUESTDTO_H

#include <crow.h>

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

/// @brief DTO HTTP-запиту
struct RequestDTO {
    std::string path;  ///< Шлях запиту
    std::string method;  ///< HTTP метод
    std::string body;  ///< Тіло запиту
    std::string request_id;  ///< ID запиту
    std::string content_type;  ///< Content-Type
    std::vector<std::pair<std::string, std::string>> headers;  ///< Заголовки
    std::string token;  ///< Authorization token
    std::unordered_map<std::string, std::string> url_params;  ///< URL параметри
};

namespace utils::details {

/// @brief Отримання Content-Type
inline std::string getContentType(const crow::request &req) {
    std::string content_type = req.get_header_value("content-type");
    return content_type.empty() ? "application/json" : content_type;
}

/// @brief Витяг токена авторизації
inline std::string extractToken(const crow::request &req) {
    return req.get_header_value("Authorization");
}

/// @brief Формування JSON помилки
inline std::string formError(const std::string &error_text) {
    return nlohmann::json{{"error", error_text}}.dump();
}

}  // namespace utils::details

namespace utils {

/// @brief Конвертація Crow request → RequestDTO
inline RequestDTO getDTO(const crow::request &req,
                         const std::string &path,
                         const std::string &request_id = "-1") {
    RequestDTO request_info;

    request_info.method = crow::method_name(req.method);
    request_info.path = path;
    request_info.body = req.body;
    request_info.content_type = utils::details::getContentType(req);
    request_info.request_id = request_id;
    request_info.token = utils::details::extractToken(req);

    auto keys = req.url_params.keys();
    for (const std::string &key : keys) {
        request_info.url_params.emplace(key, req.url_params.get(key));
    }

    for (auto const &header : req.headers) {
        request_info.headers.emplace_back(header.first, header.second);
    }

    return request_info;
}

}  // namespace utils

namespace nlohmann {

/// @brief JSON (de)serialization для RequestDTO
template <>
struct adl_serializer<RequestDTO> {
    static void to_json(json &j, const RequestDTO &r) {
        j = json{
            {"path", r.path},
            {"method", r.method},
            {"body", r.body},
            {"request_id", r.request_id},
            {"content_type", r.content_type},
            {"headers", r.headers},
            {"url_params", r.url_params}
        };
    }

    static void from_json(const json &j, RequestDTO &r) {
        j.at("path").get_to(r.path);
        j.at("method").get_to(r.method);
        j.at("body").get_to(r.body);
        j.at("request_id").get_to(r.request_id);
        j.at("content_type").get_to(r.content_type);
        j.at("headers").get_to(r.headers);
        j.at("url_params").get_to(r.url_params);
    }
};

}  // namespace nlohmann

#endif  // REQUESTDTO_H
