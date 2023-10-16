rm#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Print chars.
 */
int _printf(const char *format, ...)
{
	int f, print = 0, print_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (f = 0; format && format[f] != '\0'; ++f)
	{
		if (format[f] != '%')
		{
			buffer[buff_ind++] = format[f];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[f], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &f);
			width = get_width(format, &f, list);
			precision = get_precision(format, &f, list);
			size = get_size(format, &f);
			++f;
			print = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (print == -1)
				return (-1);
			print_chars += print;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (print_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

