#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "user.h"
#include <QVector>
#include <QString>

class UserDatabase {
public:
    static UserDatabase &instance();

    bool load(const QString &filepath = "users.json");
    bool save() const;

    bool  addUser(const User &user);
    User *findUser(const QString &username);
    bool  updateUser(const User &user);
    bool  usernameExists(const QString &username) const;
    int   globalBestScore(const QString &gameName) const;

private:
    UserDatabase() = default;

    QVector<User> m_users;
    QString       m_filePath;
};

#endif // USERDATABASE_H
