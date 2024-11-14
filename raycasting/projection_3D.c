/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_3D.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:16:43 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/14 19:02:10 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	dda(t_data *data, t_coor a, t_coor b, int color, mlx_image_t *img)
{
	int step;
	double dx;
	double dy;

	double xinc;
	double yinc;

	dy = b.y - a.y;
	dx = b.x - a.x;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	xinc = dx / step;
	yinc = dy / step;
	int i = 0;
	while (i <= step)
	{
		my_mlx_put_pixel(data, img,(t_coor){a.x , a.y}, color);
		a.x += xinc;
		a.y += yinc;
		i++;
	}
}
t_coor	first_h_inter(double angle, t_coor player)
{
	t_coor first_h;
	
	angle = ft_normalizer(angle);
	if (angle >= 0 && angle <= M_PI)// down
		first_h.y = floor(player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else if (angle > M_PI && angle < 2 * M_PI) // up
		first_h.y = floor(player.y / TILE_SIZE) * TILE_SIZE - 0.001;
	first_h.x = (first_h.y - player.y) / tan(angle) + player.x;
	return (first_h);
}

t_coor	first_v_inter(double angle, t_coor player)
{
	t_coor first_v;

	if (angle >= M_PI / 2 && angle <= 1.5 * M_PI)//left
		first_v.x = (int)(player.x / TILE_SIZE) * TILE_SIZE - 0.001;
	else if (angle >= 1.5 * M_PI || angle <= M_PI / 2)// right
		first_v.x = (int)(player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	
	first_v.y = player.y + tan(angle) * (first_v.x - player.x);
	return (first_v);
}

t_coor h_wall_detect(t_map map, t_coor first, double angle)
{
	t_coor hit;
	int i;
	int	x;
	int y;

	angle = ft_normalizer(angle);
	i = 0;
	hit.x = first.x;
	hit.y = first.y;
	while (i <= map.heigth)
	{
		x = (int)(hit.x / TILE_SIZE);
		y = (int)((hit.y) / TILE_SIZE);
		if (x >= 0 && y >= 0 && x < map.width && y < map.heigth && map.grid[y][x] == '1')
			return (hit);
		if (angle >= 0 && angle < M_PI)// down
		{
			hit.y += TILE_SIZE;
			hit.x += (TILE_SIZE) / tan(angle);
			
		}
		else // up
		{
			hit.y -= TILE_SIZE;
			hit.x -= TILE_SIZE / tan(angle);
		}
		
		i++;
	}
	return (hit);
}

t_coor v_wall_detect(t_map map, t_coor first, double angle)
{
	t_coor hit;
	int i;
	int	x;
	int y;

	i = 0;
	hit.x = first.x;
	hit.y = first.y;
	while (i <= map.width)
	{
		x = (int)(hit.x / TILE_SIZE);
		y = (int)(hit.y / TILE_SIZE);
		if (x >= 0 && x < map.width && y >= 0 && y < map.heigth && map.grid[y][x] == '1')
			return (hit);
		if (angle > M_PI / 2 && angle < 1.5 * M_PI) // left
		{
			hit.x -= TILE_SIZE;
			hit.y -= TILE_SIZE * tan(angle);
		}
		else //if (angle > 1.5 * M_PI || angle < M_PI / 2) // right
		{
			hit.x += TILE_SIZE;
			hit.y += TILE_SIZE * tan(angle);
		}
		i++;
	}
	return (hit);
}

t_coor	ft_compare(t_coor player, t_coor h, t_coor v, t_ray *ray)
{
	double PH;
	double PV;

	PH = sqrt(pow(h.y - player.y, 2)+ pow(h.x - player.x, 2));
	PV = sqrt(pow(v.y - player.y, 2)+ pow(v.x - player.x, 2));

	if (PV <= PH)
	{
		ray->distance = PV;
		ray->flag = 'v';
		return (v);
	}
	else
	{
		ray->distance = PH;
		ray->flag = 'h';
		return (h);
	}
}
int gett_rgba(uint8_t *color)
{
    return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}
void	draw_columns(t_data *data, t_ray *ray, double angle, int x, int y)
{
	// mlx_image_to_window(data->mlx, data->ft_3D, 0 , 0);
	int x_of_texture;
	int y_of_texture;
	double	projection_column;
	double	projection_distance;
	(void)x;
	(void)y;
	ray->distance *= cos(data->player.angle - angle);
	projection_distance = WIDTH / 2 * tan(FOV / 2);                                                                                                                   
	projection_column = (TILE_SIZE * projection_distance) / ray->distance;
	ray->top = (HEIGHT / 2) - (projection_column / 2);
	ray->bottom = (HEIGHT / 2) + (projection_column / 2);
	x_of_texture = ray->Wall_hit.x * data->img1->width / WIDTH;
	y_of_texture = ray->Wall_hit.y * data->img1->height / HEIGHT;
	while (ray->top <= ray->bottom )//&& y < (int)data->img2->height
	{
		// if ((sin(angle) <= 0 && ray->flag == 'h'))//----->buttom
		// {
		// 	// printf("1\n");
		// 	if (ray->top >= 0 && ray->top < HEIGHT)
		// 	{
		// 		// if (ray->flag == 1)
		// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(255, 0, 0, 255));//red
		// 		// else if(ray->flag == 2)
		// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(120,120,120, 255));
		// 	}
		// }
		if ((sin(angle) <= 0 && ray->flag == 'h'))//----->buttom
		{
			// printf("1\n");
			if (ray->top >= 0 && ray->top < HEIGHT)
			{
				//get position from image x and y
				//put_pixel
					// x_of_texture = ray->Wall_hit.x * data->img1->width / WIDTH;
					mlx_put_pixel(data->ft_3D, data->x_projection, ray->top, gett_rgba(&data->img2->pixels[(x_of_texture * data->img2->width + x_of_texture) * 4]));//pixel from image
					y_of_texture++;
				// else if(ray->flag == 2)
					// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(120,120,120, 255));
			}
		}
		if ((sin(angle) >= 0 && ray->flag == 'h'))//top
		{
			// printf("%f\n", angle);
			// (sin(data->first_player_angle) > (sqrt(2) / 2) && !(cos(data->player.angle) < -(sqrt(2) / 2) && cos(data->player.angle) > (sqrt(2) / 2)))
			if (ray->top >= 0 && ray->top < HEIGHT)
			{
				// if (ray->flag == 1)
				// 	mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(196, 153, 231, 255));
				// else if(ray->flag == 2)
					mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(70, 67, 65, 255));//gray
				
			}
		}
		if ((cos(angle) >= 0 && ray->flag == 'v'))// ----->right
		{	
				// printf("hello\n");
			// printf("2\n");
			if (ray->top >= 0 && ray->top < HEIGHT)
			{
				// if (ray->flag == 1)
					mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(13, 0, 255, 255));//blue
				// 	mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(0, 0, 255, 255));
				// else if(ray->flag == 2)
			}
			
		}
		if (cos(angle) <= 0  && ray->flag == 'v')// ----->left
		{
			// printf("3\n");
			if (ray->top >= 0 && ray->top < HEIGHT)
			{
				// if (ray->flag == 1)
				// 	mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(10,99,71, 255));
				// else if(ray->flag == 2)
					mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(249, 143, 13, 255));//orange
			}
		}
		ray->top++;
	}
	// if (sin(data->player.angle) > - (sqrt(2) / 2) && (cos(data->player.angle) > -(sqrt(2) / 2) && cos(data->player.angle) < (sqrt(2) / 2)))
	// {
	// 	while (ray->top <= ray->bottom )//&& y < (int)data->img2->height
	// 	{
	// 		if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 1)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(60,60,60, 255));
	// 		else if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 2)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(120,120,120, 255));
	// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top, gett_rgba(&data->img2->pixels[(y * data->img2->width + x) * 4]));
	// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(255, 0, 0, 255));
	// 		ray->top++;
	// 		y++;
	// 	}
	// }
	// else if (cos(data->player.angle) >  (sqrt(2) / 2) && !(sin(data->player.angle) > (sqrt(2) / 2) && sin(data->player.angle) < -(sqrt(2) / 2)))
	// {
	// 	printf("--->>>> %f \n", data->player.angle * 180 / M_PI);
	// 	while (ray->top <= ray->bottom )//&& y < (int)data->img2->height
	// 	{
	// 		if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 1)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(0, 0, 255, 255));
	// 		else if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 2)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(106, 90, 205, 255));
	// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top, gett_rgba(&data->img2->pixels[(y * data->img2->width + x) * 4]));
	// 		ray->top++;
	// 		y++;
	// 	}
	// }
	// else if (cos(data->player.angle) < -(sqrt(2) / 2) && !(sin(data->player.angle) > (sqrt(2) / 2) && sin(data->player.angle) < -(sqrt(2) / 2)))
	// {
	// 	while (ray->top <= ray->bottom )//&& y < (int)data->img2->height
	// 	{
	// 		if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 1)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(10,99,71, 255));
	// 		else if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 2)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(10,153,71, 255));
	// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top, gett_rgba(&data->img2->pixels[(y * data->img2->width + x) * 4]));
	// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(255, 0, 0, 255));
	// 		ray->top++;
	// 		y++;
	// 	}
	// }
	// else if (sin(data->first_player_angle) > (sqrt(2) / 2) && !(cos(data->player.angle) < -(sqrt(2) / 2) && cos(data->player.angle) > (sqrt(2) / 2)))
	// {
	// 	while (ray->top <= ray->bottom )//&& y < (int)data->img2->height
	// 	{
	// 		if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 1)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(196, 153, 231, 255));
	// 		else if (ray->top >= 0 && ray->top < HEIGHT && ray->flag == 2)
	// 			mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(255, 153, 231, 255));
	// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top, gett_rgba(&data->img2->pixels[(y * data->img2->width + x) * 4]));
	// 			// mlx_put_pixel(data->ft_3D, data->x_projection, ray->top , get_rgba(255, 0, 0, 255));
	// 		ray->top++;
	// 		y++;
	// 	}
	// }
}

