#include <ncurses.h>

class Vec2
{
  public:
    int x, y;

    Vec2(int x = 0, int y = 0) : x(x), y(y)
    {
    }

    Vec2 operator-(Vec2 o)
    {
        return Vec2(this->x - o.x, this->y - o.y);
    }

    Vec2 operator+(Vec2 o)
    {
        return Vec2(this->x + o.x, this->y + o.y);
    }

    bool operator==(const Vec2 o)
    {
        return (this->x == o.x && this->y == o.y) ? true : false;
    }
};

void drawAt(Vec2 pos, char c)
{
    mvaddch(pos.y, pos.x * 2, c);
    mvaddch(pos.y, pos.x * 2 + 1, c);
}
