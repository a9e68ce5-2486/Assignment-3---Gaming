#include "loginscreen.h"
#include "styles.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QFrame>

LoginScreen::LoginScreen(QWidget *parent) : QWidget(parent) {
    setStyleSheet(appStyleSheet());

    auto *outer = new QVBoxLayout(this);
    outer->setAlignment(Qt::AlignCenter);

    // Title
    auto *title = new QLabel("Gaming Framework");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #e94560; font-size: 30px; font-weight: bold; margin-bottom: 10px;");
    outer->addWidget(title);

    auto *subtitle = new QLabel("Sign in to track your scores");
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #888; font-size: 13px; margin-bottom: 20px;");
    outer->addWidget(subtitle);

    // Card
    auto *card = new QFrame;
    card->setFixedWidth(380);
    card->setStyleSheet("background: #16213e; border-radius: 12px; padding: 10px;");
    auto *form = new QVBoxLayout(card);
    form->setSpacing(10);
    form->setContentsMargins(24, 24, 24, 24);

    form->addWidget(new QLabel("Username"));
    m_usernameEdit = new QLineEdit;
    m_usernameEdit->setPlaceholderText("Enter your username");
    form->addWidget(m_usernameEdit);

    form->addWidget(new QLabel("Password"));
    m_passwordEdit = new QLineEdit;
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText("Enter your password");
    form->addWidget(m_passwordEdit);

    m_errorLabel = new QLabel;
    m_errorLabel->setStyleSheet("color: #e94560; font-size: 12px;");
    m_errorLabel->setAlignment(Qt::AlignCenter);
    m_errorLabel->setWordWrap(true);
    m_errorLabel->hide();
    form->addWidget(m_errorLabel);

    auto *signInBtn = new QPushButton("Sign In");
    connect(signInBtn, &QPushButton::clicked, this, &LoginScreen::onSignIn);
    form->addWidget(signInBtn);

    auto *sep = new QLabel("── or ──");
    sep->setAlignment(Qt::AlignCenter);
    sep->setStyleSheet("color: #555; font-size: 12px;");
    form->addWidget(sep);

    auto *signUpBtn = new QPushButton("Create Account");
    signUpBtn->setStyleSheet(
        "QPushButton { background: transparent; border: 1px solid #0f3460; }"
        "QPushButton:hover { background: #0f3460; }"
    );
    connect(signUpBtn, &QPushButton::clicked, this, &LoginScreen::signUpClicked);
    form->addWidget(signUpBtn);

    auto *guestBtn = new QPushButton("Play as Guest");
    guestBtn->setStyleSheet(
        "QPushButton { background: transparent; border: 1px solid #555; color: #aaa; }"
        "QPushButton:hover { background: #333; }"
    );
    connect(guestBtn, &QPushButton::clicked, this, &LoginScreen::guestClicked);
    form->addWidget(guestBtn);

    outer->addWidget(card, 0, Qt::AlignCenter);
}

void LoginScreen::onSignIn() {
    m_errorLabel->hide();
    emit signInClicked(m_usernameEdit->text().trimmed(), m_passwordEdit->text());
}

void LoginScreen::clearFields() {
    m_usernameEdit->clear();
    m_passwordEdit->clear();
    m_errorLabel->hide();
}

void LoginScreen::showError(const QString &message) {
    m_errorLabel->setText(message);
    m_errorLabel->show();
}
