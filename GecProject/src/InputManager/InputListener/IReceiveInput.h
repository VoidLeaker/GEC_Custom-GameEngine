#pragma once

// Input actions that can be received by input listeners. 
// These actions represent user input events such as movement, mouse clicks, and pause.
enum class InputAction
{
    eMoveUp,
    eMoveDown,
    eMoveLeft,
    eMoveRight,
    eNone,
    ePause,
    eLeftMouseClick,
    eRightMouseClick,
};


class IReceiveInput
{
public:
    virtual ~IReceiveInput() = default;
    virtual void handleInput(InputAction action) = 0;
};