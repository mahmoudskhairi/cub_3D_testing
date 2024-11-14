/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:54:43 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/14 18:27:07 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void	ft_loop(void *data);
void	init_mlx_elements(t_data *data);

void	ll(void)
{
	// system("leaks -q cub3D | grep \'leaks for\' | awk \'{print $3 ,$4}\'");
	system("leaks -q cub3D");
}

void	clean_all(t_data *data)
{
	ft_free(data->map.grid);
	free(data->textures.NO);
	free(data->textures.SO);
	free(data->textures.WE);
	free(data->textures.EA);
	// system("leaks cub3D");
}

int main(int ac, char **av)
{
	t_data data;

	// atexit(ll);
	check_requirements(ac, av,&data);
	init_mlx_elements(&data);
	mlx_loop_hook(data.mlx, ft_loop, &data);
	printf("---->%s\n", data.textures.NO);
	printf("---->%s\n", data.textures.SO);
	printf("---->%s\n", data.textures.EA);
	printf("---->%s\n", data.textures.WE);

	mlx_loop(data.mlx);
	clean_all(&data);
}
