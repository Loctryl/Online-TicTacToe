#pragma once

class BaseState
{
public:
    BaseState();
    virtual ~BaseState();
    
    virtual void OnEnter();
    virtual void OnStay();
    virtual void OnExit();
};
