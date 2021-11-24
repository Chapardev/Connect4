#include "TitleState.hpp"

#include "GameState.hpp"

TitleState::TitleState(const rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, std::map<std::string, rl::Texture2D> &p_textures, 
        std::map<std::string, rl::Sound> &p_sounds)
    : State { p_window, p_states, p_textures, p_sounds }, m_launchedOnce { false }, m_oldTime { 0.0 }, m_currentTime { 0.0 }
{
    
}

void TitleState::Update()
{
    if (!m_launchedOnce)
    {
        m_currentTime = m_window.GetTime();

        if (rl::Mouse::IsButtonPressed(MOUSE_LEFT_BUTTON))
        {
            m_states.push(std::make_unique<GameState>(m_window, m_states, m_textures, m_sounds));
            m_launchedOnce = true;
        }
    }
    else
    {
        m_states.push(std::make_unique<GameState>(m_window, m_states, m_textures, m_sounds));
    }
}

void TitleState::Draw() const
{
    if (!m_launchedOnce)
    {
        rl::Color::Red().DrawText("CONNECT 4", (m_window.GetWidth() - (rl::MeasureText("CONNECT 4", 60))) / 2, (m_window.GetHeight() - 60) / 4, 60);

        if (m_currentTime - m_oldTime > 0.5)
        {
            rl::Color::DarkGray().DrawText(
                "CLICK TO START", 
                (m_window.GetWidth() - (rl::MeasureText("CLICK TO START", 30))) / 2, 
                (m_window.GetHeight() - 30) * 3 / 4, 
                30
            );

            if (m_currentTime - m_oldTime > 1.0)
            {
                m_oldTime = m_currentTime;
            }
        }
    }
}
