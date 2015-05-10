#include "tile.h"

#include <QGraphicsPixmapItem>
#include <QVector2D>

Tile::Tile(Color color, QVector2D position)
    : m_color(color)
{
    QGraphicsItem::setAcceptTouchEvents(true);
    setPosition(position);

    switch (color)
    {
    case Color::BLUE:
        setPixmap(QPixmap(":/assets/Blue.png"));
        break;
    case Color::GREEN:
        setPixmap(QPixmap(":/assets/Green.png"));
        break;
    case Color::PURPLE:
        setPixmap(QPixmap(":/assets/Purple.png"));
        break;
    case Color::RED:
        setPixmap(QPixmap(":/assets/Red.png"));
        break;
    case Color::YELLOW:
        setPixmap(QPixmap(":/assets/Yellow.png"));
        break;
    default:
        break;
    }
}

Tile::~Tile()
{

}

Color Tile::color() const
{
    return m_color;
}

void Tile::setPosition(QVector2D position)
{
    m_position = position;
    setPos(position.x() * 42 + 330, position.y() * 42 + 105);
}

QVector2D Tile::position() const
{
    return m_position;
}
