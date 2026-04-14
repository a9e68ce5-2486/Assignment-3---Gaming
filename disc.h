#ifndef DISC_H
#define DISC_H

#include <QObject>
#include <QGraphicsEllipseItem>

enum class DiscType { Red, Green, Blue };

class Disc : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    explicit Disc(DiscType type, QGraphicsItem *parent = nullptr);

    DiscType discType() const;
    int      points()   const;
    bool     isHit()    const;
    void     markHit();

private:
    DiscType m_type;
    int      m_points;
    bool     m_hit;
};

#endif // DISC_H
