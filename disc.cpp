#include "disc.h"

#include <QBrush>
#include <QPen>

Disc::Disc(DiscType type, QGraphicsItem *parent)
    : QObject(), QGraphicsEllipseItem(0, 0, 40, 40, parent)
    , m_type(type), m_hit(false)
{
    QColor fill;
    switch (type) {
        case DiscType::Red:
            fill     = QColor(220, 50, 50);
            m_points = 3;
            break;
        case DiscType::Green:
            fill     = QColor(50, 200, 80);
            m_points = 5;
            break;
        case DiscType::Blue:
            fill     = QColor(60, 120, 240);
            m_points = 7;
            break;
    }
    setBrush(QBrush(fill));
    setPen(QPen(Qt::white, 2));
}

DiscType Disc::discType() const { return m_type; }
int      Disc::points()   const { return m_points; }
bool     Disc::isHit()    const { return m_hit; }

void Disc::markHit() {
    m_hit = true;
    setBrush(QBrush(QColor(130, 130, 130)));
    setPen(QPen(QColor(80, 80, 80), 2));
}
