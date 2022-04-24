#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#define ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
  (size_t)(!(sizeof(a) % sizeof(*(a)))))

BOOL click_in_progress = false;
BOOL VK_LBUTTON_PRESSED = false;

DWORD WINAPI ButtonStatusThread(void* value) {
  while (true) {
    BOOL key_state = (GetAsyncKeyState(VK_LBUTTON) < 0);
    if (click_in_progress == false) {
      VK_LBUTTON_PRESSED = key_state;
    }
  }
}

// // inputs[0].mi.dwFlags = (button_action_code == VK_LBUTTON_PRESSED_AFTER_PRESSED) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_LEFTDOWN;

int main(int argc, char* argv[]) {

  HANDLE button_status_thread = CreateThread(NULL, 0, ButtonStatusThread, NULL, 0, NULL);
  MSG msg;
  // sets clicks per  minute
  const short int clicks_per_minute = strtol(argv[1], NULL, 10);
  
  if (clicks_per_minute > 0) {
    const float delay_btw_clicks = 1000*((float)60/clicks_per_minute);
    while (true) {      
      while (VK_LBUTTON_PRESSED && (GetAsyncKeyState(0x5A) >= 0) && click_in_progress == false) {
        click_in_progress = true;
        
        if (VK_LBUTTON_PRESSED) {
          mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }

        if (!VK_LBUTTON_PRESSED) {
          mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        }

        click_in_progress = false;
        Sleep(delay_btw_clicks);
      }
    }
  }

   return EXIT_SUCCESS;
}