#ifndef SRC_LOGO_STATE_HPP
#define SRC_LOGO_STATE_HPP

#include "State.hpp"

class LogoState : public State
{
public:
    LogoState(const rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, std::map<std::string, rl::Texture2D> &p_textures, 
        std::map<std::string, rl::Sound> &p_sounds);

    void Update() override;
    void Draw() const override;
};

#endif // SRC_LOGO_STATE_HPP
