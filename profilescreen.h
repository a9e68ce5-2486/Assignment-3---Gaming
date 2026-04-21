#ifndef PROFILESCREEN_H
#define PROFILESCREEN_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>

class ProfileScreen : public QWidget {
    Q_OBJECT
public:
    explicit ProfileScreen(QWidget *parent = nullptr);

    void refresh();  // reload data for current user

signals:
    void backClicked();

private:
    QLabel        *m_avatarLabel;
    QLabel        *m_infoLabel;
    QTableWidget  *m_scoreTable;
};

#endif // PROFILESCREEN_H
