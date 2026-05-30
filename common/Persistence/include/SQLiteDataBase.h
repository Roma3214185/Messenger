#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <QSqlDatabase>
#include <QThread>

#include "Debug_profiling.h"
#include "interfaces/IDataBase.h"
#include "query/SQLiteQuery.h"

/// @brief Реалізація бази даних SQLite через Qt SQL API
class SQLiteDatabase : public IDataBase {
public:
    /// @brief Створює підключення до бази даних
    explicit SQLiteDatabase(QString db_name) : db_name_(std::move(db_name)) {}

    /// @brief Повертає об'єкт підключення до БД
    [[nodiscard]] QSqlDatabase db() const;

    /// @brief Виконує SQL-запит
    [[nodiscard]] bool exec(const QString &sql) override;

    /// @brief Підготовка запиту (std::string)
    std::unique_ptr<IQuery> prepare(const std::string &sql) override;

    /// @brief Відкат транзакції
    void rollback() override;

    /// @brief Початок транзакції
    bool transaction() override;

    /// @brief Підготовка запиту (QString)
    std::unique_ptr<IQuery> prepare(const QString &sql) override;

    /// @brief Підтвердження транзакції
    bool commit() override;

    /// @brief Ініціалізація схеми БД
    bool initializeSchema();

    /// @brief Перевірка існування таблиці
    bool tableExists(const QString &table_name);

    /// @brief Видалення таблиці
    bool deleteTable(const QString &name);

protected:
    /// @brief Виконання SQL у конкретному підключенні
    bool executeSql(const QSqlDatabase &db, const QString &sql);

private:
    QString db_name_; ///< Назва/шлях до бази даних
};

#endif  // SQLITEDATABASE_H
