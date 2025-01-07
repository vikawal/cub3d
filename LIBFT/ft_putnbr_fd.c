/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:14:56 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/10 18:27:47 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	if (num / 10)
	{
		ft_putnbr_fd((num / 10), fd);
		ft_putnbr_fd((num % 10), fd);
	}
	else
	{
		ft_putchar_fd(('0' + num), fd);
	}
}

int	ft_putnbr(int fd, int n, int *length)
{
	char	*nbr;
	int		status;

	nbr = ft_itoa(n);
	status = ft_putstr(fd, nbr, length);
	free(nbr);
	return (status);
}

static int	ft_unbrlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i <= ((len - 1) / 2))
	{
		tmp = str[len - i];
		str[len - i] = str[i];
		str[i] = tmp;
		i++;
	}
	return (str);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_unbrlen(n) + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}

// void	ft_putnbr_fd(int n, int fd)
// {
// 	int	sign;

// 	sign = 1;
// 	if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		sign = -1;
// 	}
// 	if (n / 10)
// 	{
// 		ft_putnbr_fd((n / 10) * sign, fd);
// 		ft_putnbr_fd((n % 10) * sign, fd);
// 	}
// 	else
// 	{
// 		ft_putchar_fd(('0' + n) * sign, fd);
// 	}
// }