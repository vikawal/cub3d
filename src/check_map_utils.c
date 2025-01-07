/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:33:36 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:14:04 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//if a given character c is present in the string sep
static int	is_separator(char c, char *sep)
{
	return (ft_strchr(sep, c) != NULL);
}

//calculates the number of substrings in the input string 
//that are separated by any character in the string sep
static int	word_count(char *str, char *sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && is_separator(str[i], sep))
			i++;
		if (str[i])
			len++;
		while (str[i] && !is_separator(str[i], sep))
			i++;
	}
	return (len);
}

//count the size of the "word" at the beginning of the string, 
//where "word"is defined as a sequence of characters not in sep
static int	get_word_length(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && !is_separator(str[i], sep))
		i++;
	return (i);
}

void	free_split(char **array, int len)
{
	int	i;

	i = 0;
	while (array[i] || (i != -1 && i < len))
		free(array[i++]);
	free(array);
}

//split
//"F 220,100,200\n" -> "F" "220,100,200"
char	**my_split(char *str, char *sep)
{
	char	**array;
	char	*word;
	int		i;

	array = malloc(sizeof(char *) * (word_count(str, sep) + 1));
	i = 0;
	if (!array)
		return (NULL);
	while (*str)
	{
		while (*str && is_separator(*str, sep))
			str++;
		if (!(*str))
			break ;
		word = ft_substr(str, 0, get_word_length(str, sep));
		if (!word)
			return (free_split(array, i), NULL);
		while (*str && !is_separator(*str, sep))
			str++;
		array[i++] = word;
	}
	array[i] = NULL;
	return (array);
}
