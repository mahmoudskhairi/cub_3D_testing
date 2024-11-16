/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_3D.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:16:43 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/16 16:45:40 by mskhairi         ###   ########.fr       */
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

void textures(t_data *data,t_ray *ray, mlx_image_t *img)
{
	int x_texture;
	double y_texture;
	int i;
	int color;

	i = ray->top;
	// x_of_texture = 0;
	// x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * data->img1->height;
	if (ray->flag == 'h')
		x_texture = (ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE)) * img->width;
	else if (ray->flag == 'v')
		x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * img->width;
	while(i < ray->bottom)
	{
		// if (ray->flag == 'h')
		// 	x_texture = (ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE)) * img->width;
		// else if (ray->flag == 'v')
		// 	x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * img->width;
		// color = 0;
		y_texture = (i - ray->top) / (ray->bottom - ray->top) * (double)data->img1->height;
		// printf("x-->%d\n", x_texture);
		// printf("y-->%f\n", y_texture);
		if (i >= 0 && i < HEIGHT)
		{
			if ((int)y_texture * img->width + x_texture < img->height * img->width)
			{
				color = gett_rgba(&img->pixels[((int)y_texture * img->width + x_texture) * 4]);
				mlx_put_pixel(data->ft_3D, data->x_projection , i, color);
			}
			// mlx_put_pixel(data->ft_3D,data->x_projection , i, get_rgba(255,255,255,255));
		}
		i++;
	}
}
void	draw_columns(t_data *data, t_ray *ray, double angle)
{
	// mlx_image_to_window(data->mlx, data->ft_3D, 0 , 0);
	double	projection_column;
	double	projection_distance;
	ray->distance *= cos(data->player.angle - angle);
	projection_distance = WIDTH / 2 * tan(FOV / 2);                                                                                     
	projection_column = ((TILE_SIZE * projection_distance) / ray->distance) * 2;
	ray->top = (HEIGHT / 2) - (projection_column / 2);
	ray->bottom = (HEIGHT / 2) + (projection_column / 2);
	if ((sin(angle) <= 0 && ray->flag == 'h'))//----->top
	{
		textures(data, ray, data->img1);
		// printf("img1\n");
	}
	if ((sin(angle) >= 0 && ray->flag == 'h'))//buttom
	{
		textures(data, ray, data->img2);
		// printf("img2\n");
	}
	if ((cos(angle) >= 0 && ray->flag == 'v'))// ----->right
	{
		textures(data, ray, data->img3);
		// printf("img3\n");
	}
	if (cos(angle) <= 0  && ray->flag == 'v')// ----->left
	{
		textures(data, ray, data->img4);
		// printf("img4\n");
	}
}

void	projection_3D(t_data *data)
{
	t_coor first_h;
	t_coor first_v;
	// printf("rays number is %d\n", N_RAYS);
	data->rays = malloc(N_RAYS * sizeof(t_ray));
	double angle = data->player.angle - FOV / 2;
	int i = 0;
	data->x_projection = 0;
	while (i < N_RAYS)// casting rays depened of player angle
	{
		first_h = first_h_inter(angle, data->player.coor);
		first_v = first_v_inter(angle, data->player.coor);
		t_coor hit_h = h_wall_detect(data->map, first_h, angle);
		t_coor hit_v = v_wall_detect(data->map, first_v, angle);
		// t_coor small_d = ft_compare(data->player.coor, hit_h, hit_v);

		data->rays[i].Wall_hit = ft_compare(data->player.coor, hit_h, hit_v, &(data->rays[i]));
		// dda(data, data->player.coor, data->rays[i].Wall_hit, get_rgba(10, 100, 10, 255), data->map.img);
		// printf("distance = %f\n", data->rays[i].distance);
		draw_columns(data, &data->rays[i], angle);
		data->x_projection++;
		angle += RAY_ANGLE_INC;
		// printf("%f\n", data->player.angle);
		// printf("ray nbr -> %d\n", i);
		i++;
	}
}


// void buttom_textures(t_data *data,t_ray *ray)
// {
// 	int x_texture;
// 	int y_texture;
// 	int i;
// 	int color = 0;

