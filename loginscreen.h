#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class LoginScreen : public QWidget {
    Q_OBJECT
public:
    explicit LoginScreen(QWidget *parent = nullptr);

    void clearFields();
    void showError(const QString &message);

signals:
    void signInClicked(const QString &username, const QString &password);
    void signUpClicked();
    void guestClicked();

private slots:
    void onSignIn();

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QLabel    *m_errorLabel;
};

#endif // LOGINSCREEN_H
