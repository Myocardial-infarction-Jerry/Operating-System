#include <iostream>
#include <stdarg.h>

void print_any_number_of_integers(int n, ...);

int main()
{
    print_any_number_of_integers(1, 21307289);
    print_any_number_of_integers(2, 2130, 7289);
    print_any_number_of_integers(8, 2, 1, 3, 0, 7, 2, 8, 9);
}

void print_any_number_of_integers(int n, ...)
{
    // 定义一个指向可变参数的指针parameter
    va_list parameter;
    // 使用固定参数列表的最后一个参数来初始化parameter
    // parameter指向可变参数列表的第一个参数
    va_start(parameter, n);

    for (int i = 0; i < n; ++i)
    {
        // 引用parameter指向的int参数，并使parameter指向下一个参数
        std::cout << va_arg(parameter, int) << " ";
    }

    // 清零parameter
    va_end(parameter);

    std::cout << std::endl;
}