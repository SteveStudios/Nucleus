// handler_keyboardps2.c - PS/2 Keyboard handler
// Created 2023/7/20 by Stephen Byrne

#include "handler_keyboardps2.h"

void handle_keyboard(void)
{
    char *allowed_chars = "abcdefghijklmnopqrstuvwxyz1234567890|~#$%()*+-:;<=>@[]^_.,'!?";
    bool is_char_allowed = false;

    if (strlen(get_key().m_key) == 1 && get_key().released == false)
    {
        for (int i = 0; i < strlen(allowed_chars); i++)
        {
            // Check if he pressed key is equal to an allowed character
            if (*get_key().m_key == allowed_chars[i])
            {
                is_char_allowed = true;
                break;
            }
            is_char_allowed = false;
        }
    }
    if (is_char_allowed)
        print(get_key().m_key);
}