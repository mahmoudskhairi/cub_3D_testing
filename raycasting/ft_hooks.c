/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:49 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/17 18:49:16 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"


int	collision_detected(t_map map, t_coor p_coor)
{
	if (map.grid[(int)(p_coor.y / TILE_SIZE)]
	&& map.grid[(int)(p_coor.y / TILE_SIZE)][(int)(p_coor.x / TILE_SIZE)] 
	&& map.grid[(int)(p_coor.y / TILE_SIZE)][(int)(p_coor.x / TILE_SIZE)] == '1')
		return (1);
	return (0);
}

void	key(void *dataa)
{
	t_data *data;

	data = (t_data *)dataa;
	t_coor next;

	next = data->player.coor;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle = ft_normalizer(data->player.angle + DEGREE);
		// printf("angle = %f\n", data->player.angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle = ft_normalizer(data->player.angle - DEGREE);
		// printf("angle = %f\n", data->player.angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{

		
		next.x = data->player.coor.x + cos(data->player.angle) * SPEED ;
		next.y = data->player.coor.y + sin(data->player.angle) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		next.x = data->player.coor.x - cos(data->player.angle) * SPEED ;
		next.y = data->player.coor.y - sin(data->player.angle) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		next.x = data->player.coor.x + cos(data->player.angle - DEGREE_90) * SPEED ;
		next.y = data->player.coor.y +  sin(data->player.angle - DEGREE_90) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		next.x = data->player.coor.x + cos(data->player.angle + DEGREE_90) * SPEED ;
		next.y = data->player.coor.y + sin(data->player.angle + DEGREE_90) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (!collision_detected(data->map, next))
		data->player.coor = next;
}
// printf("x = %f, y = %f\n", data->player.coor.x, data->player.coor.y);

void	ft_loop(void *dataa)
{
	t_data *data;

	data = (t_data *) dataa;
	cast_rays(data);
	key(dataa);
}
