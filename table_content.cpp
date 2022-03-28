#include "table_content.h"
#include <algorithm>
#include <random>
#include <QRandomGenerator>
#include <vector>

const int _size = 4;
const int n = _size * _size;

void table_content::MakeTable()
{
    std::vector<int> temp(n);
    for(int i = 0; i < n; ++i)
    {
        temp[i] = i;
    }
    std::mt19937 g(QRandomGenerator::global()->generate());
    do
    {
        std::shuffle(begin(temp), end(temp), g);
        for(int i = 0; i < n; i++)
        {
            contents[i / _size][i % _size] = temp[i];
            copied[i / _size][i % _size] = temp[i];
        }
    }while(IsFinished());
    moves = 0;
    seconds_passed = 0;
}
int table_content::GetMoves() const
{
    return moves;
}
void table_content::UpdateTime()
{
    seconds_passed++;
}
int table_content::GetTime() const
{
    return seconds_passed;
}
table_content::table_content()
{
    MakeTable();
}
bool table_content::IsFinished() const
{
    for(int i = 0; i < _size - 1; ++i)
    {
        for(int j = 0; j < _size; ++j)
        {
            if(contents[i][j] != _size * i + j + 1)
                   return false;
        }
    }
    if(contents[_size - 1][0] != 13 || contents[_size - 1][1] + contents[_size - 1][2] != 29)
        return false;
    return true;
}
void table_content::RestoreContents()
{
    for(int i = 0; i < _size; ++i)
    {
        for(int j = 0; j < _size; ++j)
        {
            contents[i][j] = copied[i][j];
        }
    }
    moves = 0;
    seconds_passed = 0;
}

int table_content::GetItem(int x, int y) const
{
    return contents[x][y];
}

MovementDirection table_content::GetPossibleMovement(int x, int y) const
{
    if(x != 0 && contents[x - 1][y] == 0)
    {
        return MovementDirection::Up;
    }
    if(x != _size - 1 && contents[x + 1][y] == 0)
    {
        return MovementDirection::Down;
    }
    if(y != 0 && contents[x][y - 1] == 0)
    {
        return MovementDirection::Left;
    }
    if(y != _size - 1 && contents[x][y + 1] == 0)
    {
        return MovementDirection::Right;
    }
    return MovementDirection::Zero;
}
void table_content::MoveCell(int x, int y, MovementDirection mv)
{
    switch(mv)
    {
    case MovementDirection::Up :
        std::swap(contents[x][y], contents[x - 1][y]);
        break;
    case MovementDirection::Down :
        std::swap(contents[x][y], contents[x + 1][y]);
        break;
    case MovementDirection::Left :
        std::swap(contents[x][y], contents[x][y - 1]);
        break;
    case MovementDirection::Right :
        std::swap(contents[x][y], contents[x][y + 1]);
        break;
    case MovementDirection::Zero :
        break;
    }
    if(mv != MovementDirection::Zero)
    {
        moves++;
    }
}
