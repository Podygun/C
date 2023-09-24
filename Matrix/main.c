#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "helper.c"
#include "service.c"
#include "logger.c"

int **GenerateMatrix(int rows, int cols);
void FreeMatrix(int **matrix);
void PrintMatrix(int **matrix, int rows, int cols);
void SortMatrix(int **matrix, int rows, int cols);
int StrToInt(char *value);
int *ExtractRowsAndColsFromFile(char *filePath);

int main(int argc, char *argv[])
{
    system("chcp 1251");
    system("cls");

    Start();

    if (argc < 2)
    {
        Log("Lack of arguments\n", CRIT);
        Log("Must pass path to config file\n", INFO);
        End();
        return 1;
    }

    int *matrixSize = ExtractRowsAndColsFromFile(argv[1]);

    int rows = matrixSize[0];
    int cols = matrixSize[1];

    if (rows <= 0)
    {
        Log("Amount of rows was <= 0", CRIT);
        End();
        return 1;
    }

    if (cols <= 0)
    {
        Log("Amount of columns was <= 0", CRIT);
        End();
        return 1;
    }

    printf("Rows: %d\n", rows);
    printf("Cols: %d\n", cols);

    int **matrix = GenerateMatrix(rows, cols);

    printf("\nBefore sorting:\n");
    PrintMatrix(matrix, rows, cols);

    SortMatrix(matrix, rows, cols);

    printf("\nAfter sorting:\n");
    PrintMatrix(matrix, rows, cols);

    FreeMatrix(matrix);
    End();

    return 0;
}

/// @brief Convert char* to Int
/// @param value to convert
/// @return Integer value | 0 if fail convert
int StrToInt(char *value)
{
    int digit;

    if (sscanf(value, "%d", &digit) == 1)
    {
        return digit;
    }
    else
    {
        printf("Can't extract digit from '%s'\n", value);
        return 0;
    }
}

/// @brief Parse txt file and extract first two rows in integer array
/// @param filePath
/// @return Array of two int number (rows, cols)
int *ExtractRowsAndColsFromFile(char *filePath)
{
    static int result[2];
    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        Log("Can't open file\n", CRIT);
        return NULL;
    }

    char line[8]; // Буфер для чтения строки

    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (i >= 2)
        {
            Log("Too much rows in configuration file\n", CRIT);
            return NULL;
        }
        result[i] = StrToInt(line);
        i++;
    }

    fclose(file);

    return result;
}

/// @brief Create and fill 2-size matrix
/// @param rows
/// @param cols
/// @return Generated Matrix
int **GenerateMatrix(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    srand(time(NULL));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 100 + 1;
        }
    }

    return matrix;
}

/// @brief Clear and free memory of 2-size matrix
/// @param matrix
/// @param rows
void FreeMatrix(int **matrix)
{
    if (matrix != NULL)
    {
        int i = 0;
        while (matrix[i] != NULL)
        {
            free(matrix[i]);
            i++;
        }
        free(matrix);
    }
}

void PrintMatrix(int **matrix, int rows, int cols)
{
    printf("Matrix %d x %d:\n\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void SortMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        // Проверяем, четная ли строка
        if (i % 2 == 0)
        {
            // Сортировка по возрастанию для четных строк
            for (int j = 0; j < cols - 1; j++)
            {
                for (int k = 0; k < cols - j - 1; k++)
                {
                    if (matrix[i][k] > matrix[i][k + 1])
                    {
                        // Обмен элементов
                        int temp = matrix[i][k];
                        matrix[i][k] = matrix[i][k + 1];
                        matrix[i][k + 1] = temp;
                    }
                }
            }
        }
        else
        {
            // Сортировка по убыванию для нечетных строк
            for (int j = 0; j < cols - 1; j++)
            {
                for (int k = 0; k < cols - j - 1; k++)
                {
                    if (matrix[i][k] < matrix[i][k + 1])
                    {
                        // Обмен элементов
                        int temp = matrix[i][k];
                        matrix[i][k] = matrix[i][k + 1];
                        matrix[i][k + 1] = temp;
                    }
                }
            }
        }
    }
}
