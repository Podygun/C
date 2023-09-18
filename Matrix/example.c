
// Comments
// int x = 7;
// double y = 16;

// Multistring Comment
/*

int GLOBAL_INT = 100;
const double PI = 3.14;

char ComputeX(char symbol)
{
    int GLOBAL_INT = 100;
    const double PI = 3.14;
    char s = symbol;
    return s;
};
*/

// Definition of funtions
double func1(float value);
float func2(double x, int steps, char *str);

// Global variables
int GLOBAL_INT = 100;
const double PI = 3.14;

// Implementaion of functions
int ComputeX()
{
    return 0;
};

void ComputeX()
{
    return 0;
};

char ComputeX(char symbol)
{
    char s = symbol;
    return s;
};

int main(int argc, char *argv[])
{

    double x = ComputeX();
    printf("Most right x is %f", x);
    return 0;
}

/// @brief Вычисляет правое выражение
/// @param x Значение x
/// @param steps Кол-во итераций для вычисления суммы (n)
/// @return Итоговая сумма элементов
double ComputeRightExpression(double x, int steps, char *str)
{
    if (x == 0)
        return 0.0;

    double result;
    double singleElement;

    for (int i = 0; i < steps; ++i)
    {
        singleElement = pow(x, 4 * i + 1) / (4 * i + 1);
        result += singleElement;
    }
    return result;
}
