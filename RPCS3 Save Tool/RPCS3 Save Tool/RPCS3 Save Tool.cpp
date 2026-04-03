#include <windows.h>
#include <iostream>

void SendCtrlKey(WORD key)
{
    INPUT inputs[4] = {};

    // Press CTRL
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;

    // Press target key (S or R)
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key;

    // Release target key
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = key;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    // Release CTRL
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(4, inputs, sizeof(INPUT));
}

int main()
{
    std::cout << "Running key remapper...\n";

    while (true)
    {
        // SPACE = Save (Ctrl + S)
        if (GetAsyncKeyState(VK_SPACE) & 1)
        {
            SendCtrlKey('S');
            std::cout << "Saved!\n";
        }

        // RIGHT SHIFT = Load (Ctrl + R)
        if (GetAsyncKeyState(VK_RSHIFT) & 1)
        {
            SendCtrlKey('R');
            std::cout << "Loaded!\n";
        }

        Sleep(10); // prevent CPU spam
    }

    return 0;
}