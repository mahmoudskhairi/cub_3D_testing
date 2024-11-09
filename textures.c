#include <stdlib.h>
#include <string.h>
#include <stdio.h>
# include "../MLX42/include/MLX42/MLX42.h"


int get_rgba(uint8_t *color)
{
    return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

int main()
{
	int x = 0; 
	int y; 
	mlx_t *mlx = mlx_init(1500, 1100, "textures", true);

	mlx_image_t *img1 = mlx_new_image(mlx, 1500, 1100);
	mlx_texture_t *texture = mlx_load_png("so_long.png");
	mlx_image_t *img2 = mlx_texture_to_image(mlx, texture);
	mlx_image_to_window(mlx, img1, 0 , 0);
	if (!img2)
		return (printf("np work heheh\n"), 0);
	printf("width--> %d\n",img2->width );
	printf("height--> %d\n",img2->height);
	while(x < img2->width)
	{
		y = 0;
		while(y < img2->height)
		{
			mlx_put_pixel(img1, x, y, get_rgba(&img2->pixels[(y * img2->width + x) * 4]));
			y++;
		}
		x++;
	}
	mlx_loop(mlx);
	return (1);
}