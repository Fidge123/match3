#include "tile.h"

#include <cmath>

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QTouchEvent>
#include <QVector2D>
#include <QDebug>

#include <grid.h>

Tile::Tile(Color color, QVector2D position, Grid * grid)
    : m_grid(grid)
    , m_isSelected(false)
{
    QGraphicsItem::setAcceptTouchEvents(true);
    setPosition(position);
    setColor(color);
}

Tile::~Tile()
{

}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    m_pressedPos = event->pos();
}

void Tile::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    if (0 < event->pos().x() &&
        event->pos().x() < 32 &&
        0 < event->pos().y() &&
        event->pos().y() < 32)
    {
        m_grid->setSelectedTile(this);
    }
    else
    {
        if (m_pressedPos.x() - event->pos().x() < 0 &&
            abs(m_pressedPos.x() - event->pos().x()) > abs(m_pressedPos.y() - event->pos().y()))
        {
            m_grid->swapRight(this);
        }
        else if (m_pressedPos.x() - event->pos().x() > 32 &&
            std::abs(m_pressedPos.x() - event->pos().x()) > std::abs(m_pressedPos.y() - event->pos().y()))
        {
            m_grid->swapLeft(this);
        }
        else if (m_pressedPos.y() - event->pos().y() < 0 &&
            std::abs(m_pressedPos.x() - event->pos().x()) < std::abs(m_pressedPos.y() - event->pos().y()))
        {
            m_grid->swapDown(this);
        }
        else if (m_pressedPos.y() - event->pos().y() > 32 &&
            std::abs(m_pressedPos.x() - event->pos().x()) < std::abs(m_pressedPos.y() - event->pos().y()))
        {
            m_grid->swapUp(this);
        }
    }
}

Color Tile::color() const
{
    return m_color;
}

void Tile::setColor(Color color)
{
    m_color = color;

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
    case Color::BLUE_HL:
        setPixmap(QPixmap(":/assets/BlueHL.png"));
        break;
    case Color::GREEN_HL:
        setPixmap(QPixmap(":/assets/GreenHL.png"));
        break;
    case Color::PURPLE_HL:
        setPixmap(QPixmap(":/assets/PurpleHL.png"));
        break;
    case Color::RED_HL:
        setPixmap(QPixmap(":/assets/RedHL.png"));
        break;
    case Color::YELLOW_HL:
        setPixmap(QPixmap(":/assets/YellowHL.png"));
        break;
    default:
        break;
    }
}

bool Tile::isSelected()
{
    return m_isSelected;
}

void Tile::setIsSelected(bool selected)
{
    if (m_isSelected != selected)
    {
        if (selected)
        {
            setColor(Color(static_cast<int>(color()) + 5));
        }
        else
        {
            setColor(Color(static_cast<int>(color()) - 5));
        }

        m_isSelected = selected;
    }
}

QVector2D Tile::position() const
{
    return m_position;
}

void Tile::setPosition(QVector2D position)
{
    m_position = position;
    setPos(position.x() * 42 + 330, position.y() * 42 + 105);
}
