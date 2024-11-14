/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palestine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:27:04 by mskhairi          #+#    #+#             */
/*   Updated: 2024/10/17 13:53:44 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../MLX42/include/MLX42/MLX42.h"
// #include <stdio.h>

// int main()
// {
// 	void *mlx = mlx_init(1500, 1200, "graphic", 0);
// 	if (!mlx)
// 	{
// 		printf("error\n");
// 	}
// 	mlx_texture_t *texture = mlx_load_png("so_long.png");
// 	if (!texture)
// 		printf("texture is not loading\n");
// 	mlx_image_t *image = mlx_texture_to_image(mlx, texture);
// 		if (!image)
// 		printf("texture is not transform to image\n");
// 	if (mlx_image_to_window(mlx, image, 0 ,0) < 0)
// 		printf("image_to_window Error\n");
// 	mlx_loop(mlx);
// }

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// void center_of_window(mlx_image_t* img)
// {
// 	int width = 0;
// 	int heigth;
// 	while(width < Window_W)
// 	{
// 		heigth = Window_H / 3;
// 		while(heigth < 2 * Window_H / 3)
// 		{
// 			mlx_put_pixel(img, width , heigth, get_rgba(59, 10, 16, 200));
// 			heigth++;
// 		}
// 		width += 10;
// 	}
// }
// void buttom_of_window(mlx_image_t* img)
// {
// 	int width = 0;
// 	int heigth;
// 	while(width < Window_W)
// 	{
// 		heigth = 2 * Window_H / 3;
// 		while(heigth < Window_H)
// 		{
// 			mlx_put_pixel(img, width , heigth, get_rgba(223, 35, 93, 200));
// 			heigth++;
// 		}
// 		width += 20;
// 	}
// }
#define BPP sizeof(int32_t)
#define Window_W 2000
#define Window_H 1100

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void red_top(mlx_image_t* img)
{
	int width = 0;
	int heigth = 0;
	while(width < Window_W / 3)
	{
		while(heigth < Window_H / 2)
		{
			mlx_put_pixel(img, width , heigth, get_rgba(255, 0, 0, 200));
			heigth++;
		}
		width++;
		heigth = width; 
	}
}
void red_buttom(mlx_image_t* img)
{
	int width = 0;
	int heigth;
	while(width < Window_W / 3)
	{
		heigth = Window_H / 2;
		while(heigth < Window_H - width)
		{
			mlx_put_pixel(img, width , heigth, get_rgba(255, 0, 0, 200));
			heigth++;
		}
		width++;
	}
}
void left_black(mlx_image_t* img)
{
	int width = 0;
	int heigth = 0;
	while(heigth < Window_H / 3)
	{
		
		while(width < Window_W / 6)
		{
			mlx_put_pixel(img, width , heigth, get_rgba(0, 0, 0, 200));
			width++;
		}
		heigth++;
		width = heigth;
	}
}
void right_black(mlx_image_t* img)
{
	int heigth = 0;
	int width;
	while(heigth < Window_H / 3 - 33)
	{
		width = Window_W / 6;
		while(width < Window_W)
		{
			mlx_put_pixel(img, width , heigth, get_rgba(0, 0, 0, 200));
			width++;
		}
		heigth++;
	}
}

void left_green(mlx_image_t* img)
{
	int width1 = 0;
	int width2 = 0;
	int heigth = Window_H;
	while(heigth > 2 * Window_H / 3)
	{
		width1 = width2;
		while(width1 < Window_W / 6)
		{
			mlx_put_pixel(img, width1 , heigth, get_rgba(0, 166, 0, 200));
			width1++;
		}
		heigth--;
		width2++;
	}
}
void right_green(mlx_image_t* img)
{
	int width;
	int heigth = 2 * Window_H / 3 + 33;
	while(heigth < Window_H)
	{
		width = Window_W / 6;
		while(width < Window_W)
		{
			mlx_put_pixel(img, width , heigth, get_rgba(0, 166, 0, 200));
			width++;
		}
		heigth++;
	}
}
void right_white(mlx_image_t* img)
{
	int width = Window_W / 3 - 115;
	int heigth = Window_H / 3 - 33;
	while(heigth < 2 * Window_H / 3 + 33)
	{
		width = Window_W / 3 - 115;
		while(width < Window_W)
		{
			mlx_put_pixel(img, width , heigth, get_rgba(255, 255, 255, 200));
			width++;
		}
		heigth++;
	}
}
void top_white(mlx_image_t* img)
{
	int width1 = Window_W / 6;
	int width2 = Window_W / 6;
	int heigth = Window_H / 3 - 33;
	while(heigth < Window_H / 2)
	{
		width1 = width2;
		while(width1 < Window_W / 3 - 115)
		{
			mlx_put_pixel(img, width1 , heigth, get_rgba(255, 255, 255, 200));
			width1++;
		}
		width2++;
		heigth++;
	}
}
void buttom_white(mlx_image_t* img)
{
	int width1 = Window_W / 6;
	int width2 = Window_W / 6;
	int heigth = 2 * Window_H / 3 + 33;
	while(heigth > Window_H / 3)
	{
		width1 = width2;
		while(width1 < Window_W / 3)
		{
			mlx_put_pixel(img, width1 , heigth, get_rgba(255, 255, 255, 200));
			width1++;
		}
		heigth--;
		width2++;
	}
}


int	main()
{
    mlx_t* mlx = mlx_init(Window_W, Window_H, "MLX_palastine_flag", true);
    if (!mlx) exit(EXIT_FAILURE);
    mlx_image_t* img = mlx_new_image(mlx, Window_W , Window_H);
	mlx_image_to_window(mlx, img,0 , 0);
	red_top(img);
	red_buttom(img);
	left_black(img);
	right_black(img);
	left_green(img);
	right_green(img);
	right_white(img);
	top_white(img);
	buttom_white(img);
	mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}