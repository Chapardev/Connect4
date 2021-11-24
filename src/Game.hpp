#ifndef SRC_GAME_HPP
#define SRC_GAME_HPP

#include "LogoState.hpp"

class Game
{
public:
    Game();

    bool IsRunning() const { return !m_window.ShouldClose(); }

    void Update();
    void Draw();

private:
    static constexpr int s_boxSize { 128 };
    static constexpr int s_columns { 7 };
    static constexpr int s_rows { 6 };

    rl::Window m_window;
    rl::AudioDevice m_audioDevice;

    std::stack<std::unique_ptr<State>> m_states;
    std::map<std::string, rl::Texture2D> m_textures;
    std::map<std::string, rl::Sound> m_sounds;
};

#endif // SRC_GAME_HPP
