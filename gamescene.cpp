#include "gamescene.h"
#include "disc.h"

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <algorithm>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_hudBg(nullptr)
    , m_scoreText(nullptr), m_timeText(nullptr), m_levelText(nullptr)
    , m_livesText(nullptr)
    , m_redText(nullptr), m_greenText(nullptr), m_blueText(nullptr)
    , m_overlayBg(nullptr), m_overlayText(nullptr)
    , m_confirmBg(nullptr), m_confirmText(nullptr), m_confirmingRestart(false)
    , m_score(0), m_redHits(0), m_greenHits(0), m_blueHits(0)
    , m_timeLeft(GAME_DURATION), m_level(1), m_lives(MAX_LIVES), m_running(false)
{
    setSceneRect(0, 0, SCENE_W, SCENE_H);

    m_spawnTimer  = new QTimer(this);
    m_scrollTimer = new QTimer(this);
    m_gameTimer   = new QTimer(this);

    connect(m_spawnTimer,  &QTimer::timeout, this, &GameScene::spawnDisc);
    connect(m_scrollTimer, &QTimer::timeout, this, &GameScene::scrollDiscs);
    connect(m_gameTimer,   &QTimer::timeout, this, &GameScene::tickTimer);

    setupHUD();
    showStartPrompt();
}

// ── HUD ───────────────────────────────────────────────────────────────────────

void GameScene::setupHUD() {
    m_hudBg = new QGraphicsRectItem(0, 0, SCENE_W, HUD_H);
    m_hudBg->setBrush(QBrush(QColor(20, 20, 50)));
    m_hudBg->setPen(QPen(QColor(60, 60, 120), 1));
    m_hudBg->setZValue(10);
    addItem(m_hudBg);

    auto makeText = [this](const QString &str, qreal x, qreal y,
                            QColor color, int size) -> QGraphicsTextItem * {
        QGraphicsTextItem *t = new QGraphicsTextItem(str);
        t->setDefaultTextColor(color);
        t->setFont(QFont("Arial", size, QFont::Bold));
        t->setPos(x, y);
        t->setZValue(11);
        addItem(t);
        return t;
    };

    m_scoreText  = makeText("Score: 0",       10,  12, Qt::white,           14);
    m_timeText   = makeText("Time: 60",       170,  12, Qt::cyan,            14);
    m_levelText  = makeText("Level: 1",       330,  12, QColor(255, 200, 0), 14);
    m_livesText  = makeText("❤ ❤ ❤",         480,  12, QColor(233, 69, 96), 14);
    m_redText    = makeText("Red: 0 [3pt]",   620,   5, QColor(220, 80, 80), 10);
    m_greenText  = makeText("Green: 0 [5pt]", 620,  28, QColor(80, 200, 80), 10);
    m_blueText   = makeText("Blue: 0 [7pt]",  770,   5, QColor(100,150,255), 10);
}

void GameScene::updateHUD() {
    m_scoreText->setPlainText(QString("Score: %1").arg(m_score));
    m_timeText->setPlainText(QString("Time: %1").arg(m_timeLeft));
    m_levelText->setPlainText(QString("Level: %1").arg(m_level));
    m_redText->setPlainText(QString("Red: %1 [3pt]").arg(m_redHits));
    m_greenText->setPlainText(QString("Green: %1 [5pt]").arg(m_greenHits));
    m_blueText->setPlainText(QString("Blue: %1 [7pt]").arg(m_blueHits));

    // 用愛心符號顯示剩餘生命
    QString hearts;
    for (int i = 0; i < MAX_LIVES; i++)
        hearts += (i < m_lives) ? "❤ " : "♡ ";
    m_livesText->setPlainText(hearts.trimmed());

    // 時間快到時變紅色警示
    m_timeText->setDefaultTextColor(m_timeLeft <= 10 ? QColor(233, 69, 96) : Qt::cyan);
}

// ── Overlay helpers ───────────────────────────────────────────────────────────

void GameScene::showStartPrompt() {
    removeOverlay();

    m_overlayBg = new QGraphicsRectItem(80, 160, 740, 240);
    m_overlayBg->setBrush(QBrush(QColor(0, 0, 0, 210)));
    m_overlayBg->setPen(QPen(QColor(255, 200, 0), 3));
    m_overlayBg->setZValue(20);
    addItem(m_overlayBg);

    m_overlayText = new QGraphicsTextItem(
        "ShootingH\n\n"
        "Shoot the scrolling discs!\n"
        "Red = 3pts  |  Green = 5pts  |  Blue = 7pts\n\n"
        "❤ 3 Lives  —  miss a disc and lose one life!\n\n"
        "Press F1 or R to Start"
    );
    m_overlayText->setDefaultTextColor(Qt::white);
    m_overlayText->setFont(QFont("Arial", 15, QFont::Bold));
    m_overlayText->setTextWidth(720);
    m_overlayText->setPos(90, 165);
    m_overlayText->setZValue(21);
    addItem(m_overlayText);
}

