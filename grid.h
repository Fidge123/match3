#pragma once

#include <vector>

class Game;
class Tile;

class Grid
{
public:
    Grid(Game * game);
    ~Grid();

    void setSelectedTile(Tile * tile);

    bool swap(Tile * t1, Tile * t2);
    bool swapUp(Tile * t);
    bool swapDown(Tile * t);
    bool swapLeft(Tile * t);
    bool swapRight(Tile * t);

protected:
    void initializeTiles();
    void fillGrid();
    void applyGravity();
    bool removePairs(bool enableScoring);

protected:
    std::vector<std::vector<Tile *>> m_tiles;
    Tile * m_selectedTile;
    Game * m_game;
};
