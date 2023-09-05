#include <vector>
#include <algorithm>
#include "Screen.h"
#include <SDL.h>

const int Map_Height = 480;
const int Map_Width = 720;

bool isAlive(const std::vector<std::vector<int>>& game, int x, int y)
{
    int alive = 0;
    // testing the left
    if (x > 0 && game[x - 1][y] == 1)
        alive += 1;
    // testing the right
    if (x < Map_Width-1 && game[x + 1][y] == 1)
        alive += 1;
    // testing the top
    if (y > 0 && game[x][y - 1] == 1)
        alive += 1;
    // testing the bottom
    if (y < Map_Height - 1 && game[x][y + 1] == 1)
        alive += 1;

    // testing top-left
    if (x > 0 && y > 0 && game[x - 1][y - 1] == 1)
        alive += 1;
    // testing top-right
    if (x < Map_Width - 1 && y > 0 && game[x + 1][y - 1] == 1)
        alive += 1;
    // testing bottom-left
    if (x > 0 && y < Map_Height - 1 && game[x - 1][y + 1] == 1)
        alive += 1;
    // testing bottom-right
    if (x < Map_Width - 1 && y < Map_Height - 1 && game[x + 1][y + 1] == 1)
        alive += 1;

    //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    if (game[x][y] == 1 && alive < 2)
        return false;
    //Any live cell with two or three live neighbours lives on to the next generation.
    if (game[x][y] == 1 && (alive == 2 || alive == 3))
        return true;
    //Any live cell with more than three live neighbours dies, as if by overpopulation.
    if (alive > 3)
        return false;
    //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    if (game[x][y] == 0 && alive == 3)
        return true;

    return false;
}

int main(int argc, char* argv[])
{
    G screen;

    std::vector<std::vector<int>> display(Map_Width, std::vector<int>(Map_Height));
    std::vector<std::vector<int>> swap(Map_Width, std::vector<int>(Map_Height));

    // Create random points
    for (auto& row : display)
        std::generate(row.begin(), row.end(), []() { return rand() % 10 == 0 ? 1 : 0; });

    while (true)
    {
        // Check for alive points
        for (int i = 0; i < Map_Width; i++)
        {
            for (int j = 0; j < Map_Height; j++)
            {
                swap[i][j] = isAlive(display, i, j) ? 1 : 0;
            }
        }

        // Draw
        for (int i = 0; i < Map_Width; i++)
        {
            for (int j = 0; j < Map_Height; j++)
            {
                if (swap[i][j])
                {
                    screen.drawpixel(i, j);
                }
            }
        }

        // Swap buffers
        display = swap;

        // Display to screen
        screen.update();
        SDL_Delay(30);
        screen.input();
        screen.clearpixels();
    }

    return 0;
}