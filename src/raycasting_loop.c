/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:21:54 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:42:18 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*uint8_t *pixel: A pointer to an array of 4 uint8_t values: 
the components of the color:
    pixel[0]: The alpha channel (transparency).
    pixel[1]: The red channel.
    pixel[2]: The green channel.
    pixel[3]: The blue channel.
	we add alpha, red, green and bule channels*/
static int	create_color(uint8_t *pixel)
{
	int	rgba;

	rgba = 0;
	rgba += pixel[0] << 24;
	rgba += pixel[1] << 16;
	rgba += pixel[2] << 8;
	rgba += pixel[3];
	return (rgba);
}
/*Example: {255, 100, 150, 200} -> rgba = 0xFF6496C8
    rgba = 255 << 24 = 0xFF000000
    rgba = 0xFF000000 + (100 << 16) = 0xFF640000
    rgba = 0xFF640000 + (150 << 8) = 0xFF649600
    rgba = 0xFF649600 + 200 = 0xFF6496C8
.*/

/*step: how much the texture coordinate tex_pos should advance 
with each pixel in the vertical line: maps the texture height 
proportionally to the vertical line height on the screen..*/
/*tex_pos: The starting position in the texture for the 
vertical line being drawn: aligns the texture mapping with 
the middle of the vertical wall slice*/
/* y = The current pixel row on the screen being processed.*/
/*portion of the screen corresponding to the wall slice being drawn.*/

/*calculate the Y coordinate in the texture for the current screen pixel:
texture wraps correctly (bitwise AND with (height - 1):
power-of-2 texture dimensions).
move to next texture row and calculate the index in the texture's pixel
array based on the current texture coordinates->tex.x and tex.y
and draw it
*/
static void	ray_to_img(t_data *data, t_raycast *rc)
{
	double		step;
	double		tex_pos;
	uint32_t	color;
	int			y;

	step = 1.0 * data->map->no->height / rc->line_height;
	tex_pos = (rc->draw_start - data->height / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y <= rc->draw_end)
	{
		rc->tex.y = (int)tex_pos & (data->map->no->height - 1);
		tex_pos += step;
		color = create_color((uint8_t *)&((uint32_t *)rc->t->pixels)
			[rc->t->width * rc->tex.y + (rc->t->width - rc->tex.x - 1)]);
		mlx_put_pixel(data->img, rc->x, y, color);
		y++;
	}
}

/*find screen coordinates needed to render a vertical line Y
(representing a wall slice in sector start-end) 
height: closer->bigger
The wall slice is centered vertically around the middle of the screen
It doesn't exceed the screen's boundaries, avoiding mistakes*/
static void	get_screen_coord(t_data *data, t_raycast *rc)
{
	rc->line_height = (int)(data->height / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + data->height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + data->height / 2;
	if (rc->draw_end >= data->height)
		rc->draw_end = data->height - 1;
}

/*calculate the texture coordinate for a wall hit in the raycasting
wall_x: the exact position on the wall where the ray hit:
x (hit on a horizontal side (1) or y (side==0)?
Subtracting the int part (floor(wall_x)) to isolates the fract part 
of the hit position -> to map the hit position to a texture coordinate.
 Convert wall_x to a Texture Coordinate:
texture mirror:
vertical side(0) ->ray moving right -> texture mirrored horizontally
horizontal side(1) -> ray moving up -> texture mirrored vertically
.*/
static void	get_tex_coord(t_data *data, t_raycast *rc)
{
	double	wall_x;

	if (rc->side == 0)
		wall_x = data->player->pos.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		wall_x = data->player->pos.x + rc->perp_wall_dist * rc->ray_dir.x;
	wall_x -= floor((wall_x));
	rc->tex.x = (int)(wall_x * (double)(rc->t->width));
	if (rc->side == 0 && rc->ray_dir.x > 0)
		rc->tex.x = rc->t->width - rc->tex.x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		rc->tex.x = rc->t->width - rc->tex.x - 1;
}

//MAIN LOOP!
/*1. Shoots one ray per screen column to each column
2. check where ray hits a horiz/vertical wall
3. height of the wall on the screen
4. draw texture*/
void	raycast(t_data *data)
{
	t_raycast	rc;

	resize_render(data);
	draw_ceiling_floor(data);
	rc.x = 0;
	while (rc.x < data->width)
	{
		init_ray_param(data, &rc);
		step_init(data, &rc);
		dda(data, &rc);
		if (rc.side == 0)
			rc.perp_wall_dist = (rc.side_dist.x - rc.delta_dist.x);
		else
			rc.perp_wall_dist = (rc.side_dist.y - rc.delta_dist.y);
		get_screen_coord(data, &rc);
		choose_texture_ptr(data, &rc);
		get_tex_coord(data, &rc);
		ray_to_img(data, &rc);
		rc.x += 1;
	}
}