// 	i = ray->top;
// 	// x_of_texture = 0;
// 	// x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * data->img1->height;
// 	while(i < ray->bottom)
// 	{
// 		x_texture = (ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE)) * data->img1->width;
// 		y_texture = (i - (int)ray->top) / ((int)ray->bottom - (int)ray->top) * data->img1->height;
// 		if (i >= 0 && i < HEIGHT)
// 		{
// 			// printf("%f\n", ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE));
// 			// x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * data->img1->height;
// 			color = gett_rgba(&data->img1->pixels[(y_texture * data->img1->width + x_texture) * 4]);
// 			// mlx_put_pixel(data->ft_3D, data->x_projection , i, color);
// 			mlx_put_pixel(data->ft_3D,data->x_projection , i, get_rgba(255,255,255,255));
// 		}
// 		i++;
// 	}
// }
// void top_textures(t_data *data,t_ray *ray)
// {
// 	int x_texture;
// 	int y_texture;
// 	int i;
// 	int color;

// 	i = ray->top;
// 	// x_of_texture = 0;
// 	while(i < ray->bottom)
// 	{
// 		if (i >= 0 && i < HEIGHT)
// 		{
// 			// printf("%f\n", ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE));
// 			// x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.	y / TILE_SIZE)) * data->img1->height;
// 			x_texture = (ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE)) * data->img2->width;
// 			y_texture = (i - ray->top) / (ray->bottom - ray->top) * data->img2->height;
// 			color = gett_rgba(&data->img2->pixels[(y_texture * data->img2->width + x_texture) * 4]);
// 			mlx_put_pixel(data->ft_3D, data->x_projection , i, color);
// 			// mlx_put_pixel(data->ft_3D,data->x_projection , i, get_rgba(255,255,255,255));
// 		}
// 		i++;
// 	}
// }
// void right_textures(t_data *data,t_ray *ray)
// {
// 	int x_texture;
// 	int y_texture;
// 	int i;
// 	int color;

// 	i = ray->top;
// 	// x_of_texture = 0;
// 	x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.	y / TILE_SIZE)) * data->img3->height;
// 	while(i < ray->bottom)
// 	{
// 		if (i >= 0 && i < HEIGHT)
// 		{
// 			// printf("%f\n", ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE));
// 			x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * data->img3->height;
// 			y_texture = (i - ray->top) / (ray->bottom - ray->top) * data->img3->height;
// 			color = gett_rgba(&data->img3->pixels[(y_texture * data->img3->width + x_texture) * 4]);
// 			mlx_put_pixel(data->ft_3D,data->x_projection , i, color);
// 			// mlx_put_pixel(data->ft_3D,ray->Wall_hit.y , i, color);
// 			// mlx_put_pixel(data->ft_3D,data->x_projection , i, get_rgba(255,255,255,255));
// 		}
// 		i++;
// 	}
// }
// void left_textures(t_data *data,t_ray *ray)
// {
// 	int x_texture;
// 	int y_texture;
// 	int i;
// 	int color;

// 	i = ray->top;
// 	// x_of_texture = 0;
	
// 			// printf("%f\n", ray->Wall_hit.x);
// 			// printf("%f\n", ray->Wall_hit.y);
// 	x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.	y / TILE_SIZE)) * data->img4->height;
// 	while(i < ray->bottom)
// 	{
// 		if (i >= 0 && i < HEIGHT)
// 		{
// 			x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * data->img4->height;
// 			y_texture = (i - ray->top) / (ray->bottom - ray->top) * data->img4->height;
// 			color = gett_rgba(&data->img4->pixels[(y_texture * data->img4->width + x_texture) * 4]);
// 			mlx_put_pixel(data->ft_3D,data->x_projection , i, color);
// 			// mlx_put_pixel(data->ft_3D,data->x_projection , i, get_rgba(255,255,255,255));
			
// 		}
// 		i++;
// 	}
// }
// void	draw_columns(t_data *data, t_ray *ray, double angle)
// {
// 	// mlx_image_to_window(data->mlx, data->ft_3D, 0 , 0);
// 	double	projection_column;
// 	double	projection_distance;
// 	ray->distance *= cos(data->player.angle - angle);
// 	projection_distance = WIDTH / 2 * tan(FOV / 2);                                                                                     
// 	projection_column = (TILE_SIZE * projection_distance) / ray->distance;
// 	ray->top = (HEIGHT / 2) - (projection_column / 2);
// 	ray->bottom = (HEIGHT / 2) + (projection_column / 2);
// 	if ((sin(angle) <= 0 && ray->flag == 'h'))//----->buttom
// 		buttom_textures(data, ray);
// 	if ((sin(angle) >= 0 && ray->flag == 'h'))//top
// 		top_textures(data, ray);
// 	if ((cos(angle) >= 0 && ray->flag == 'v'))// ----->right
// 		right_textures(data, ray);
// 	if (cos(angle) <= 0  && ray->flag == 'v')// ----->left
// 		left_textures(data, ray);
// 	}
