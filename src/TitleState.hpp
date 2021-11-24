#ifndef SRC_TITLE_STATE_HPP
#define SRC_TITLE_STATE_HPP

#include "State.hpp"

using Time = double;

class TitleState : public State
{
public:
    TitleState(const rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, std::map<std::string, rl::Texture2D> &p_textures, 
        std::map<std::string, rl::Sound> &p_sounds);

    void Update() override;
    void Draw() const override;

private:
    bool m_launchedOnce;
    mutable Time m_oldTime;
    Time m_currentTime;
};

#endif // SRC_TITLE_STATE_HPP