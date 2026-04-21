#include "signupscreen.h"
#include "styles.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QFileDialog>
#include <QFrame>
#include <QFont>

SignUpScreen::SignUpScreen(QWidget *parent) : QWidget(parent) {
    setStyleSheet(appStyleSheet());

    auto *outer = new QVBoxLayout(this);
    outer->setAlignment(Qt::AlignCenter);

    // Title
    auto *title = new QLabel("Create Account");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #e94560; font-size: 26px; font-weight: bold; margin-bottom: 6px;");
    outer->addWidget(title);

    // Scroll area for the form
    auto *scroll = new QScrollArea;
    scroll->setFixedWidth(460);
    scroll->setMaximumHeight(520);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    auto *card = new QFrame;
    card->setStyleSheet("background: #16213e; border-radius: 12px;");
    auto *form = new QGridLayout(card);
    form->setSpacing(8);
    form->setContentsMargins(24, 20, 24, 20);

    int row = 0;
    auto addRow = [&](const QString &label, QWidget *widget) {
        form->addWidget(new QLabel(label), row, 0);
        form->addWidget(widget,            row, 1);
        row++;
    };

    m_firstNameEdit = new QLineEdit;
    m_firstNameEdit->setPlaceholderText("First name");
    addRow("First Name *", m_firstNameEdit);

    m_lastNameEdit = new QLineEdit;
    m_lastNameEdit->setPlaceholderText("Last name");
    addRow("Last Name *", m_lastNameEdit);

    m_dobEdit = new QDateEdit;
    m_dobEdit->setDisplayFormat("yyyy-MM-dd");
    m_dobEdit->setDate(QDate(2000, 1, 1));
    m_dobEdit->setCalendarPopup(true);
    addRow("Date of Birth *", m_dobEdit);

    m_genderCombo = new QComboBox;
    m_genderCombo->addItems({"Prefer not to say", "Male", "Female", "Non-binary", "Other"});
    addRow("Gender (optional)", m_genderCombo);

    // Profile picture row with browse button
    auto *picWidget = new QWidget;
    auto *picLayout = new QHBoxLayout(picWidget);
    picLayout->setContentsMargins(0, 0, 0, 0);
    picLayout->setSpacing(6);
    m_profilePicEdit = new QLineEdit;
    m_profilePicEdit->setPlaceholderText("(optional) image path");
    auto *browseBtn = new QPushButton("Browse");
    browseBtn->setFixedWidth(72);
    browseBtn->setStyleSheet(
        "QPushButton { padding: 6px 8px; font-size: 12px; }"
    );
    connect(browseBtn, &QPushButton::clicked, this, &SignUpScreen::onBrowsePicture);
    picLayout->addWidget(m_profilePicEdit);
    picLayout->addWidget(browseBtn);
    form->addWidget(new QLabel("Profile Picture"), row, 0);
    form->addWidget(picWidget,                      row, 1);
    row++;

    m_usernameEdit = new QLineEdit;
    m_usernameEdit->setPlaceholderText("At least 3 chars, letters/numbers/_");
    addRow("Username *", m_usernameEdit);

    m_passwordEdit = new QLineEdit;
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText("Min 8 chars, upper, lower, digit");
    addRow("Password *", m_passwordEdit);

    m_confirmPasswordEdit = new QLineEdit;
    m_confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    m_confirmPasswordEdit->setPlaceholderText("Repeat password");
    addRow("Confirm Password *", m_confirmPasswordEdit);

    m_errorLabel = new QLabel;
    m_errorLabel->setStyleSheet("color: #e94560; font-size: 12px;");
    m_errorLabel->setAlignment(Qt::AlignCenter);
    m_errorLabel->setWordWrap(true);
    m_errorLabel->hide();
    form->addWidget(m_errorLabel, row++, 0, 1, 2);

    auto *btnRow = new QHBoxLayout;
    auto *backBtn   = new QPushButton("Back");
    auto *submitBtn = new QPushButton("Create Account");
    backBtn->setStyleSheet(
        "QPushButton { background: transparent; border: 1px solid #555; color: #aaa; }"
        "QPushButton:hover { background: #333; }"
    );
    connect(backBtn,   &QPushButton::clicked, this, &SignUpScreen::backClicked);
    connect(submitBtn, &QPushButton::clicked, this, &SignUpScreen::onSubmit);
    btnRow->addWidget(backBtn);
    btnRow->addWidget(submitBtn);
    form->addLayout(btnRow, row++, 0, 1, 2);

    scroll->setWidget(card);
    outer->addWidget(scroll, 0, Qt::AlignCenter);
}

void SignUpScreen::onBrowsePicture() {
    QString path = QFileDialog::getOpenFileName(
        this, "Select Profile Picture", QString(),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
    );
    if (!path.isEmpty())
        m_profilePicEdit->setText(path);
}

void SignUpScreen::onSubmit() {
    m_errorLabel->hide();

    if (m_passwordEdit->text() != m_confirmPasswordEdit->text()) {
        showError("Passwords do not match.");
        return;
    }

    emit signUpSubmitted(
        m_firstNameEdit->text().trimmed(),
        m_lastNameEdit->text().trimmed(),
        m_dobEdit->date(),
        m_genderCombo->currentText(),
        m_profilePicEdit->text().trimmed(),
        m_usernameEdit->text().trimmed(),
        m_passwordEdit->text()
    );
}

void SignUpScreen::clearFields() {
    m_firstNameEdit->clear();
    m_lastNameEdit->clear();
    m_dobEdit->setDate(QDate(2000, 1, 1));
    m_genderCombo->setCurrentIndex(0);
    m_profilePicEdit->clear();
    m_usernameEdit->clear();
    m_passwordEdit->clear();
    m_confirmPasswordEdit->clear();
    m_errorLabel->hide();
}

void SignUpScreen::showError(const QString &message) {
    m_errorLabel->setText(message);
    m_errorLabel->show();
}
