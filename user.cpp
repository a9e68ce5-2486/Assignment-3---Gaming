#include "user.h"

#include <QCryptographicHash>
#include <QJsonArray>

// ---------- ScoreEntry ----------

QJsonObject ScoreEntry::toJson() const {
    QJsonObject obj;
    obj["gameName"]  = gameName;
    obj["score"]     = score;
    obj["timestamp"] = timestamp.toString(Qt::ISODate);
    return obj;
}

ScoreEntry ScoreEntry::fromJson(const QJsonObject &obj) {
    ScoreEntry e;
    e.gameName  = obj["gameName"].toString();
    e.score     = obj["score"].toInt();
    e.timestamp = QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate);
    return e;
}

// ---------- User ----------

bool User::isBirthdayToday() const {
    QDate today = QDate::currentDate();
    return dateOfBirth.isValid()
        && dateOfBirth.month() == today.month()
        && dateOfBirth.day()   == today.day();
}

void User::addScore(const QString &gameName, int score) {
    ScoreEntry e;
    e.gameName  = gameName;
    e.score     = score;
    e.timestamp = QDateTime::currentDateTime();
    scoreHistory.append(e);
}

int User::bestScore(const QString &gameName) const {
    int best = 0;
    for (const ScoreEntry &e : scoreHistory) {
        if (e.gameName == gameName && e.score > best)
            best = e.score;
    }
    return best;
}

QJsonObject User::toJson() const {
    QJsonObject obj;
    obj["firstName"]         = firstName;
    obj["lastName"]          = lastName;
    obj["dateOfBirth"]       = dateOfBirth.toString("yyyy-MM-dd");
    obj["gender"]            = gender;
    obj["profilePicturePath"]= profilePicturePath;
    obj["username"]          = username;
    obj["passwordHash"]      = passwordHash;

    QJsonArray arr;
    for (const ScoreEntry &e : scoreHistory)
        arr.append(e.toJson());
    obj["scoreHistory"] = arr;

    return obj;
}

User User::fromJson(const QJsonObject &obj) {
    User u;
    u.firstName          = obj["firstName"].toString();
    u.lastName           = obj["lastName"].toString();
    u.dateOfBirth        = QDate::fromString(obj["dateOfBirth"].toString(), "yyyy-MM-dd");
    u.gender             = obj["gender"].toString();
    u.profilePicturePath = obj["profilePicturePath"].toString();
    u.username           = obj["username"].toString();
    u.passwordHash       = obj["passwordHash"].toString();

    for (const QJsonValue &v : obj["scoreHistory"].toArray())
        u.scoreHistory.append(ScoreEntry::fromJson(v.toObject()));

    return u;
}

QString User::hashPassword(const QString &password) {
    QByteArray hash = QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Sha256
    );
    return QString(hash.toHex());
}

bool User::checkPassword(const QString &password, const QString &hash) {
    return hashPassword(password) == hash;
}
