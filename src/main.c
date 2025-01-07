/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:13:56 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:14:12 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//init map: all is NULL, no colors set
t_map	start_map(void)
{
	t_map	map;

	map.map = 0;
	map.no = 0;
	map.so = 0;
	map.we = 0;
	map.ea = 0;
	map.floor_color = -1;
	map.ceiling_color = -1;
	map.fc[0] = 0;
	map.max = 0;
	map.fc[1] = 0;
	return (map);
}

//init player data: top left position x/y
//no player yet
//direction is -1,0 (left, WEST)
//camera plane vector (plane): "perpendicular" 90 (up, Y)
t_player	start_player(void)
{
	t_player	player;

	player.pos.x = 0;
	player.pos.y = 0;
	player.nb = 0;
	player.dir.x = -1;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = 1;
	return (player);
}

//init general game data
t_data	general_data(t_map *map, t_player *player, mlx_t *mlx)
{
	t_data	data;

	data.player = player;
	data.map = map;
	data.mlx = mlx;
	data.width = WIDTH;
	data.height = HEIGHT;
	data.img = 0;
	return (data);
}
//image is changing all the time, it is not in data struct directly

int	main(int argc, char **argv)
{
	t_map		map;
	t_data		data;
	t_player	player;
	mlx_t		*mlx;

	if (argc != 2)
		return (ft_printf(2, ERR_ARGV), 0);
	mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!mlx)
		return (ft_printf(2, ERR_MLX), 0);
	map = start_map();
	player = start_player();
	data = general_data(&map, &player, mlx);
	input_check(argv[1], &data);
	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!data.img)
		free_all(ERR_MALLOC, 2, &data);
	raycast(&data);
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
		free_all(ERR_MLX, 2, &data);
	mlx_key_hook(mlx, &keypress, &data);
	mlx_resize_hook(mlx, &resize_window, &data);
	mlx_close_hook(mlx, &close_window, &data);
	mlx_loop(mlx);
	return (0);
}
