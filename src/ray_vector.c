/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:16:50 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:14:22 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//when screen/window is changed, we resize it
void	resize_render(t_data *data)
{
	static int	width = WIDTH;
	static int	height = HEIGHT;

	if (width != data->width || height != data->height)
	{
		mlx_delete_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, data->width, data->height);
		if (!data->img)
			free_all(ERR_MALLOC, 2, data);
		if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
			free_all(ERR_MLX, 2, data);
		width = data->width;
		height = data->height;
	}
}

/*buff = pointer to the pixel buffer of the image. 
-> holds the pixel data for the entire image.
size_buff = stores the total number of pixels in the image
upper part of image (ceiling) -> ceiling color
lower -> floor color
*/
void	draw_ceiling_floor(t_data *data)
{
	uint32_t	*buff;
	int			size_buff;
	int			i;

	i = 0;
	size_buff = (data->img->width * data->img->height);
	buff = (uint32_t *)data->img->pixels;
	while (i < size_buff / 2)
	{
		buff[i] = data->map->ceiling_color;
		i++;
	}
	while (i < size_buff)
	{
		buff[i] = data->map->floor_color;
		i++;
	}
}

/*1)camera_x -> horizontal position of the ray on the screen (-1-1). 
Calculated for each pixel (rc->x) on the screen width (data->width)
2)direction of the ray based on the player's direction and plane.
3)calculate ray step size (delta_dist): how far the ray moves 
in each direction for every iteration.
if it is 0 -> ray is moving along a straight line parallel to that axis)
-> delta distance is set big (1e30) to avoid :0 problem
if it is !=0 -> delta is calculated as the inverse of the ray's 
direction, and fabs() ->result is positive.
*/
void	init_ray_param(t_data *data, t_raycast *rc)
{
	double		camera_x;

	camera_x = 2 * rc->x / (double) data->width - 1;
	rc->ray_dir.x = data->player->dir.x + data->player->plane.x * camera_x;
	rc->ray_dir.y = data->player->dir.y
		+ data->player->plane.y * camera_x;
	rc->ipos.x = (int)data->player->pos.x;
	rc->ipos.y = (int)data->player->pos.y;
	if (rc->ray_dir.x == 0)
		rc->delta_dist.x = DOFIGA;
	else
		rc->delta_dist.x = fabs(1 / rc->ray_dir.x);
	if (rc->ray_dir.y == 0)
		rc->delta_dist.y = DOFIGA;
	else
		rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
}

/*stepping parameters and distances to the nearest grid boundary:
step.x/y -> direction in which the ray moves (+1/-1 for x/y)
side_dist.x/y -> distance start pos of the ray -> 
1st grid boundary in the x and y directions*/
/*first ray goes left, then right, down and up:
(side_dist.x) = distance from the player's current X position 
(data->player->pos.x)to left edge of the current grid cell(rc->ipos.x) 
then multiplied by delta_dist.x to normalize it into the ray’s world 
distance to use in DDA algorithm.*/
void	step_init(t_data *data, t_raycast *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (data->player->pos.x - rc->ipos.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (rc->ipos.x + 1.0 - data->player->pos.x)
			* rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (data->player->pos.y - rc->ipos.y)
			* rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (rc->ipos.y + 1.0 - data->player->pos.y)
			* rc->delta_dist.y;
	}
}

/*Digital Differential Analysis:
trace a ray through a grid-based map. 
-> determine the point where the ray gets a wall (1)
 go through the grid cell by cell -> where the ray 
 will hit the next vertical (0)/horizontal(1) grid line.
 -> exact grid cell containing the wall is identified*/
void	dda(t_data *data, t_raycast *rc)
{
	while (1 != 0)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->ipos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->ipos.y += rc->step.y;
			rc->side = 1;
		}
		if (data->map->map[rc->ipos.y][rc->ipos.x] == '1')
			return ;
	}
}
