/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:28:33 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:14:08 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//validation of file name
static void	check_name(char *map_name)
{
	if (ft_strlen(map_name) < 5)
	{
		ft_printf(2, ERR_FILENAME);
		exit (0);
	}
	if (ft_strncmp(&map_name[ft_strlen(map_name) - 4], ".cub", 4)
		|| map_name[ft_strlen(map_name) - 5] == '.')
	{
		ft_printf(2, ERR_FILEEXTENSION);
		exit (0);
	}
}

//check startposition of player to put his direction
//place player on the center of the tile
//check if there's only 1 player
//make player's position 0 = FLOOR (update map)
//check forbidden chars (only 1 and 0 and empty are in map now)
static void	check_player_pos(t_data *data, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		data->player->pos.x = x + 0.5f;
		data->player->pos.y = y + 0.5f;
		data->player->nb++;
		data->map->map[y][x] = '0';
		if (c == 'N')
			fill_player_infos(data, (double []){0, -1}, (double []){-1, 0});
		else if (c == 'S')
			fill_player_infos(data, (double []){0, 1}, (double []){1, 0});
		else if (c == 'E')
			fill_player_infos(data, (double []){-1, 0}, (double []){0, 1});
		else if (c == 'W')
			fill_player_infos(data, (double []){1, 0}, (double []){0, -1});
	}
	else if (c != '0' && c != '1' && c != ' ')
		free_all(ERR_FORBIDDENCHAR, 2, data);
}

//checking line by line that map is closed:
/*check whether the current character is either :
a wall ('1'), a floor ('0'), or the player  ('N', 'S', 'E', 'W').
-> check if map is closed: are we in 1st/last row/column?
-> check empty spaces around: above, below, left, right
*/
static void	check_boarders(char *line, t_data *data, t_map *map, int i)
{
	size_t	j;

	j = 0;
	while (line[j])
	{
		check_player_pos(data, line[j], i, j);
		if (line[j] == '0' || line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'W' || line[j] == 'E')
		{
			if (j == 0 || j == data->map->max - 1
				|| i == 0 || i == ft_strslen(map->map) - 1)
				free_all(ERR_MAPNOTCLOSED, 2, data);
			if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
				|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
				free_all(ERR_MAPNOTCLOSED, 2, data);
		}
		j++;
	}
}

//fill map with lines ansd reverse them to make it easier to check
// map will be read from right to left (raycasting logic)
//check player == 1
static void	check_map(t_data *data, t_map *map)
{
	int		i;

	i = 0;
	while (map->map[i])
	{
		map->map[i] = fill_line(data, map->map[i]);
		map->map[i] = ft_strrev(map->map[i]);
		i++;
	}
	i = 0;
	while (map->map[i])
	{
		check_boarders(map->map[i], data, map, i);
		i++;
	}
	if (data->player->nb == 0)
		free_all(ERR_NOPLAYER, 2, data);
	if (data->player->nb > 1)
		free_all(ERR_MANYPLAYERS, 2, data);
}

//parsing it all together to check the input is ok
int	input_check(char *map_name, t_data *data)
{
	int		fd;
	char	*line;

	check_name(map_name);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (perror("cub3d"), free_all(0, 0, data), 1);
	get_infos(fd, data);
	check_map(data, data->map);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_whitespace(line))
		{
			free(line);
			continue ;
		}
		free(line);
		free_all(ERR_EXTRA_CONTENT, 2, data);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
