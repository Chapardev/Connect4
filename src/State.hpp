#ifndef SRC_STATE_HPP
#define SRC_STATE_HPP

#include "raylib-cpp.hpp"

#include <map>
#include <memory>
#include <stack>

class State
{
public:
    State(const rl::Window &window, std::stack<std::unique_ptr<State>> &states, std::map<std::string, rl::Texture2D> &textures, 
        std::map<std::string, rl::Sound> &sounds);

    virtual void Update() = 0;
    virtual void Draw() const = 0;

protected:
    const rl::Window &m_window;
    std::stack<std::unique_ptr<State>> &m_states;
    std::map<std::string, rl::Texture2D> &m_textures;
    std::map<std::string, rl::Sound> &m_sounds;
};

#endif // SRC_STATE_HPP
