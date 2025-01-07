/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:32:10 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/10 18:02:21 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_putstr(int fd, char *str, int *length)
{
	int	status;

	if (str == NULL)
		return (ft_putstr(fd, "(null)", length));
	while (*str)
	{
		status = ft_putchar(fd, *str++, length);
		if (status != 1)
			return (status);
	}
	return (status);
}

// int main(void)
// {
// 	char a[] = "Hello, I am a happy healthy string! Who are you?";
// 	ft_putstr_fd(a, 2);
// 	return(0);
// }