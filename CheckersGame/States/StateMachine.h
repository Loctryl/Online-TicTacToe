#pragma once
#include <vector>


class BaseState;


class StateMachine
{

    BaseState* mCurrentState;
public:

    StateMachine();
    virtual ~StateMachine();

    void SwitchState(BaseState* newState);
    void Update() const;
    
};