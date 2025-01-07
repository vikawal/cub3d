/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:15:08 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:14:41 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//initialize the player's directional vector (dir) 
//and camera plane vector (plane) in the t_data struct.
/*In the standard Cartesian coordinate system used in games, 
the positive y-axis points down (not up, as in math).
    dir = {0, -1} means the player is facing directly upward (northward).
    {1, 0} would mean facing right (east), 
	{0, 1} means downward (south), 
	and {-1, 0} means left (west).*/

/*The plane vector defines the camera plane for the player's field of view(FOV)
It is perpendicular to the dir vector. What Does the Plane Do?
The camera plane determines the area of the game world visible to the player.
It stretches out in a direction perpendicular to the player's dir vector and 
sets the bounds for the field of view.*/

/*The plane vector is usually chosen as a small fraction of a unit vector 
(like 0.66) to determine the player's field of view (FOV).
A value of 0.66 corresponds to a FOV of about 66 degrees(common FOV for games)
A smaller plane vector narrows the FOV. A larger plane vector widens the FOV.*/

/*The plane vector is always perpendicular to the dir vector:
If the player is facing north (dir = {0, -1}), the camera plane is horizontal 
(plane = {0.66, 0}).
If the player turns east (dir = {1, 0}), the plane becomes vertical 
(plane = {0, 0.66}).*/

//foundational for raycasting, to calculate the direction of rays 
//that simulate vision and render the game world on the screen.
void	fill_player_infos(t_data *data, double dir[2], double plane[2])
{
	data->player->dir.x = dir[0];
	data->player->dir.y = dir[1];
	data->player->plane.x = plane[0];
	data->player->plane.y = plane[1];
}

// Tracks how many times the floor (F) and ceiling (C) 
// colors are set in the map configuration.
void	add_color(char t, t_data *data)
{
	if (t == 'C')
		data->map->fc[1]++;
	else if (t == 'F')
		data->map->fc[0]++;
}

//Extracts and duplicates a substring from a given string 
//starting at a specific index, stopping at the first space or newline
char	*strdup_to(char *line, int start)
{
	char	*path;
	int		j;

	j = 0;
	while (line[start] && line[start] == ' ')
		start++;
	path = malloc(ft_strlen(line) - start + 1);
	if (!path)
		return (NULL);
	while (line[start] && line[start] != '\n' && line[start] != ' ')
		path[j++] = line[start++];
	path[j] = 0;
	return (path);
}

//Pads a map row with spaces to ensure all rows are of the same width
char	*fill_line(t_data *data, char *str)
{
	size_t	i;
	char	*s;

	s = malloc(data->map->max + 1);
	if (!s)
		free_all(ERR_MALLOC, 2, data);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		if (s[i] == '\n')
			s[i] = ' ';
		i++;
	}
	while (i < data->map->max)
		s[i++] = ' ';
	s[i] = 0;
	free(str);
	return (s);
}

//Frees all dynamically allocated resources in the t_data structure 
//and exits the program.
void	free_all(char *str, int out, t_data *data)
{
	int	i;

	i = 0;
	if (out == 2)
		ft_printf(out, "Error\n");
	if (str)
		ft_printf(out, "%s\n", str);
	if (data->map->map)
		while (data->map->map[i])
			free(data->map->map[i++]);
	free(data->map->map);
	if (data->map->no)
		mlx_delete_image(data->mlx, data->map->no);
	if (data->map->so)
		mlx_delete_image(data->mlx, data->map->so);
	if (data->map->we)
		mlx_delete_image(data->mlx, data->map->we);
	if (data->map->ea)
		mlx_delete_image(data->mlx, data->map->ea);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit (0);
}
