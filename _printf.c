#include "main.h"

void _cleaner(va_list arg_list, buffer_t *output);
int _act_printf(const char *format, va_list arg_list, buffer_t *output);
int _printf(const char *format, ...);

/**
 * _cleaner - Cleans the buffer for _printf
 * @arg_list: List of arguments
 * @output: A buffer_t struct
 */

void _cleaner(va_list arg_list, buffer_t *output)
{
	va_end(arg_list);
	write(1, output->start, output->length);
	_free_buffer(output);
}

/**
 * _act_printf - Calculates the number of character stored to
 * output
 * @format: Character string input
 * @output: A buffer_t struc that contains a buffer
 * @arg_list: List of arguments
 *
 * Return: The number of characters stored to output
 */

int _act_printf(const char *format, va_list arg_list, buffer_t *output)
{
	int indx, width, precision, rem = 0;
	char temp;
	unsigned char flags, length;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (indx = 0; *(format + indx); indx++)
	{
		length = 0;
		if (*(format + indx) == '%')
		{
			temp = 0;
			flags = find_flags(format + indx + 1, &temp);
			width = find_width(arg_list, format + indx + temp + 1, &temp);
			precision = find_precision(arg_list, format + indx + temp + 1,
					&temp);
			length = find_length(format + indx + temp + 1, &temp);

			f = find_specifiers(format + indx + temp + 1);
			if (f != NULL)
			{
				indx += temp + 1;
				rem += f(arg_list, output, flags, width, precision, length);
				continue;
			}
			else if (*(format + indx + temp + 1) == '\0')
			{
				rem = -1;
				break;
			}
		}
		rem += _memory_copy(output, (format + indx), 1);
		indx += (length != 0) ? 1 : 0;
	}
	_cleaner(arg_list, output);
	return (rem);
}

/**
 * _printf - Outputs a formatted string
 * @format: Character string input
 *
 * Return: The number of characters printed
 */

int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list arg_list;
	int rem;

	if (format == NULL)
		return (-1);
	output = initialize_buffer();
	if (output == NULL)
		return (-1);

	va_start(arg_list, format);

	rem = _act_printf(format, arg_list, output);

	return (rem);
}
