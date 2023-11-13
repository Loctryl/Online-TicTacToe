#pragma once
#include <States/BaseState.h>
#include <States/StateMachine.h>


class GameState : StateMachine
{
public:
    class Init : BaseState
    {
        void OnEnter() override;
        void OnStay() override;
        void OnExit() override;
    };

    class Update : BaseState
    {
        
    };
};