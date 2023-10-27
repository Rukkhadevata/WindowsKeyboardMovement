#include <iostream>
#include <string>
#include <cstdio>
#include <windows.h>
#include <winuser.h>

using namespace std;

BOOL is_pressed(int key)
{
    BOOL ret = GetAsyncKeyState(key);
    return ret;
}

void mouse_wheel(int dir)
{
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_WHEEL;
    inputs[0].mi.mouseData = dir;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}

void mouse_hwheel(int hdir)
{
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_MOUSE;
#define MOUSEEVENTF_HWHEEL              0x01000 /* hwheel button rolled */
    inputs[0].mi.dwFlags = MOUSEEVENTF_HWHEEL;
    inputs[0].mi.mouseData = hdir;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}

int main()
{
    // ios::sync_with_stdio(false);
    // cout.tie(0);
    // cin.tie(0);
    cout << "enter a integer speed:";
    cout.flush();
    int WHEEL_SPEED;
    cin >> WHEEL_SPEED;
    cout << "HJKL/DU mappings is enabled.\n";
    cout << "use Ctrl + C to exit this program.";
    while (1)
    {
        if (is_pressed('J'))
        {
            mouse_wheel(-WHEEL_SPEED);
        }
        else if (is_pressed('K'))
        {
            mouse_wheel(WHEEL_SPEED);
        }
        else if (is_pressed('H'))
        {
            mouse_hwheel(-WHEEL_SPEED);
        }
        else if (is_pressed('L'))
        {
            mouse_hwheel(WHEEL_SPEED);
        }
        else if (is_pressed('D'))
        {
            mouse_wheel(-WHEEL_SPEED * 3);
        }
        else if (is_pressed('U'))
        {
            mouse_wheel(WHEEL_SPEED * 3);
        }
        Sleep(3);
    }
    return 0;
}
