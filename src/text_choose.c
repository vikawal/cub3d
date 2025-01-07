/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_choose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:59:43 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/17 16:52:31 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*rc->ipos:grid cell where the wall was hit.
data->player->pos: The player's current pos.
rc->side: wall hit is vert(0) or horiz(1)
Textures of East, West, North, South).*/

void	choose_texture_ptr(t_data *data, t_raycast *rc)
{
	if (rc->ipos.x >= data->player->pos.x && rc->side == 0)
	{
		rc->t = data->map->we;
	}
	if (rc->ipos.x < data->player->pos.x && rc->side == 0)
	{
		rc->t = data->map->ea;
	}
	if (rc->ipos.y >= data->player->pos.y && rc->side == 1)
	{
		rc->t = data->map->so;
	}
	if (rc->ipos.y < data->player->pos.y && rc->side == 1)
	{
		rc->t = data->map->no;
	}
}
