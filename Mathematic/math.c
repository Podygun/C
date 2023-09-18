#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <wchar.h>

#include "helper.c"
#include "service.c"

double ComputeLeftDerivative(double value);
double ComputeLeftExpression(double x);
double ComputeRightExpression(double x, int steps);
double ComputeX();

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    Start();

    double x = ComputeX();
    printf("Most right x is %f", x);

    End();

    return 0;
}

/// @brief Вычисляет правое выражение
/// @param x Значение x
/// @param steps Кол-во итераций для вычисления суммы (n)
/// @return Итоговая сумма элементов
double ComputeRightExpression(double x, int steps)
{
    // printf("\tComputeRightExpression(%f,%d)\n", x, steps);
    if (x == 0)
        return 0.0;

    double result;
    double singleElement;

    for (int i = 0; i < steps; ++i)
    {
        singleElement = pow(x, 4 * i + 1) / (4 * i + 1);
        result += singleElement;
        // printf("\tel = %f , res = %f\n", singleElement, result);
    }
    // printf("\n\n\n");
    return result;
}

/// @brief Вычисляет левое выражение
/// @param x Для подстановки
/// @return Ответ по переданному x
double ComputeLeftExpression(double x)
{
    double value = (log((1 + x) / (1 - x))) / 4 + (atan(x) / 2);
    return value;
}

/// @brief Вычисляет производную для левой части выражения
/// @param x Для подстановки
/// @return Ответ по переданному x
double ComputeLeftDerivative(double x)
{
    return 1 / ((1 - x) * (1 + x) * (x * x + 1));
}

double ComputeX()
{
    // input data
    const double startX = 0.0;
    const double endX = 0.8;
    const double stepSize = 0.1;
    const int totalSteps = 5;
    const double accuracy = 1e-4;

    // variables
    double result;
    double x = startX;
    double rightValue;
    double leftDerivativeValue;
    double leftValue;

    for (; x <= endX; x += stepSize)
    {
        printf("\n==============================================================\n");
        printf("x = %.1f\n", x);
        wprintf(L"%-12ls %-12ls %-12ls %-12ls %-12ls\n", L"Left", L"left`", L"Right", L"DeltaL-R", L"DeltaFinal");

        rightValue = ComputeRightExpression(x, totalSteps);
        leftValue = ComputeLeftExpression(x);
        leftDerivativeValue = ComputeLeftDerivative(x);

        double delta = leftValue - rightValue;
        double delta_x = delta / leftDerivativeValue;

        printf("%-12.10f %-12.10f %-12.10f %-12.10f %-12.10f\n", leftValue, leftDerivativeValue, rightValue, delta, delta_x);
    }

    return result;
}
