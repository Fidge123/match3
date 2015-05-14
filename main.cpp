#include <QApplication>

#include "game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto game = new Game();
    game->show();

    return app.exec();
}
