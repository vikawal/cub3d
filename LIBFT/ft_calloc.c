/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:18:33 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/10 17:56:27 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include "libft.h"
#include <stdint.h>
/*for libft*/
// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*pointer;

// 	if (nmemb > 0 && SIZE_MAX / nmemb < size)
// 		return (0);
// 	pointer = malloc(nmemb * size);
// 	if (!pointer)
// 		return (0);
// 	ft_bzero(pointer, (nmemb * size));
// 	return (pointer);
// }

//if (nmemb > 0 && (size_t)1 << 40 / nmemb < size)
// int main()
// {
// int *arr_calloc = (int *)ft_calloc(5, sizeof(int));
// for(int i = 0; i<5; i++)
// printf("%d", arr_calloc[i]);
// printf("\n");
// free(arr_calloc);
// return (0);
// }

/* for get_next_line*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;
	size_t	i;

	i = 0;
	if (nmemb > 0 && SIZE_MAX / nmemb < size)
		return (NULL);
	pointer = malloc(nmemb * size);
	if (!pointer)
		return (0);
	while (i < nmemb * size)
	{
		*((unsigned char *)pointer + i) = '\0';
		i++;
	}
	return (pointer);
}
