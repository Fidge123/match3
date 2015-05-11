#pragma once

#include <QVector2D>
#include <QPointF>
#include <QGraphicsPixmapItem>

class QGraphicsItem;

class Grid;

enum class Color
{
    BLUE = 0,
    GREEN = 1,
    PURPLE = 2,
    RED = 3,
    YELLOW = 4
};

class Tile : public QGraphicsPixmapItem
{

public:
    Tile(Color color, QVector2D position, Grid * grid = nullptr);
    ~Tile();

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    Color color() const;
    void setPosition(QVector2D position);
    QVector2D position() const;

protected:
    Color m_color;
    Grid * m_grid;
    QPointF m_pressedPos;
    QVector2D m_position;
};
