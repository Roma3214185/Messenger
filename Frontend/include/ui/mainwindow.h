#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "dto/Message.h"
#include "interfaces/IMainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Presenter;
class ChatBase;
class QListView;
class ITheme;
class MessageListView;
class MessageDelegate;
class MessageModel;
class ClickOutsideClosableListView;
class QStandardItemModel;
class DelegatorsFactory;
class QTextCursor;
class Model;
struct ReactionInfo;
struct MessageToken;

using MessageId = long long;
using ThemePtr = std::unique_ptr<ITheme>;

/// @brief Головне вікно застосунку (UI рівень)
class MainWindow final : public QMainWindow, public IMainWindow {
    Q_OBJECT

public:
    /// @brief Ініціалізація головного вікна
    MainWindow(Model *model, DelegatorsFactory *delegators_factory, QWidget *parent = nullptr);

    ~MainWindow() final;

    /// @brief Встановлення активного чату
    void setChatWindow(std::shared_ptr<ChatBase> chat) override;

    /// @brief Встановлення моделі чатів
    void setChatModel(ChatModel *model) override;

    /// @brief Встановлення моделі користувача
    void setUserModel(UserModel *user_model) override;

    /// @brief Очищення поля пошуку користувачів
    void clearFindUserEdit();

    /// @brief Показ помилки
    void showError(const QString &error) override;

    /// @brief Встановлення індексу поточного чату
    void setCurrentChatIndex(QModelIndex chat_idx) override;

    /// @brief Фільтрація подій UI
    bool eventFilter(QObject *, QEvent *event) override;

    /// @brief Встановлення Presenter
    void setPresenter(Presenter *presenter);

    /// @brief Ініціалізація UI
    void initialise();

Q_SIGNALS:
    void clickedOnScreenPosition(QPoint point);
    void screenGeometryChanged();

private Q_SLOTS:
    void on_upSubmitButton_clicked();
    void on_inSubmitButton_clicked();
    void on_userTextEdit_textChanged(const QString &changed_text);
    void on_textEdit_textChanged();
    void on_sendButton_clicked();
    void on_logoutButton_clicked();
    void on_themeButton_clicked(bool checked);
    void on_cancelEditMessageButton_clicked();
    void on_okEditButton_clicked();
    void on_editTextEdit_textChanged();
    void on_search_messages_line_edit_textChanged(const QString &message_to_search_users);
    void on_serch_messages_list_view_clicked(const QModelIndex &index_clicked);
    void on_EmojiButtonStateChanged(bool open_emoji_meu);
    void on_PressEvent(QMouseEvent *event);
    void on_EmojiClicked(const ReactionInfo &emoji);
    void on_MessageContextMenu(const QPoint &pos);
    void on_ReactionClicked(const QPoint &pos);

private:
    void closeEmojiMenu(bool close_manually = true);
    void setWriteMode();
    void setTheme(ThemePtr theme);
    void setMainWindow() const;
    void cancelSearchMessagesMode();
    void setSignInPage();
    void setMessageListView();
    void setSignUpPage();
    void clearSignUpPage();
    void setDelegators();
    void setupConnections();
    void setupUI();
    void openEmojiMenu();
    void scrollСhatToMessage(const QModelIndex &index_to_scroll);
    void copyMessage(const Message &message);
    void editMessage(const Message &message);
    void deleteMessage(const Message &message);
    void closeChatWidget();

    void setSearchMessageMode();
    void setTitleChatMode();
    QStandardItemModel *getEmojiModel();
    void setupUserListView();
    void setupSearchMessageListView();
    void setupEmojiMenu();
    void resetMessageAnswerOnMode();
    void setMessageAnswerOnMode(const Message &message_to_answer);
    void clearSignInPage();
    void insertTokens(QTextCursor &cursor, const std::vector<MessageToken> &message_tokens);

    ThemePtr current_theme_;
    Ui::MainWindow *ui;
    Presenter *presenter_{nullptr};
    DelegatorsFactory *delegators_factory_;
    std::unique_ptr<MessageListView> message_list_view_;
    MessageDelegate *message_delegate_;
    std::optional<Message> editable_message_;  ///< Поточне редаговане повідомлення
    std::unique_ptr<MessageModel> search_results_model_;
    std::optional<MessageId> answer_on_message_;

    ClickOutsideClosableListView *user_list_view_{nullptr};        ///< Список користувачів
    ClickOutsideClosableListView *search_message_list_view_{nullptr}; ///< Пошук повідомлень
    ClickOutsideClosableListView *emoji_menu_{nullptr};            ///< Меню емодзі
};

#endif  // MAINWINDOW_H
