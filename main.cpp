#include <QApplication>
#include <QTimer>

#include "game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Game * game = new Game();

    game->show();

    QTimer::singleShot(60000, &app, SLOT(quit()));

    return app.exec();
}
