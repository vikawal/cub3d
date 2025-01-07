/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:04:00 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:14:36 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//calculate the length of an array of strings
int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

///join two arrays of strings
char	**ft_arrayjoin(char **old, char **new, int size_new)
{
	char	**new_array;
	int		i;
	int		j;

	if (!old)
		return (NULL);
	new_array = malloc((ft_strslen(old) + size_new + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new_array[i] = old[i];
		i++;
	}
	j = 0;
	while (j < size_new)
	{
		new_array[i] = new[j];
		i++;
		j++;
	}
	new_array[i] = 0;
	return (new_array);
}
