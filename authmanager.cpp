#include "authmanager.h"
#include "userdatabase.h"

#include <QRegularExpression>

AuthManager &AuthManager::instance() {
    static AuthManager mgr;
    return mgr;
}

AuthManager::AuthManager(QObject *parent) : QObject(parent) {}

bool AuthManager::signUp(const User &user, QString &error) {
    QString usernameError;
    if (!validateUsername(user.username, usernameError)) {
        error = usernameError;
        return false;
    }
    if (UserDatabase::instance().usernameExists(user.username)) {
        error = "Username is already taken.";
        return false;
    }
    if (!UserDatabase::instance().addUser(user)) {
        error = "Failed to save user data.";
        return false;
    }
    return true;
}

User *AuthManager::signIn(const QString &username, const QString &password, QString &error) {
    User *user = UserDatabase::instance().findUser(username);
    if (user == nullptr) {
        error = "Username not found.";
        return nullptr;
    }
    if (!User::checkPassword(password, user->passwordHash)) {
        error = "Incorrect password.";
        return nullptr;
    }
    m_currentUser = user;
    m_isGuest     = false;
    emit userLoggedIn(m_currentUser);
    return m_currentUser;
}

void AuthManager::signOut() {
    m_currentUser = nullptr;
    m_isGuest     = false;
    emit userLoggedOut();
}

void AuthManager::playAsGuest() {
    m_currentUser = nullptr;
    m_isGuest     = true;
    emit userLoggedIn(nullptr);
}

User *AuthManager::currentUser() const {
    return m_currentUser;
}

bool AuthManager::isGuest() const {
    return m_isGuest;
}

bool AuthManager::validatePassword(const QString &password, QString &error) {
    if (password.length() < 8) {
        error = "Password must be at least 8 characters long.";
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (const QChar &c : password) {
        if (c.isUpper()) hasUpper = true;
        if (c.isLower()) hasLower = true;
        if (c.isDigit()) hasDigit = true;
    }
    if (!hasUpper) {
        error = "Password must contain at least one uppercase letter.";
        return false;
    }
    if (!hasLower) {
        error = "Password must contain at least one lowercase letter.";
        return false;
    }
    if (!hasDigit) {
        error = "Password must contain at least one number.";
        return false;
    }
    return true;
}

bool AuthManager::validateUsername(const QString &username, QString &error) {
    if (username.isEmpty()) {
        error = "Username cannot be empty.";
        return false;
    }
    if (username.length() < 3) {
        error = "Username must be at least 3 characters.";
        return false;
    }
    QRegularExpression re("^[a-zA-Z0-9_]+$");
    if (!re.match(username).hasMatch()) {
        error = "Username may only contain letters, numbers, and underscores.";
        return false;
    }
    return true;
}
