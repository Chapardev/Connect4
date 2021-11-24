#ifndef SRC_BOX_HPP
#define SRC_BOX_HPP

#include "raylib-cpp.hpp"

enum { EMPTY, PLAYER1, PLAYER2 };

class Box
{
public:
    Box() = default;
    Box(const rl::Rectangle &rec);

    bool IsHovered() const noexcept { return rl::Mouse::GetPosition().CheckCollision(m_rec); }
    bool GotClicked() const noexcept
    {
        return rl::Mouse::IsButtonPressed(MOUSE_LEFT_BUTTON) && rl::Mouse::GetPosition().CheckCollision(m_rec);
    }

    int GetState() const noexcept { return m_state; }

    void AddDisc(int playerTurn) { m_state = playerTurn; }

    void Draw(rl::Texture2D &texture) const;

private:
    rl::Rectangle m_rec;
    int m_state;
};

#endif // SRC_BOX_HPP
