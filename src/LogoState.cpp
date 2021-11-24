#include "LogoState.hpp"

#include "TitleState.hpp"

LogoState::LogoState(const rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, std::map<std::string, rl::Texture2D> &p_textures, 
        std::map<std::string, rl::Sound> &p_sounds)
    : State { p_window, p_states, p_textures, p_sounds }
{
    m_textures.emplace("logo", "../assets/images/raylib_logo.png");
    m_sounds.emplace("logo", "../assets/sounds/logo_sound.wav");
}

void LogoState::Update()
{
    static const double oldTime { m_window.GetTime() };
    static bool soundPlayed { false };

    if ((m_window.GetTime() - oldTime > 1.0) && !soundPlayed)
    {
        m_sounds.at("logo").Play();
        soundPlayed = true;
    }
    
    if (((m_window.GetTime() - oldTime) > 4.0) || (rl::Mouse::IsButtonPressed(MOUSE_LEFT_BUTTON)))
    {
        m_textures.erase("logo");
        m_sounds.erase("logo");
        // Logo state will not be shown anymore after that, so you can pop it
        m_states.pop();
        m_states.push(std::make_unique<TitleState>(m_window, m_states, m_textures, m_sounds));
    }
}

void LogoState::Draw() const
{
    static const double oldTime { m_window.GetTime() };

    if ((m_window.GetTime() - oldTime) > 1.0)
    {
        rl::Color::Black().DrawText(
            "Made with", 
            (m_window.GetWidth() - (rl::MeasureText("Made with", 32) + m_textures.at("logo").GetWidth())) / 2, 
            (m_window.GetHeight() - 32) / 2, 
            32
        );
        
        m_textures.at("logo").Draw(
            (m_window.GetWidth() - (rl::MeasureText("Made with", 32) + m_textures.at("logo").GetWidth())) / 2 
                + rl::MeasureText("Made with", 32) + 10, 
            (m_window.GetHeight() - m_textures.at("logo").GetHeight()) / 2
        );
    }
}
