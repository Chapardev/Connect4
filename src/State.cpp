#include "State.hpp"

State::State(const rl::Window &window, std::stack<std::unique_ptr<State>> &states, std::map<std::string, rl::Texture2D> &textures, 
        std::map<std::string, rl::Sound> &sounds)
    : m_window { window }, m_states { states }, m_textures { textures }, m_sounds { sounds }
{
    
}
