#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QLabel>

class HomeScreen : public QWidget {
    Q_OBJECT
public:
    explicit HomeScreen(QWidget *parent = nullptr);

    void refresh();  // call after login to update displayed info

signals:
    void playGameClicked();
    void profileClicked();
    void signOutClicked();

private:
    QLabel *m_avatarLabel;
    QLabel *m_nameLabel;
    QLabel *m_dateLabel;
    QLabel *m_greetingLabel;
};

#endif // HOMESCREEN_H
