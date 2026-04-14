#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPainter>

class Disc;

class GameScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

    void startGame();
    void restartGame();
    int  finalScore() const;
    int  finalLevel() const;

signals:
    void gameOver(int score);
    void returnToMenu();

public slots:
    void spawnDisc();
    void scrollDiscs();
    void tickTimer();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    void setupHUD();
    void updateHUD();
    void showStartPrompt();
    void showRestartConfirm();
    void dismissRestartConfirm();
    void endGame();
    void clearDiscs();
    void removeOverlay();

    static const int SCENE_W       = 900;
    static const int SCENE_H       = 560;
    static const int HUD_H         = 60;
    static const int GAME_DURATION = 60;

    QTimer *m_spawnTimer;
    QTimer *m_scrollTimer;
    QTimer *m_gameTimer;

    static const int MAX_LIVES = 3;

    QGraphicsRectItem *m_hudBg;
    QGraphicsTextItem *m_scoreText;
    QGraphicsTextItem *m_timeText;
    QGraphicsTextItem *m_levelText;
    QGraphicsTextItem *m_livesText;
    QGraphicsTextItem *m_redText;
    QGraphicsTextItem *m_greenText;
    QGraphicsTextItem *m_blueText;

    QGraphicsRectItem *m_overlayBg;
    QGraphicsTextItem *m_overlayText;

    QGraphicsRectItem *m_confirmBg;
    QGraphicsTextItem *m_confirmText;
    bool               m_confirmingRestart;

    int  m_score;
    int  m_redHits;
    int  m_greenHits;
    int  m_blueHits;
    int  m_timeLeft;
    int  m_level;
    int  m_lives;
    bool m_running;
};

#endif // GAMESCENE_H
