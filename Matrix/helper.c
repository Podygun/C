#include <stdio.h>
#include <wchar.h>

/// @brief Print message in console
/// @param message String with prefix L
void cout(const wchar_t *message)
{
    wprintf(L"%ls", message);
}
