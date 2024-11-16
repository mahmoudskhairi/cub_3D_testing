#include <stdio.h>
#include <stdlib.h>
// #include <st.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t			i;
	char	*ps1;
	char	*ps2;

	i = 0;
	ps1 = ( char *) s1;
	ps2 = ( char *) s2;
	if (s1 == s2)
		return (s1);
	if (!ps1 && !ps2)
		return (NULL);
	while (i < n)
	{
		ps1[i] = ps2[i];
		i++;
	}
	return (s1);
}

int main()
{
	char s[10] = "hellot";
	unsigned char s2[10] = "€€€€";
	printf("%s\n", s2);
	// printf("%s\n", ft_memcpy(s, s2, 6));
}

// void textures(t_data *data,t_ray *ray, mlx_image_t *img)
// {
// 	int x_texture;
// 	int y_texture;
// 	int i;
// 	int color;

// 	i = ray->top;
// 	// x_of_texture = 0;
// 	// x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * data->img1->height;
// 	if (ray->flag == 'h')
// 		x_texture = (ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE)) * img->width;
// 	else if (ray->flag == 'v')
// 		x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * img->width;
// 	while(i < ray->bottom)
// 	{
// 		if (ray->flag == 'h')
// 			x_texture = (ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE)) * img->width;
// 		else if (ray->flag == 'v')
// 			x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * img->width;
// 		color = 0;
// 		y_texture = (i - ray->top) / (ray->bottom - ray->top) * data->img1->height;
// 		if (i >= 0 && i < HEIGHT)
// 		{
// 			if (x_texture * 4 < (int)img->width && y_texture * 4 < (int)img->height)
// 			{
// 				color = gett_rgba(&img->pixels[y_texture * img->width + x_texture * 4]);
// 				mlx_put_pixel(data->ft_3D, data->x_projection , i, color);
// 			}
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
// 		textures(data, ray, data->img1);
// 	if ((sin(angle) >= 0 && ray->flag == 'h'))//top
// 		textures(data, ray, data->img2);
// 	if ((cos(angle) >= 0 && ray->flag == 'v'))// ----->right
// 		textures(data, ray, data->img3);
// 	if (cos(angle) <= 0  && ray->flag == 'v')// ----->left
// 		textures(data, ray, data->img4);
// }