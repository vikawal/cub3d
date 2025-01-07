/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vmyshko <vmyshko@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 19:30:57 by vmyshko       #+#    #+#                 */
/*   Updated: 2024/12/17 12:16:11 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include "stdio.h"
// #include <string.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int	is_whitespace(char *line)
{
	while (*line)
	{
		if (!(*line == ' ' || *line == '\t' || *line == '\n'))
		{
			return (0);
		}
		line++;
	}
	return (1);
}
