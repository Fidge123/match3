#pragma once

#include <QVector2D>
#include <QGraphicsPixmapItem>

class QGraphicsItem;

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
    Tile(Color color, QVector2D position);
    ~Tile();

    bool swapWith(Tile tile);
    Color color();
    QVector2D position();

protected:
    Color m_color;
    QVector2D m_position;
};
