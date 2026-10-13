#pragma once

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