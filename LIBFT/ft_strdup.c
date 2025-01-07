/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:31:39 by vmyshko           #+#    #+#             */
/*   Updated: 2024/11/29 13:35:33 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	length;

	length = ft_strlen(s) + 1;
	dest = malloc(length);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s, length);
	return (dest);
}

// int main ()
// {
// 	char src[] = "Hello, strdup!";
// 	char *result_1 = ft_strdup(src);
// 	char *result_2 = strdup(src);
// 	printf("Start string: %s\n", src);
// 	printf("My strdup: %s\n", result_1);
// 	printf("Original strdup: %s\n", result_2);
// 	free(result_1);
// 	free(result_2);
// 	return (0);
// }

//for get_next_line
// char	*ft_strdup(char *s)
// {
// 	size_t	len;
// 	char	*dup;
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	len = ft_strlen(s);
// 	dup = (char *)malloc((len + 1) * sizeof(char));
// 	if (!dup)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[len] = '\0';
// 	return (dup);
// }