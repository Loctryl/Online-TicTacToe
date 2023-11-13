#include "StateMachine.h"
#include "BaseState.h"
#include "Resources/framework.h"

StateMachine::StateMachine() { mCurrentState = nullptr; }

StateMachine::~StateMachine() { REL_PTR(mCurrentState) }

void StateMachine::SwitchState(BaseState* newState)
{
    mCurrentState->OnExit();
    REL_PTR(mCurrentState)

    mCurrentState = newState;
    mCurrentState->OnEnter();
}

void StateMachine::Update() const { mCurrentState->OnStay(); }