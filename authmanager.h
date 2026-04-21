#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include "user.h"

class AuthManager : public QObject {
    Q_OBJECT
public:
    static AuthManager &instance();

    bool  signUp(const User &user, QString &error);
    User *signIn(const QString &username, const QString &password, QString &error);
    void  signOut();
    void  playAsGuest();

    User *currentUser() const;
    bool  isGuest() const;

    static bool validatePassword(const QString &password, QString &error);
    static bool validateUsername(const QString &username, QString &error);

signals:
    void userLoggedIn(User *user);   // nullptr when guest
    void userLoggedOut();

private:
    explicit AuthManager(QObject *parent = nullptr);

    User *m_currentUser = nullptr;
    bool  m_isGuest     = false;
};

#endif // AUTHMANAGER_H
