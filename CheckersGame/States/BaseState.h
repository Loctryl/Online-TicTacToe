#pragma once

class BaseState
{
public:
    BaseState();
    virtual ~BaseState();
    
    virtual void OnEnter() = 0;
    virtual void OnStay() = 0;
    virtual void OnExit() = 0;
};
