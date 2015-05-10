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

    Color color() const;

    void setPosition(QVector2D position);
    QVector2D position() const;

protected:
    Color m_color;
    QVector2D m_position;
};
