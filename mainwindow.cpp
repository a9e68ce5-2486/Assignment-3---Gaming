#include "mainwindow.h"
#include "styles.h"
#include "authmanager.h"
#include "userdatabase.h"
#include "loginscreen.h"
#include "signupscreen.h"
#include "homescreen.h"
#include "profilescreen.h"
#include "gamescene.h"
#include "user.h"

#include <QApplication>
#include <QMessageBox>

// Stack widget page indices
static const int PAGE_LOGIN   = 0;
static const int PAGE_SIGNUP  = 1;
static const int PAGE_HOME    = 2;
static const int PAGE_PROFILE = 3;
static const int PAGE_GAME    = 4;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Gaming Framework");
    setMinimumSize(920, 620);
    setStyleSheet(appStyleSheet());

    // Load user data from disk
    UserDatabase::instance().load("users.json");

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    // --- Screens ---
    m_loginScreen   = new LoginScreen(this);
    m_signUpScreen  = new SignUpScreen(this);
    m_homeScreen    = new HomeScreen(this);
    m_profileScreen = new ProfileScreen(this);

    m_gameScene = new GameScene(this);
    m_gameView  = new QGraphicsView(m_gameScene, this);
    m_gameView->setFixedSize(902, 562);
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setRenderHint(QPainter::Antialiasing);
    m_gameView->setFocusPolicy(Qt::StrongFocus);

    m_stack->addWidget(m_loginScreen);    // 0
    m_stack->addWidget(m_signUpScreen);   // 1
    m_stack->addWidget(m_homeScreen);     // 2
    m_stack->addWidget(m_profileScreen);  // 3
    m_stack->addWidget(m_gameView);       // 4

    // --- Connect LoginScreen ---
    connect(m_loginScreen, &LoginScreen::signInClicked,
            this, [this](const QString &username, const QString &password) {
        QString err;
        User *user = AuthManager::instance().signIn(username, password, err);
        if (user == nullptr) {
            m_loginScreen->showError(err);
        } else {
            m_loginScreen->clearFields();
            showHome();
        }
    });
    connect(m_loginScreen, &LoginScreen::signUpClicked,  this, &MainWindow::showSignUp);
    connect(m_loginScreen, &LoginScreen::guestClicked,   this, [this]() {
        AuthManager::instance().playAsGuest();
        showHome();
    });

    // --- Connect SignUpScreen ---
    connect(m_signUpScreen, &SignUpScreen::signUpSubmitted,
            this, [this](const QString &firstName, const QString &lastName,
                         const QDate &dob, const QString &gender,
                         const QString &profilePic, const QString &username,
                         const QString &password) {
        // Validate fields
        if (firstName.isEmpty() || lastName.isEmpty()) {
            m_signUpScreen->showError("First and last name are required.");
            return;
        }
        QString pwErr;
        if (!AuthManager::validatePassword(password, pwErr)) {
            m_signUpScreen->showError(pwErr);
            return;
        }

        // Get confirm password check via the signal arguments (we pass both)
        // Note: confirm password comparison is done in signupscreen before emit
        // so we trust it here — but we emit both separately for safety:
        // (confirm check is in onSubmit() in SignUpScreen — see below)

        User newUser;
        newUser.firstName          = firstName;
        newUser.lastName           = lastName;
        newUser.dateOfBirth        = dob;
        newUser.gender             = gender;
        newUser.profilePicturePath = profilePic;
        newUser.username           = username;
        newUser.passwordHash       = User::hashPassword(password);

        QString err;
        if (!AuthManager::instance().signUp(newUser, err)) {
            m_signUpScreen->showError(err);
            return;
        }

        m_signUpScreen->clearFields();
        // Auto sign-in after registration
        AuthManager::instance().signIn(username, password, err);
        showHome();
    });
    connect(m_signUpScreen, &SignUpScreen::backClicked, this, &MainWindow::showLogin);

    // --- Connect HomeScreen ---
    connect(m_homeScreen, &HomeScreen::playGameClicked,  this, &MainWindow::showGame);
    connect(m_homeScreen, &HomeScreen::profileClicked,   this, &MainWindow::showProfile);
    connect(m_homeScreen, &HomeScreen::signOutClicked,   this, [this]() {
        AuthManager::instance().signOut();
        showLogin();
    });

    // --- Connect ProfileScreen ---
    connect(m_profileScreen, &ProfileScreen::backClicked, this, &MainWindow::showHome);

    // --- Connect GameScene ---
    connect(m_gameScene, &GameScene::gameOver,      this, &MainWindow::onGameOver);
    connect(m_gameScene, &GameScene::returnToMenu,  this, &MainWindow::showHome);

    showLogin();
}

void MainWindow::showLogin() {
    m_loginScreen->clearFields();
    m_stack->setCurrentIndex(PAGE_LOGIN);
    setMinimumSize(920, 620);
    resize(920, 620);
}

void MainWindow::showSignUp() {
    m_stack->setCurrentIndex(PAGE_SIGNUP);
}

void MainWindow::showHome() {
    m_homeScreen->refresh();
    m_stack->setCurrentIndex(PAGE_HOME);
    setMinimumSize(920, 620);
    resize(920, 620);
}

void MainWindow::showProfile() {
    m_profileScreen->refresh();
    m_stack->setCurrentIndex(PAGE_PROFILE);
}

void MainWindow::showGame() {
    m_gameScene->restartGame();
    m_stack->setCurrentIndex(PAGE_GAME);
    setFixedSize(920, 580);
    m_gameView->setFocus();
}

void MainWindow::onGameOver(int score) {
    User *user = AuthManager::instance().currentUser();
    if (user != nullptr) {
        user->addScore("ShootingH", score);
        UserDatabase::instance().updateUser(*user);
    }
    // Game-over overlay inside the scene handles next steps (R / Esc)
}
