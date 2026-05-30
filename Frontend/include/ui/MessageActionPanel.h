#ifndef MESSAGEACTIONPANEL_H
#define MESSAGEACTIONPANEL_H

#include <QListView>
#include <QObject>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include "dto/Message.h"

/// @brief Delegate з фіксованою висотою елементів списку
class FixedHeightDelegate : public QStyledItemDelegate {
public:
    FixedHeightDelegate(int height, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), itemHeight(height) {}

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QSize s = QStyledItemDelegate::sizeHint(option, index);
        s.setHeight(itemHeight);
        return s;
    }

private:
    int itemHeight;  ///< Фіксована висота елемента
};

/// @brief Панель дій для повідомлення (контекстне меню + реакції)
class MessageActionPanel : public QWidget {
    Q_OBJECT
public:
    /// @brief Створення панелі для повідомлення та його реакцій
    MessageActionPanel(const Message &msg,
                       const std::vector<ReactionInfo> &reactions,
                       QWidget *parent = nullptr);

Q_SIGNALS:
    void copyClicked(const Message &msg);
    void editClicked(const Message &msg);
    void deleteClicked(const Message &msg);
    void onAnswerClicked(const Message &msg);
    void reactionClicked(const Message &msg, long long emojiId);

private:
    /// @brief Завантаження списку реакцій
    void loadEmojiReactions();

    /// @brief Обробка кліку по action елементу
    void onActionClicked(const QModelIndex &index);

    /// @brief Обробка кліку по emoji
    void onEmojiClicked(const QModelIndex &index);

    /// @brief Ініціалізація списку дій
    void setupActionList();

    /// @brief Ініціалізація emoji сітки
    void setupEmojiiGrid();

    std::vector<ReactionInfo> reactions_;  ///< Доступні реакції
    Message msg_;                          ///< Повідомлення

    QListView *actionList_;               ///< Список дій
    QStringListModel *actionModel_;       ///< Модель дій
    QListView *emojiGrid_;                ///< Сітка емодзі
    QStandardItemModel *emojiModel_;      ///< Модель емодзі
};

#endif  // MESSAGEACTIONPANEL_H