void	projection_3D(t_data *data)
{
	t_coor first_h;
	t_coor first_v;
	static int x = 0;
	static int y = 0;
	// (void)x;
	// (void)y;
	// printf("rays number is %d\n", N_RAYS);
	data->rays = malloc(N_RAYS * sizeof(t_ray));
	double angle = data->player.angle - FOV / 2;
	int i = 0;
	data->x_projection = 0;
	while (i < N_RAYS)// casting rays depened of player angle
	{
		y = 0;
		first_h = first_h_inter(angle, data->player.coor);
		first_v = first_v_inter(angle, data->player.coor);
		t_coor hit_h = h_wall_detect(data->map, first_h, angle);
		t_coor hit_v = v_wall_detect(data->map, first_v, angle);
		// t_coor small_d = ft_compare(data->player.coor, hit_h, hit_v);

		data->rays[i].Wall_hit = ft_compare(data->player.coor, hit_h, hit_v, &(data->rays[i]));
		// dda(data, data->player.coor, data->rays[i].Wall_hit, get_rgba(10, 100, 10, 255), data->map.img);
		// printf("distance = %f\n", data->rays[i].distance);
		draw_columns(data, &data->rays[i], angle, x, y);
		data->x_projection++;
		angle += RAY_ANGLE_INC;
		// printf("%f\n", data->player.angle);
		// printf("ray nbr -> %d\n", i);
		i++;
		x++;
		// if (x == N_RAYS / 2)
		// 	x = 0;
	}
	// dda(data, data->player.coor, (t_coor){data->player.coor.x + cos(data->player.angle) * 50,
		// data->player.coor.y + sin(data->player.angle) * 50}, get_rgba(255, 10, 0, 255), data->map.img);
		// first_h = first_h_inter(data->player.angle, data->player.coor);
		// first_v = first_v_inter(data->player.angle, data->player.coor);
		// t_coor hit_h = h_wall_detect(data->map, first_h, data->player.angle);
		// t_coor hit_v = v_wall_detect(data->map, first_v, data->player.angle);
		// t_coor small_d = ft_compare(data->player.coor, hit_h, hit_v);
		// dda(data, data->player.coor, hit_v, get_rgba(0, 110, 0, 255));
	
	// dda(data, data->player.coor, (t_coor){data->player.coor.x + cos(data->player.angle) * 70,
	// 	data->player.coor.y + sin(data->player.angle) * 70});

	
		
	// double angle = data->player.angle - 0.785398;
	
	// while (angle < data->player.angle + 0.785398)// castin rays depened of player angle
	// {
	// 	dda(data, data->player.coor, (t_coor){data->player.coor.x + cos(angle) * 100,
	// 	data->player.coor.y + sin(angle) * 100});
	// 	angle += 0.00872665;
	// }
}


