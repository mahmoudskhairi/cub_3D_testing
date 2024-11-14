/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:19:17 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/10/30 19:31:42 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void mini_map(t_data *data)
{
	double x;
	double y;
	
	// y = 0;
	// while(y < MINI_HEIGHT + 3)
	// {
	// 	x = 0;
	// 	while(x < MINI_WIDTH + 3)
	// 	{
	// 		if (x >= 20 * TILE_SIZE || y >= 10 * TILE_SIZE || x <= 3 || y <= 3)
	// 			my_mlx_put_pixel(data, data->ft_3D, (t_coor){x, y}, get_rgba(0, 5, 5, 255));
	// 		else
	// 			my_mlx_put_pixel(data, data->ft_3D, (t_coor){x, y}, get_rgba(200, 215, 255, 255));
	// 		x++;
	// 	}
	// 	y++;
	// }
	y = data->player.coor.y / TILE_SIZE;
	x = data->player.coor.x / TILE_SIZE;
	// printf("y = %f, x = %f\n", y, x);
	double a = y + 5;
	y -= 5;
	while (y < a)
	{ 
		x = data->player.coor.x / TILE_SIZE;
		double z = x + 10;
			x -= 10;
		while (x < z)
		{
			if (x >= 0 && x < data->map.width && y >= 0 && y < data->map.heigth)
				draw_tile(data, (x + 10) * TILE_SIZE - data->player.coor.x,
					(y + 5)* TILE_SIZE - data->player.coor.y, data->map.grid[(int)y][(int)x], data->ft_3D);
			x++;
		}
		y++;
	}
	draw_player(data, (t_coor){10 * TILE_SIZE + fmod (data->player.coor.x, TILE_SIZE),
		5 * TILE_SIZE + fmod (data->player.coor.y, TILE_SIZE)}, data->ft_3D);
}
