#include "GameState.hpp"

#include <algorithm>

GameState::GameState(const rl::Window &window, std::stack<std::unique_ptr<State>> &states, std::map<std::string, rl::Texture2D> &textures, 
        std::map<std::string, rl::Sound> &sounds)
    : State { window, states, textures, sounds }, m_playerTurn { 1 }, m_firstInterval { false }, m_oldTime { 0.0 }, m_currentTime { 0.0 }
{
    if (m_textures.find("box") == m_textures.end())
    {
        m_textures.emplace("box", "../assets/images/box.png");
        m_textures.emplace("disc", "../assets/images/disc2.png");
        m_sounds.emplace("disc", "../assets/sounds/disc_sound.wav");
    }

    int x { 0 };
    for (auto &subArray : m_boxes)
    {
        int y { 0 };
        for (auto &box : subArray)
        {
            box = rl::Rectangle(
                x * m_textures.at("box").GetWidth(), 
                y * m_textures.at("box").GetHeight(),
                m_textures.at("box").GetWidth(),
                m_textures.at("box").GetHeight() 
            );
            ++y;
        }
        ++x;
    }
}

bool GameState::CheckColumns() const
{
    for (std::size_t y { 0 }; y < m_boxes[0].size() - 3; ++y)
    {
        for (std::size_t x { 0 }; x < m_boxes.size(); ++x)
        {
            const int currentBoxState { m_boxes[x][y].GetState() };
            if ((currentBoxState != EMPTY) && (m_boxes[x][y+1].GetState() == currentBoxState) 
                && (m_boxes[x][y+2].GetState() == currentBoxState) && (m_boxes[x][y+3].GetState() == currentBoxState))
            {
                return true;
            }
        }
    }

    return false;
}

bool GameState::CheckRows() const
{
    for (std::size_t x { 0 }; x < m_boxes.size() - 3; x++ )
    {
        for (std::size_t y { 0 }; y < m_boxes[0].size(); y++)
        {
            const int currentBoxState { m_boxes[x][y].GetState() };
            if ((currentBoxState != EMPTY) && (m_boxes[x+1][y].GetState() == currentBoxState) 
                && (m_boxes[x+2][y].GetState() == currentBoxState) && (m_boxes[x+3][y].GetState() == currentBoxState))
            {
                return true;
            }         
        }
    }

    return false;
}

bool GameState::CheckAscendingDiagonal() const
{
    for (std::size_t x { 3 }; x < m_boxes.size(); ++x)
    {
        for (std::size_t y { 0 }; y < m_boxes[0].size() - 3; ++y)
        {
            const int currentBoxState { m_boxes[x][y].GetState() };
            if ((currentBoxState != EMPTY) && (m_boxes[x-1][y+1].GetState() == currentBoxState) && (m_boxes[x-2][y+2].GetState() == currentBoxState) 
                && (m_boxes[x-3][y+3].GetState() == currentBoxState))
            {
                return true;
            }
        }
    }

    return false;
}

bool GameState::CheckDescendingDiagonal() const
{
    for (std::size_t x { 3 }; x < m_boxes.size(); ++x)
    {
        for (std::size_t y { 3 }; y < m_boxes[0].size(); ++y)
        {
            const int currentBoxState { m_boxes[x][y].GetState() };
            if ((currentBoxState != EMPTY) && (m_boxes[x-1][y-1].GetState() == currentBoxState) && (m_boxes[x-2][y-2].GetState() == currentBoxState) 
                && (m_boxes[x-3][y-3].GetState() == currentBoxState))
            {
                return true;
            }
        }
    }

    return false;
}

bool GameState::CheckVictory() const
{
    return this->CheckColumns() || this->CheckRows() || this->CheckAscendingDiagonal() || this->CheckDescendingDiagonal();
}

bool GameState::CheckDraw() const
{
    return std::all_of(
        m_boxes.begin(), 
        m_boxes.end(), 
        [](const auto &subArray) {
            return std::all_of(subArray.begin(), subArray.end(), [](const Box &b) { return b.GetState() != EMPTY; });
        }
    );
}

void GameState::UpdateTime()
{
    m_currentTime = m_window.GetTime();

    if (m_currentTime - m_oldTime > 1.0)
    {
        if (!m_firstInterval)
        {
            m_firstInterval = true;
            m_oldTime = m_currentTime;
        }
        else
        {
            m_states.pop();
        }
    }
}

void GameState::Update()
{
    if (this->CheckVictory() || this->CheckDraw())
    {
        this->UpdateTime();
    }
    else
    {
        if (IsKeyPressed('R'))
        {
            m_states.pop();
        }

        int x { 0 };
        for (auto &subArray : m_boxes)
        {
            int y { 0 };
            for (auto &box : subArray)
            {
                if (box.GotClicked())
                {
                    const auto lastEmptyBox { std::find_if(subArray.rbegin(), subArray.rend(), [](const Box &b) { return b.GetState() == EMPTY; }) };
                    if (lastEmptyBox != subArray.rend())
                    {
                        m_sounds.at("disc").Play();
                        lastEmptyBox->AddDisc(m_playerTurn);
                        m_playerTurn = (m_playerTurn == 1) ? 2 : 1;
                    }
                }
                ++y;
            }
            ++x;
        }
    }
}

void GameState::DrawGameOverText(const std::string &text) const
{
    rl::Color::Black().DrawText(text, (m_window.GetWidth() - rl::MeasureText(text, 45)) / 2, (m_window.GetHeight() - 45) / 2, 45);
}

void GameState::Draw() const
{
    int x { 0 };
    for (const auto &subArray : m_boxes)
    {
        int y { 0 };
        for (const auto &box : subArray)
        {
            m_textures.at("box").Draw(x * m_textures.at("box").GetWidth(), y * m_textures.at("box").GetHeight());
            box.Draw(m_textures.at("disc"));
            ++y;
        }
        ++x;
    }

    if (this->CheckVictory())
    {
        this->DrawGameOverText("Player " + std::to_string((m_playerTurn == 1) ? 2 : 1) + " won!");
    }
    else if (this->CheckDraw())
    {
        this->DrawGameOverText("Draw!");
    }
}
