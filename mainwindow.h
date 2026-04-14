#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGraphicsView>

class LoginScreen;
class SignUpScreen;
class HomeScreen;
class ProfileScreen;
class GameScene;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void showLogin();
    void showSignUp();
    void showHome();
    void showProfile();
    void showGame();
    void onGameOver(int score);

private:
    QStackedWidget *m_stack;
    LoginScreen    *m_loginScreen;
    SignUpScreen   *m_signUpScreen;
    HomeScreen     *m_homeScreen;
    ProfileScreen  *m_profileScreen;
    QGraphicsView  *m_gameView;
    GameScene      *m_gameScene;
};

#endif // MAINWINDOW_H
