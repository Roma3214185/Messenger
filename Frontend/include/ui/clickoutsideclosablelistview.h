#ifndef CLICKOUTSIDECLOSABLELISTVIEW_H
#define CLICKOUTSIDECLOSABLELISTVIEW_H

#include <QListView>
#include <QObject>
#include <QWidget>

class OutsideClickFilter;

/// @brief QListView, що закривається при кліку поза межами віджета
class ClickOutsideClosableListView final : public QListView {
public:
    using EventCallback = std::function<void()>;

    /// @brief Створення списку з підтримкою закриття по кліку поза межами
    explicit ClickOutsideClosableListView(QWidget* parent);

    /// @brief Додати дозволений віджет (клік по ньому не закриває список)
    void addAcceptableClickableWidget(QWidget* widget);

    /// @brief Встановлення моделі даних
    void setModel(QAbstractItemModel* model) override;

    /// @brief Колбек оновлення
    void setUpdateCallback(EventCallback update_callback);

    /// @brief Колбек закриття
    void setOnCloseCallback(EventCallback close_callback);

private:
    /// @brief Обробка події показу
    void showEvent(QShowEvent* event) override;

    /// @brief Обробка події закриття
    void closeEvent(QCloseEvent* event) override;

    /// @brief Виклик callback закриття
    void call_close_callback();

    /// @brief Оновлення стану (callback)
    inline void update();

    std::optional<EventCallback> update_callback_;  ///< Колбек оновлення
    std::optional<EventCallback> close_callback_;   ///< Колбек закриття
    OutsideClickFilter* filter_;                    ///< Фільтр зовнішніх кліків
};

#endif  // CLICKOUTSIDECLOSABLELISTVIEW_H
