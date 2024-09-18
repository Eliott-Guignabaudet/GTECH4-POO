#pragma once
#include <functional>
#include "Controller.h"
#include "Vector2.h"


using namespace Maths;
class PlayerController :
    public Controller
{
public:
    virtual void PossessFighter(Fighter* fighter) override;
    virtual void Update() override;
    std::function<void()> OnFinishTurn;
private:
    void HandleInput();
    void HandleInputDirection(Vector2& direction);
    void HandleInputFinishTurn();
    void MovePlayer(Vector2 direction);
};

