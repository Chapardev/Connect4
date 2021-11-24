#ifndef SRC_GAME_STATE_HPP
#define SRC_GAME_STATE_HPP

#include "State.hpp"

#include "Box.hpp"

#include <array>

using Time = double;

class GameState : public State
{
public:
    GameState(const rl::Window &window, std::stack<std::unique_ptr<State>> &states, std::map<std::string, rl::Texture2D> &textures, 
        std::map<std::string, rl::Sound> &sounds);

    bool CheckColumns() const;
    bool CheckRows() const;
    bool CheckAscendingDiagonal() const;
    bool CheckDescendingDiagonal() const;
    bool CheckVictory() const;
    bool CheckDraw() const;

    // Updates the time elapsed when a player wins or when there is a draw
    void UpdateTime();
    void Update() override;

    void DrawGameOverText(const std::string &text) const;
    void Draw() const override;

private:
    int m_playerTurn;
    std::array<std::array<Box, 6>, 7> m_boxes;

    bool m_firstInterval;
    Time m_oldTime;
    Time m_currentTime;
};

#endif // SRC_GAME_STATE_HPP
