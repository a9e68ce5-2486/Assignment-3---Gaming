#include "homescreen.h"
#include "styles.h"
#include "authmanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QFont>
#include <QFrame>

HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent) {
    setStyleSheet(appStyleSheet());

    auto *outer = new QVBoxLayout(this);
    outer->setAlignment(Qt::AlignCenter);
    outer->setSpacing(18);

    // --- Profile card ---
    auto *card = new QFrame;
    card->setFixedWidth(480);
    card->setStyleSheet("background: #16213e; border-radius: 14px; padding: 10px;");
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setAlignment(Qt::AlignCenter);
    cardLayout->setSpacing(10);
    cardLayout->setContentsMargins(24, 24, 24, 24);

    m_avatarLabel = new QLabel;
    m_avatarLabel->setFixedSize(100, 100);
    m_avatarLabel->setAlignment(Qt::AlignCenter);
    m_avatarLabel->setStyleSheet(
        "border-radius: 50px; background: #0f3460; "
        "color: #e94560; font-size: 36px; font-weight: bold;"
    );
    cardLayout->addWidget(m_avatarLabel, 0, Qt::AlignCenter);

    m_nameLabel = new QLabel;
    m_nameLabel->setAlignment(Qt::AlignCenter);
    m_nameLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #e0e0e0;");
    cardLayout->addWidget(m_nameLabel);

    m_dateLabel = new QLabel;
    m_dateLabel->setAlignment(Qt::AlignCenter);
    m_dateLabel->setStyleSheet("font-size: 13px; color: #888;");
    cardLayout->addWidget(m_dateLabel);

    m_greetingLabel = new QLabel;
    m_greetingLabel->setAlignment(Qt::AlignCenter);
    m_greetingLabel->setStyleSheet(
        "font-size: 15px; color: #ffcc00; font-weight: bold; padding: 6px;"
        "background: #2a2060; border-radius: 8px;"
    );
    m_greetingLabel->setWordWrap(true);
    m_greetingLabel->hide();
    cardLayout->addWidget(m_greetingLabel);

    outer->addWidget(card, 0, Qt::AlignCenter);

    // --- Buttons ---
    auto *playBtn    = new QPushButton("Play ShootingH");
    auto *profileBtn = new QPushButton("My Profile");
    auto *signOutBtn = new QPushButton("Sign Out");

    playBtn->setStyleSheet(
        "QPushButton { font-size: 15px; padding: 12px 30px; }"
    );
    profileBtn->setStyleSheet(
        "QPushButton { background: transparent; border: 1px solid #0f3460; padding: 10px 28px; }"
        "QPushButton:hover { background: #0f3460; }"
    );
    signOutBtn->setStyleSheet(
        "QPushButton { background: transparent; border: 1px solid #555; color: #aaa; padding: 8px 20px; }"
        "QPushButton:hover { background: #e94560; color: white; border-color: #e94560; }"
    );

    connect(playBtn,    &QPushButton::clicked, this, &HomeScreen::playGameClicked);
    connect(profileBtn, &QPushButton::clicked, this, &HomeScreen::profileClicked);
    connect(signOutBtn, &QPushButton::clicked, this, &HomeScreen::signOutClicked);

    auto *btnRow = new QHBoxLayout;
    btnRow->setSpacing(14);
    btnRow->addWidget(playBtn);
    btnRow->addWidget(profileBtn);
    outer->addLayout(btnRow);
    outer->addWidget(signOutBtn, 0, Qt::AlignCenter);
}

void HomeScreen::refresh() {
    User *user = AuthManager::instance().currentUser();
    bool  guest = AuthManager::instance().isGuest();

    if (guest || user == nullptr) {
        m_avatarLabel->setText("?");
        m_nameLabel->setText("Playing as Guest");
        m_dateLabel->setText(QDate::currentDate().toString("dddd, MMMM d, yyyy"));
        m_greetingLabel->hide();
        return;
    }

    // Avatar: try to load picture, fall back to initials
    QPixmap pic(user->profilePicturePath);
    if (!pic.isNull()) {
        m_avatarLabel->setPixmap(
            pic.scaled(100, 100, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)
               .copy(0, 0, 100, 100)
        );
        m_avatarLabel->setStyleSheet(
            "border-radius: 50px; border: 2px solid #e94560;"
        );
    } else {
        QString initials = QString("%1%2")
            .arg(user->firstName.isEmpty() ? "?" : QString(user->firstName[0]).toUpper())
            .arg(user->lastName.isEmpty()  ? ""  : QString(user->lastName[0]).toUpper());
        m_avatarLabel->setText(initials);
        m_avatarLabel->setStyleSheet(
            "border-radius: 50px; background: #0f3460; "
            "color: #e94560; font-size: 32px; font-weight: bold;"
        );
    }

    m_nameLabel->setText(
        QString("Welcome, %1 %2!").arg(user->firstName, user->lastName)
    );
    m_dateLabel->setText(QDate::currentDate().toString("dddd, MMMM d, yyyy"));

    if (user->isBirthdayToday()) {
        m_greetingLabel->setText(
            QString("Happy Birthday, %1! Wishing you a fantastic day!").arg(user->firstName)
        );
        m_greetingLabel->show();
    } else {
        m_greetingLabel->hide();
    }
}