void GameScene::removeOverlay() {
    if (m_overlayBg) {
        removeItem(m_overlayBg);
        delete m_overlayBg;
        m_overlayBg = nullptr;
    }
    if (m_overlayText) {
        removeItem(m_overlayText);
        delete m_overlayText;
        m_overlayText = nullptr;
    }
}

// ── Restart confirmation ──────────────────────────────────────────────────────

void GameScene::showRestartConfirm() {
    // 暫停遊戲
    m_spawnTimer->stop();
    m_scrollTimer->stop();
    m_gameTimer->stop();
    m_confirmingRestart = true;

    m_confirmBg = new QGraphicsRectItem(250, 210, 400, 140);
    m_confirmBg->setBrush(QBrush(QColor(15, 15, 40, 230)));
    m_confirmBg->setPen(QPen(QColor(255, 200, 0), 2));
    m_confirmBg->setZValue(30);
    addItem(m_confirmBg);

    m_confirmText = new QGraphicsTextItem(
        "Restart game?\n\n"
        "  Y  — Yes, restart\n"
        "  N  — No, keep playing"
    );
    m_confirmText->setDefaultTextColor(Qt::white);
    m_confirmText->setFont(QFont("Arial", 14, QFont::Bold));
    m_confirmText->setTextWidth(380);
    m_confirmText->setPos(260, 218);
    m_confirmText->setZValue(31);
    addItem(m_confirmText);
}

void GameScene::dismissRestartConfirm() {
    if (m_confirmBg) {
        removeItem(m_confirmBg);
        delete m_confirmBg;
        m_confirmBg = nullptr;
    }
    if (m_confirmText) {
        removeItem(m_confirmText);
        delete m_confirmText;
        m_confirmText = nullptr;
    }
    m_confirmingRestart = false;

    // 繼續遊戲
    m_spawnTimer->start();
    m_scrollTimer->start();
    m_gameTimer->start();
}

// ── Game lifecycle ────────────────────────────────────────────────────────────

void GameScene::startGame() {
    removeOverlay();

    m_score     = 0;
    m_redHits   = 0;
    m_greenHits = 0;
    m_blueHits  = 0;
    m_timeLeft  = GAME_DURATION;
    m_level     = 1;
    m_lives     = MAX_LIVES;
    m_running   = true;

    updateHUD();

    m_spawnTimer->start(1200);
    m_scrollTimer->start(30);
    m_gameTimer->start(1000);
}

void GameScene::restartGame() {
    m_spawnTimer->stop();
    m_scrollTimer->stop();
    m_gameTimer->stop();
    clearDiscs();
    startGame();
}

int GameScene::finalScore() const { return m_score; }
int GameScene::finalLevel() const { return m_level; }

void GameScene::clearDiscs() {
    const QList<QGraphicsItem *> allItems = items();
    for (QGraphicsItem *item : allItems) {
        Disc *disc = dynamic_cast<Disc *>(item);
        if (disc != nullptr) {
            removeItem(disc);
            delete disc;
        }
    }
}

// ── Timers ────────────────────────────────────────────────────────────────────

void GameScene::spawnDisc() {
    if (!m_running) return;

    int count = (m_level >= 3) ? 2 : 1;
    for (int i = 0; i < count; i++) {
        int typeIdx   = static_cast<int>(QRandomGenerator::global()->bounded(3));
        DiscType type = static_cast<DiscType>(typeIdx);

        qreal y = HUD_H + 20 + QRandomGenerator::global()->bounded(SCENE_H - HUD_H - 60);
        qreal x = SCENE_W + 10 + i * 70;

        Disc *disc = new Disc(type);
        disc->setPos(x, y);
        addItem(disc);
    }

    int interval = std::max(400, 1200 - (m_level - 1) * 150);
    m_spawnTimer->setInterval(interval);
}

void GameScene::scrollDiscs() {
    if (!m_running) return;

    int speed = 2 + m_level;

    QList<QGraphicsItem *> toRemove;
    const QList<QGraphicsItem *> allItems = items();
    for (QGraphicsItem *item : allItems) {
        Disc *disc = dynamic_cast<Disc *>(item);
        if (disc != nullptr && !disc->isHit()) {
            disc->moveBy(-speed, 0);
            if (disc->x() + 50 < 0)
                toRemove.append(disc);
        }
    }

    for (QGraphicsItem *item : toRemove) {
        removeItem(item);
        delete item;

        // 每個飛碟漏掉就扣一條命
        m_lives--;
        updateHUD();

        // 顯示 Miss 提示
        QGraphicsTextItem *missPopup = new QGraphicsTextItem("-1 ❤");
        missPopup->setDefaultTextColor(QColor(233, 69, 96));
        missPopup->setFont(QFont("Arial", 14, QFont::Bold));
        // 顯示在畫面左側
        qreal px = 20 + QRandomGenerator::global()->bounded(100);
        qreal py = HUD_H + 20 + QRandomGenerator::global()->bounded(200);
        missPopup->setPos(px, py);
        missPopup->setZValue(15);
        addItem(missPopup);

        QTimer::singleShot(700, this, [this, missPopup]() {
            removeItem(missPopup);
            delete missPopup;
        });

        if (m_lives <= 0) {
            endGame();
            return;   // 已 endGame，不繼續處理其他飛碟
        }
    }
}

