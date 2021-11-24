#include "Box.hpp"

Box::Box(const rl::Rectangle &rec)
    : m_rec { rec }, m_state { EMPTY }
{

}

void Box::Draw(rl::Texture2D &texture) const
{
    if (m_state != EMPTY)
    {
        rl::Vector2 { m_rec.GetX() + m_rec.GetWidth() / 2, m_rec.GetY() + m_rec.GetHeight() / 2 }.DrawCircle(
            m_rec.GetWidth() / 4 + 1, ((m_state == PLAYER1) ? rl::Color::Yellow() : rl::Color::Red())
        );

        texture.Draw(rl::Vector2 { m_rec.GetX(), m_rec.GetY() });
    }
}
