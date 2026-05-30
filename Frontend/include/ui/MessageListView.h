#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QListView>

class MessageModel;

/// @brief Список повідомлень з додатковим керуванням скролом та навігацією
class MessageListView : public QListView {
    Q_OBJECT
public:
    using Callback = std::function<void()>;

    /// @brief Створення view для повідомлень
    explicit MessageListView(QWidget *parent = nullptr);

    /// @brief Встановлення моделі повідомлень
    void setMessageModel(MessageModel *model);

    /// @brief Прокрутка до останнього повідомлення
    void scrollListToBottom();

    /// @brief Максимальне значення скролбара
    int getMaximumMessageScrollBar() const;

    /// @brief Поточне значення скролбара
    int getMessageScrollBarValue() const;

    /// @brief Встановлення значення скролбара
    void setMessageScrollBarValue(int value);

    /// @brief Збереження фокуса під час оновлення моделі
    void preserveFocusWhile(MessageModel *message_model, Callback update_model);

    /// @brief Пошук індексу за ID повідомлення
    QModelIndex findIndexByMessageId(long long id);

    /// @brief Прокрутка до конкретного повідомлення
    void scrollToMessage(const QModelIndex &index_to_scroll);

    /// @brief Обробка кліку миші
    void mousePressEvent(QMouseEvent *event) override;

Q_SIGNALS:
    void scrollChanged(int value);
    void clickedWithEvent(QMouseEvent *event);
};

#endif  // MESSAGELISTVIEW_H
