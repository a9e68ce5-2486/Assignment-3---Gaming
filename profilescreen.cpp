#include "profilescreen.h"
#include "styles.h"
#include "authmanager.h"
#include "userdatabase.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QFont>
#include <QFrame>
#include <QHeaderView>

ProfileScreen::ProfileScreen(QWidget *parent) : QWidget(parent) {
    setStyleSheet(appStyleSheet());

    auto *outer = new QVBoxLayout(this);
    outer->setSpacing(14);
    outer->setContentsMargins(30, 20, 30, 20);

    // Title bar
    auto *topRow = new QHBoxLayout;
    auto *titleLabel = new QLabel("My Profile");
    titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #e94560;");
    auto *backBtn = new QPushButton("Back");
    backBtn->setStyleSheet(
        "QPushButton { background: transparent; border: 1px solid #555; color: #aaa; padding: 6px 14px; }"
        "QPushButton:hover { background: #e94560; color: white; border-color: #e94560; }"
    );
    connect(backBtn, &QPushButton::clicked, this, &ProfileScreen::backClicked);
    topRow->addWidget(titleLabel);
    topRow->addStretch();
    topRow->addWidget(backBtn);
    outer->addLayout(topRow);

    // Profile info card
    auto *infoCard = new QFrame;
    infoCard->setStyleSheet("background: #16213e; border-radius: 10px;");
    auto *infoLayout = new QHBoxLayout(infoCard);
    infoLayout->setContentsMargins(20, 16, 20, 16);
    infoLayout->setSpacing(20);

    m_avatarLabel = new QLabel;
    m_avatarLabel->setFixedSize(80, 80);
    m_avatarLabel->setAlignment(Qt::AlignCenter);
    m_avatarLabel->setStyleSheet(
        "border-radius: 40px; background: #0f3460; "
        "color: #e94560; font-size: 28px; font-weight: bold;"
    );
    infoLayout->addWidget(m_avatarLabel);

    m_infoLabel = new QLabel;
    m_infoLabel->setStyleSheet("font-size: 13px; line-height: 1.6;");
    m_infoLabel->setWordWrap(true);
    infoLayout->addWidget(m_infoLabel, 1);
    outer->addWidget(infoCard);

    // Score history
    auto *histLabel = new QLabel("Score History");
    histLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #e0e0e0;");
    outer->addWidget(histLabel);

    m_scoreTable = new QTableWidget(0, 5);
    m_scoreTable->setHorizontalHeaderLabels(
        {"Date & Time", "Game", "Score", "Personal Best", "Global Best"}
    );
    m_scoreTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_scoreTable->verticalHeader()->hide();
    m_scoreTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_scoreTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_scoreTable->setAlternatingRowColors(true);
    m_scoreTable->setStyleSheet(
        "QTableWidget { alternate-background-color: #1a2540; }"
    );
    outer->addWidget(m_scoreTable, 1);
}

void ProfileScreen::refresh() {
    User *user = AuthManager::instance().currentUser();
    if (user == nullptr) return;

    // Avatar
    QPixmap pic(user->profilePicturePath);
    if (!pic.isNull()) {
        m_avatarLabel->setPixmap(
            pic.scaled(80, 80, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)
               .copy(0, 0, 80, 80)
        );
        m_avatarLabel->setStyleSheet("border-radius: 40px; border: 2px solid #e94560;");
    } else {
        QString initials = QString("%1%2")
            .arg(user->firstName.isEmpty() ? "?" : QString(user->firstName[0]).toUpper())
            .arg(user->lastName.isEmpty()  ? ""  : QString(user->lastName[0]).toUpper());
        m_avatarLabel->setText(initials);
        m_avatarLabel->setStyleSheet(
            "border-radius: 40px; background: #0f3460; "
            "color: #e94560; font-size: 24px; font-weight: bold;"
        );
    }

    // Info text
    QString gender = user->gender.isEmpty() || user->gender == "Prefer not to say"
                     ? "Not specified"
                     : user->gender;
    m_infoLabel->setText(
        QString("<b>%1 %2</b><br>"
                "Username: %3<br>"
                "Date of Birth: %4<br>"
                "Gender: %5")
            .arg(user->firstName, user->lastName)
            .arg(user->username)
            .arg(user->dateOfBirth.toString("MMMM d, yyyy"))
            .arg(gender)
    );

    // Score table
    m_scoreTable->setRowCount(0);
    const QVector<ScoreEntry> &history = user->scoreHistory;

    // Show newest first
    for (int i = history.size() - 1; i >= 0; i--) {
        const ScoreEntry &e = history[i];
        int row = m_scoreTable->rowCount();
        m_scoreTable->insertRow(row);

        m_scoreTable->setItem(row, 0,
            new QTableWidgetItem(e.timestamp.toString("yyyy-MM-dd  hh:mm")));
        m_scoreTable->setItem(row, 1,
            new QTableWidgetItem(e.gameName));
        m_scoreTable->setItem(row, 2,
            new QTableWidgetItem(QString::number(e.score)));
        m_scoreTable->setItem(row, 3,
            new QTableWidgetItem(QString::number(user->bestScore(e.gameName))));
        m_scoreTable->setItem(row, 4,
            new QTableWidgetItem(
                QString::number(UserDatabase::instance().globalBestScore(e.gameName))
            )
        );
    }

    if (history.isEmpty()) {
        m_scoreTable->setRowCount(1);
        auto *placeholder = new QTableWidgetItem("No games played yet.");
        placeholder->setTextAlignment(Qt::AlignCenter);
        m_scoreTable->setItem(0, 0, placeholder);
        m_scoreTable->setSpan(0, 0, 1, 5);
    }
}
