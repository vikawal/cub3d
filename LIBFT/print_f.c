/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:47:21 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/10 18:21:53 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(int fd, unsigned int n, int *length)
{
	char	*nbr;
	int		status;

	nbr = ft_uitoa(n);
	status = ft_putstr(fd, nbr, length);
	free(nbr);
	return (status);
}

static int	print_hex(int fd, unsigned long long n, char cap, int *length)
{
	int	status;

	if (n / 16)
	{
		status = print_hex(fd, n / 16, cap, length);
		if (status == -1)
			return (-1);
	}
	if (n % 16 < 10 && ft_putchar(fd, (n % 16) + '0', length) == -1)
		return (-1);
	if (ft_putchar(fd, (n % 16) + (cap - 10), length) == -1)
		return (-1);
	return (1);
}

static int	format_handler(int fd, const char *format, va_list args, int *len)
{
	if (format[1] == 'c')
		return (ft_putchar(fd, (char)va_arg(args, int), len));
	if (format[1] == 's')
		return (ft_putstr(fd, va_arg(args, char *), len));
	if (format[1] == 'p')
	{
		if (ft_putstr(fd, "0x", len) != 1)
			return (-1);
		return (print_hex(fd, va_arg(args, unsigned long long), 'a', len));
	}
	if ((format[1] == 'd' || format[1] == 'i'))
		return (ft_putnbr(fd, va_arg(args, int), len));
	if (format[1] == 'u')
		return (ft_putunbr(fd, va_arg(args, unsigned int), len) == -1);
	if (format[1] == 'x')
		return (print_hex(fd, va_arg(args, unsigned int), 'a', len));
	if (format[1] == 'X')
		return (print_hex(fd, va_arg(args, unsigned int), 'A', len));
	else
		return (ft_putchar(fd, format[1], len));
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		length;

	va_start(args, format);
	i = 0;
	length = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format_handler(fd, &format[i], args, &length) == -1)
				return (-1);
			i++;
		}
		else if (format[i] != '%')
		{
			if (ft_putchar(fd, format[i], &length) == -1)
				return (-1);
		}
		i++;
	}
	va_end(args);
	return (length);
}
