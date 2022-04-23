#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#define VK_LBUTTON_PRESSED_AFTER_PRESSED -127
#define VK_LBUTTON_PRESSED_AFTER_UNPRESSED -128
#define ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
  (size_t)(!(sizeof(a) % sizeof(*(a)))))

int main(int argc, char* argv[]) {

  BOOL end = false;
  MSG msg;
  // sets clicks per  minute
  short int clicks_per_minute = strtol(argv[1], NULL, 10);
  
  if (clicks_per_minute > 0) {
    float delay_btw_clicks = 1000*((float)60/clicks_per_minute);
    float delay_before_up = 100*((float)60/clicks_per_minute);

    while (!end) {
      Sleep(delay_btw_clicks);
      short int button_action_code = GetKeyState(VK_LBUTTON);
      if (button_action_code == VK_LBUTTON_PRESSED_AFTER_PRESSED
      || button_action_code == VK_LBUTTON_PRESSED_AFTER_UNPRESSED) {
        INPUT inputs[1] = {};
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.mouseData = XBUTTON1;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        // inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        Sleep(delay_before_up);
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.mouseData = XBUTTON1;
        // inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        
        printf("Pressed\n");
      }
    }
  }

   return EXIT_SUCCESS;
}