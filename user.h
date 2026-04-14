#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

struct ScoreEntry {
    QString gameName;
    int score;
    QDateTime timestamp;

    QJsonObject toJson() const;
    static ScoreEntry fromJson(const QJsonObject &obj);
};

class User {
public:
    User() = default;

    QString firstName;
    QString lastName;
    QDate   dateOfBirth;
    QString gender;
    QString profilePicturePath;
    QString username;
    QString passwordHash;
    QVector<ScoreEntry> scoreHistory;

    bool isBirthdayToday() const;
    void addScore(const QString &gameName, int score);
    int  bestScore(const QString &gameName) const;

    QJsonObject toJson() const;
    static User fromJson(const QJsonObject &obj);

    static QString hashPassword(const QString &password);
    static bool    checkPassword(const QString &password, const QString &hash);
};

#endif // USER_H
