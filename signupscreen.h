#ifndef SIGNUPSCREEN_H
#define SIGNUPSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QLabel>

class SignUpScreen : public QWidget {
    Q_OBJECT
public:
    explicit SignUpScreen(QWidget *parent = nullptr);

    void clearFields();
    void showError(const QString &message);

signals:
    void signUpSubmitted(const QString &firstName,
                         const QString &lastName,
                         const QDate   &dob,
                         const QString &gender,
                         const QString &profilePic,
                         const QString &username,
                         const QString &password);
    void backClicked();

private slots:
    void onBrowsePicture();
    void onSubmit();

private:
    QLineEdit *m_firstNameEdit;
    QLineEdit *m_lastNameEdit;
    QDateEdit *m_dobEdit;
    QComboBox *m_genderCombo;
    QLineEdit *m_profilePicEdit;
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QLineEdit *m_confirmPasswordEdit;
    QLabel    *m_errorLabel;
};

#endif // SIGNUPSCREEN_H
