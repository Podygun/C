#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

enum LogLevel
{
    DEBUG, // white
    INFO,  // green
    CRIT   // red
};

void ResetConsoleColors()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

char *GetTime()
{
    static char time_buffer[12];

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_buffer, sizeof(time_buffer), "[%H:%M:%S]", timeinfo);

    return time_buffer;
}

bool IsLinux()
{
#ifdef _WIN32
    return false;
#endif
    return true;
}

void Log(char *message, enum LogLevel level)
{
    if (IsLinux())
    {
        switch (level)
        {
        case DEBUG:
            printf("\033[31;43mКрасный текст на желтом фоне\033[0m\n");

            // Возврат к стандартным цветам (белый текст на черном фоне)
            printf("\033[0mСтандартные цвета\n");
            break;

        default:
            break;
        }
    }
    else
    {
        ResetConsoleColors();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (level)
        {
        case DEBUG:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
            printf("%-10s ", GetTime());
            ResetConsoleColors();
            printf("%-6s %s", "DEBUG", message);
            break;
        case INFO:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
            printf("%-10s ", GetTime());
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("%-6s %s", "INFO", message);
            break;
        case CRIT:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
            printf("%-10s ", GetTime());
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("%-6s %s", "ERROR", message);
            break;
        default:
            break;
        }

        ResetConsoleColors();
    }
}

void WriteToFile(char *message, enum LogLevel level)
{
    // // строка для записи
    // char * message = "Hello METANIT.COM!\nAn apple a day keeps the doctor away";
    // // файл для записи
    // char * filename = "data.txt";
    // // запись в файл
    // FILE *fp = fopen(filename, "w");
    // if(fp)
    // {
    //     // записываем строку
    //     fputs(message, fp);
    //     fclose(fp);
    //     printf("File has been written\n");
    // }
}
