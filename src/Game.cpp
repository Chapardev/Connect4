#include "Game.hpp"

Game::Game() : m_window { s_boxSize * s_columns, s_boxSize * s_rows, "Connect 4" }
{
    m_window.SetIcon(rl::Image { "../assets/images/raylib_icon.png" });

    /* 
     * Game states cycle work like this:
     * [Logo] -> Title -> Gameplay -> Ending
     *            ^--------------------'
     */
    m_states.push(std::make_unique<LogoState>(m_window, m_states, m_textures, m_sounds));
}

void Game::Update()
{
    m_states.top()->Update();
}

void Game::Draw()
{
    m_window.BeginDrawing();

        m_window.ClearBackground(rl::Color::RayWhite());

        m_states.top()->Draw();

    m_window.EndDrawing();
}
