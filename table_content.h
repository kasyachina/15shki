#ifndef TABLE_CONTENT_H
#define TABLE_CONTENT_H

enum class MovementDirection
{
    Zero,
    Up,
    Down,
    Left,
    Right,
};

class table_content
{
private:
    int contents[4][4];
    int copied[4][4];
    int moves;
    int seconds_passed;
public:
    table_content();
    void MakeTable();
    int GetItem(int x, int y) const;
    int GetMoves() const;
    int GetTime() const;
    void UpdateTime();
    MovementDirection GetPossibleMovement(int x, int y) const;
    void MoveCell(int x, int y, MovementDirection mv);
    bool IsFinished() const;
    void RestoreContents();
};
#endif // TABLE_CONTENT_H
