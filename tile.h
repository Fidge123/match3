#pragma once

#include <QVector2D>
#include <QPointF>
#include <QObject>
#include <QGraphicsPixmapItem>

class Grid;
class QPropertyAnimation;

enum class Color
{
    BLUE = 0,
    GREEN = 1,
    PURPLE = 2,
    RED = 3,
    YELLOW = 4,
    BLUE_HL = 5,
    GREEN_HL = 6,
    PURPLE_HL = 7,
    RED_HL = 8,
    YELLOW_HL = 9
};

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    Tile(Color color, QVector2D position, Grid * grid = nullptr);
    ~Tile();

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    Color color() const;
    void setColor(Color color);
    bool isSelected();
    void setIsSelected(bool selected);
    QVector2D position() const;
    void setPosition(QVector2D position);

protected:
    Grid * m_grid;

    QVector2D m_position;
    QPropertyAnimation * m_animation;
    Color m_color;
    bool m_isSelected;

    QPointF m_pressedPos;
};
