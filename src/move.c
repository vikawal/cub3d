/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:52:17 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:14:17 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//adjust the player’s direction vector & camera plane vector
// -> by a given angle (speed) by geomentry formula:
/*
    New X: x′=x⋅cos⁡(speed)−y⋅sin⁡(speed)x′=x⋅cos(speed)−y⋅sin(speed)
    New Y: y′=x⋅sin⁡(speed)+y⋅cos⁡(speed)y′=x⋅sin(speed)+y⋅cos(speed)*/
//NEW dir and plane, -> recalculate and redraw NEW scene 
void	rotate(double speed, t_data *data)
{
	double	old_x;
	double	old_y;

	old_x = data->player->dir.x;
	old_y = data->player->dir.y;
	data->player->dir.x = old_x * cos(speed) - old_y * sin(speed);
	data->player->dir.y = old_x * sin(speed) + old_y * cos(speed);
	old_x = data->player->plane.x;
	old_y = data->player->plane.y;
	data->player->plane.x = old_x * cos(speed) - old_y * sin(speed);
	data->player->plane.y = old_x * sin(speed) + old_y * cos(speed);
	raycast(data);
}

/*moving player with sp(eed) and direction vector:
(1,0)right, (−1,0)left, (0,1)down, (0,−1)up
Check the tiles slightly above and below player.
If both tiles are '0' (floor), update the player's pos
and raycast new view/position
!!!0.1 -> use for layer's "size" to prevent collisions with walls
!!!sp * 2 ->check  ahead of the player’s pos, according tospeed ->
NO moving into walls even at high speeds.
*/
void	move(t_data *data, double sp, t_vector v)
{
	int			sign;
	t_vector	pos;
	char		**map;

	sign = 0;
	map = data->map->map;
	pos = data->player->pos;
	if (fabs(v.x) == 1)
		sign = v.x;
	if (map[(int)(pos.y + sign * 0.1)][(int)(pos.x + v.x * sp * 2)] == '0'
		&& map[(int)(pos.y - sign * 0.1)][(int)(pos.x + v.x * sp * 2)] == '0')
		data->player->pos.x += v.x * sp;
	if (fabs(v.y) == 1)
		sign = v.y;
	if (map[(int)(pos.y + v.y * sp * 2)][(int)(pos.x + sign * 0.1)] == '0'
		&& map[(int)(pos.y + v.y * sp * 2)][(int)(pos.x - sign * 0.1)] == '0')
		data->player->pos.y += v.y * sp;
	raycast(data);
}

//keyhook options 
//negative - clockwise, positive - counterclockwise
void	keypress(mlx_key_data_t key, void *gdata)
{
	t_data	*data;

	data = gdata;
	if (key.key == MLX_KEY_ESCAPE)
		free_all("Game escaped\n", 1, data);
	else if (key.key == MLX_KEY_LEFT)
		rotate(RSPEED, data);
	else if (key.key == MLX_KEY_RIGHT)
		rotate(-RSPEED, data);
	else if (key.key == MLX_KEY_W)
		move(data, MSPEED, data->player->dir);
	else if (key.key == MLX_KEY_S)
		move(data, -MSPEED, data->player->dir);
	else if (key.key == MLX_KEY_A)
		move(data, -MSPEED, data->player->plane);
	else if (key.key == MLX_KEY_D)
		move(data, MSPEED, data->player->plane);
}

//cleaning when closing
void	close_window(void *gdata)
{
	t_data	*data;

	data = gdata;
	free_all("Game closed\n", 1, data);
}

//resize window hook
void	resize_window(int32_t width, int32_t height, void *gdata)
{
	t_data	*data;

	data = gdata;
	data->width = width;
	data->height = height;
	raycast(data);
}
