/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:18:48 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/10 18:00:40 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

//for libft

// char	*ft_strchr(const char *s, int c)
// {
// 	unsigned char	char_c;

// 	char_c = (unsigned char)c;
// 	while (*s != char_c)
// 	{
// 		if (*s == '\0')
// 			return (0);
// 		s++;
// 	}
// 	return ((char *)s);
// }
// int main()
// {
// 	char test_string[] = "Hello, abc";
// 	char *test = test_string;
// 	int c = 'b';
// 	char *result = ft_strchr(test, c);
// 	if (result)
// 	{
// 		printf("character %c found at position %p\n", c, result);
// 	}
// 	else
// 	{
// 		printf("character %c NOT found\n", c);
// 	}
// 	char *result_1 = strchr(test, c);
// 	if (result)
// 	{
// 		printf("character %c found at position %p\n", c, result_1);
// 	}
// 	else
// 	{
// 		printf("character %c NOT found\n", c);
// 	}
// 	return(0);
// }

/*for get_next_line */
char	*ft_strchr(const char *s, int c)
{
	unsigned char	char_c;

	char_c = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	while (*s != char_c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
