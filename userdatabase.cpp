#include "userdatabase.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

UserDatabase &UserDatabase::instance() {
    static UserDatabase db;
    return db;
}

bool UserDatabase::load(const QString &filepath) {
    m_filePath = filepath;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
        return true;  // empty database is fine on first run

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray())
        return false;

    m_users.clear();
    for (const QJsonValue &v : doc.array())
        m_users.append(User::fromJson(v.toObject()));

    return true;
}

bool UserDatabase::save() const {
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonArray arr;
    for (const User &u : m_users)
        arr.append(u.toJson());

    file.write(QJsonDocument(arr).toJson());
    file.close();
    return true;
}

bool UserDatabase::addUser(const User &user) {
    if (usernameExists(user.username))
        return false;
    m_users.append(user);
    return save();
}

User *UserDatabase::findUser(const QString &username) {
    for (User &u : m_users) {
        if (u.username == username)
            return &u;
    }
    return nullptr;
}

bool UserDatabase::updateUser(const User &user) {
    for (User &u : m_users) {
        if (u.username == user.username) {
            u = user;
            return save();
        }
    }
    return false;
}

bool UserDatabase::usernameExists(const QString &username) const {
    for (const User &u : m_users) {
        if (u.username == username)
            return true;
    }
    return false;
}

int UserDatabase::globalBestScore(const QString &gameName) const {
    int best = 0;
    for (const User &u : m_users) {
        int s = u.bestScore(gameName);
        if (s > best)
            best = s;
    }
    return best;
}
