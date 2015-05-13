#include "game.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QTimer>

#include "tile.h"
#include "grid.h"

Game::Game()
    : m_scene(new QGraphicsScene(this))
    , m_scoreDisplay(new QGraphicsTextItem)
    , m_timerDisplay(new QGraphicsTextItem)
    , m_score(0)
    , m_seconds(60)
    , m_timer(new QTimer)
    , m_isActive(false)
{
    setScene(m_scene);

    QGraphicsPixmapItem * bg = new QGraphicsPixmapItem(QPixmap(":/assets/BackGround.jpg"));
    m_scene->addItem(bg);

    QPushButton * button = new QPushButton("Start");
    button->setGeometry(80, 200, 80, 40);
    m_scene->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(start()));

    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimerDisplay()));

    m_scoreDisplay->setScale(3.5);
    m_scoreDisplay->setDefaultTextColor(QColor(255, 255, 255));
    m_scoreDisplay->setPos(30, 30);
    m_scoreDisplay->setPlainText(QString("Score: 0"));
    m_scene->addItem(m_scoreDisplay);

    m_timerDisplay->setScale(3.5);
    m_timerDisplay->setDefaultTextColor(QColor(255, 255, 255));
    m_timerDisplay->setPos(30, 100);
    m_timerDisplay->setPlainText(QString("Time: 60"));
    m_scene->addItem(m_timerDisplay);
}

Game::~Game()
{

}

void Game::start()
{
    if (!m_isActive)
    {
        m_grid = new Grid(this);
        setScore(0);
        m_timer->start();
        m_isActive = true;
    }
}

void Game::reset()
{
    if (m_isActive)
    {
        m_isActive = false;
        delete m_grid;
        m_seconds = 60;
    }
}

void Game::updateTimerDisplay()
{
    if (m_seconds--)
    {
        m_timerDisplay->setPlainText(QString("Time: ") += QString::number(m_seconds));
    }
    else
    {
        m_timer->stop();
        reset();
    }
}

QGraphicsScene * Game::scene()
{
    return m_scene;
}

int Game::score()
{
    return m_score;
}

void Game::setScore(int score)
{
    m_score = score;
    m_scoreDisplay->setPlainText(QString("Score: ") += QString::number(m_score));
}

QTimer * Game::timer()
{
    return m_timer;
}

void Game::mousePressEvent(QMouseEvent * event)
{
    QGraphicsView::mousePressEvent(event);
}

void Game::mouseReleaseEvent(QMouseEvent * event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

