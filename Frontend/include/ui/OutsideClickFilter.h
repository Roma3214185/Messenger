#ifndef OUTSIDECLICKFILTER_H
#define OUTSIDECLICKFILTER_H

#include <QEvent>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>

/// @brief Фільтр подій для визначення кліків поза межами popup-віджета
class OutsideClickFilter final : public QObject {
    Q_OBJECT
public:
    using EventCallback = std::function<void()>;

    /// @brief Створення фільтра для конкретного popup віджета
    explicit OutsideClickFilter(QWidget *popupWidget);

    /// @brief Перевірка кліку поза межами popup
    void checkClickOutside(QPointF point);

    /// @brief Додавання дозволеного віджета (клік по ньому не закриває popup)
    void addAcceptableClickableWidget(QWidget *widget);

private:
    /// @brief Обробка подій через event filter
    bool eventFilter(QObject *obj, QEvent *event) override;

    /// @brief Перевірка, чи клік був поза межами дозволених зон
    bool clickIsOutside(QPointF point);

    QWidget *popup_;                              ///< Віджет popup
    std::vector<QWidget *> clickable_widgets_;    ///< Дозволені для кліку віджети
};

#endif  // OUTSIDECLICKFILTER_H
