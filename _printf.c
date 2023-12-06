#include "main.h"
#include <unistd.h> // Include the necessary header for write

/**
 * _printf - Custom printf function
 * @format: Format string with conversion specifiers
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (format && *format)
    {
        if (*format == '%' && *(format + 1) != '\0')
        {
            switch (*(format + 1))
            {
                case 'c':
                    count += putchar(va_arg(args, int));
                    format += 2;
                    break;
                case 's':
                    count += print_str(va_arg(args, char *));
                    format += 2;
                    break;
                case '%':
                    count += putchar('%');
                    format += 2;
                    break;
                default:
                    count += putchar(*format);
                    format++;
            }
        }
        else
        {
            count += putchar(*format);
            format++;
        }
    }

    va_end(args);

    return count;
}

/**
 * putchar - Custom putchar function
 * @c: Character to be printed
 *
 * Return: 1 (success)
 */
int putchar(int c)
{
    return write(1, &c, 1);
}

/**
 * print_str - Custom function to print a string
 * @str: String to be printed
 *
 * Return: Number of characters printed
 */
int print_str(char *str)
{
    int count = 0;

    if (str == NULL)
        str = "(null)";

    while (*str)
    {
        count += putchar(*str);
        str++;
    }

    return count;
}

