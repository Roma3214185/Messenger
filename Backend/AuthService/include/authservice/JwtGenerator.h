#ifndef JWTGENERATOR_H
#define JWTGENERATOR_H

#include <fstream>

#include "JwtUtils.h"
#include "interfaces/IGenerator.h"

/// @brief Генератор JWT токенів та криптографічних ключів
class JwtGenerator : public IGenerator {
public:
    /// @brief Генерація пари ключів (public/private)
    bool generateKeys() override;

    /// @brief Створення JWT токена для користувача
    std::string generateToken(long long user_id) override;

private:
    /// @brief Збереження ключа у файл
    void saveInFile(const std::string &file_name, const std::string &key);
};

#endif  // JWTGENERATOR_H