void GameScene::tickTimer() {
    if (!m_running) return;
    m_timeLeft--;
    updateHUD();
    if (m_timeLeft <= 0)
        endGame();
}

void GameScene::endGame() {
    m_running = false;
    m_spawnTimer->stop();
    m_scrollTimer->stop();
    m_gameTimer->stop();

    removeOverlay();

    // 判斷結束原因
    QString reason = (m_lives <= 0)
        ? "No lives left!"
        : "Time's up!";

    m_overlayBg = new QGraphicsRectItem(70, 130, 760, 300);
    m_overlayBg->setBrush(QBrush(QColor(0, 0, 0, 215)));
    m_overlayBg->setPen(QPen(QColor(233, 69, 96), 3));
    m_overlayBg->setZValue(20);
    addItem(m_overlayBg);

    QString msg = QString(
        "Game Over  —  %1\n\n"
        "Final Score : %2\n"
        "Lives Left  : %3\n"
        "Red: %4   Green: %5   Blue: %6\n\n"
        "Press R to Play Again\n"
        "Press Esc to Return to Menu"
    ).arg(reason)
     .arg(m_score)
     .arg(m_lives)
     .arg(m_redHits).arg(m_greenHits).arg(m_blueHits);

    m_overlayText = new QGraphicsTextItem(msg);
    m_overlayText->setDefaultTextColor(Qt::white);
    m_overlayText->setFont(QFont("Arial", 17, QFont::Bold));
    m_overlayText->setTextWidth(740);
    m_overlayText->setPos(80, 140);
    m_overlayText->setZValue(21);
    addItem(m_overlayText);

    emit gameOver(m_score);
}

// ── Input ─────────────────────────────────────────────────────────────────────

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!m_running) return;

    QPointF pos = event->scenePos();
    if (pos.y() < HUD_H) return;

    const QList<QGraphicsItem *> clicked = items(pos);
    for (QGraphicsItem *item : clicked) {
        Disc *disc = dynamic_cast<Disc *>(item);
        if (disc != nullptr && !disc->isHit()) {
            disc->markHit();

            int pts = disc->points();
            m_score += pts;

            switch (disc->discType()) {
                case DiscType::Red:   m_redHits++;   break;
                case DiscType::Green: m_greenHits++; break;
                case DiscType::Blue:  m_blueHits++;  break;
            }

            // 浮動得分提示
            QGraphicsTextItem *popup = new QGraphicsTextItem(
                QString("+%1").arg(pts)
            );
            popup->setDefaultTextColor(QColor(255, 230, 0));
            popup->setFont(QFont("Arial", 16, QFont::Bold));
            popup->setPos(disc->pos() + QPointF(4, -22));
            popup->setZValue(15);
            addItem(popup);

            QTimer::singleShot(600, this, [this, popup]() {
                removeItem(popup);
                delete popup;
            });

            // 飛碟變灰後移除
            QTimer::singleShot(450, this, [this, disc]() {
                removeItem(disc);
                delete disc;
            });

            // 每 20 分升一級，最高 5 級
            m_level = std::min(5, 1 + m_score / 20);

            updateHUD();
            break;
        }
    }
}

void GameScene::keyPressEvent(QKeyEvent *event) {

    // ── 確認重啟對話框中 ──
    if (m_confirmingRestart) {
        if (event->key() == Qt::Key_Y) {
            dismissRestartConfirm();
            restartGame();
        } else if (event->key() == Qt::Key_N || event->key() == Qt::Key_Escape) {
            dismissRestartConfirm();   // 取消，繼續遊戲
        }
        event->accept();
        return;
    }

    // ── 遊戲進行中按 R / F1 → 先問確認 ──
    if ((event->key() == Qt::Key_R || event->key() == Qt::Key_F1) && m_running) {
        showRestartConfirm();
        event->accept();
        return;
    }

    // ── 遊戲結束後按 R / F1 → 直接重啟（沒東西可以失去）──
    if ((event->key() == Qt::Key_R || event->key() == Qt::Key_F1) && !m_running) {
        restartGame();
        event->accept();
        return;
    }

    // ── 遊戲結束後按 Esc → 返回主選單 ──
    if (event->key() == Qt::Key_Escape && !m_running) {
        emit returnToMenu();
        event->accept();
        return;
    }

    QGraphicsScene::keyPressEvent(event);
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter, rect);

    painter->fillRect(rect, QColor(10, 10, 30));

    // 遊戲區域格線
    painter->setPen(QPen(QColor(22, 22, 55), 1));
    const int gs = 60;
    for (int x = 0; x < SCENE_W; x += gs)
        painter->drawLine(x, HUD_H, x, SCENE_H);
    for (int y = HUD_H; y < SCENE_H; y += gs)
        painter->drawLine(0, y, SCENE_W, y);
}
