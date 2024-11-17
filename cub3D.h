/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:54:40 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/17 16:49:10 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

/*------------------------[ includes ]----------------------------------*/

#include <unistd.h>//
#include <stdio.h> // for testing
#include <fcntl.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "src/libft/libft.h"

#define TILE_SIZE  24
#define MINI_HEIGHT TILE_SIZE * 10
#define MINI_WIDTH  TILE_SIZE * 20

#define DEGREE_0 0.0
#define DEGREE_90 90 * M_PI / 180
#define DEGREE_60 60 * M_PI / 180
#define DEGREE_180 M_PI
#define DEGREE_270 270 * M_PI / 180

#define WIDTH 1600
#define HEIGHT 1000

#define RAD M_PI / 180 // one radian
#define DEGREE 5 * M_PI / 180
#define	SPEED 2
// #define RES 

#define N_RAYS 1600

#define FOV DEGREE_60

#define RAY_ANGLE_INC FOV / N_RAYS


/*------------------------[ structs ]----------------------------------*/

typedef struct s_coor
{
	double	x;
	double	y;
	
}	t_coor;

typedef struct s_player
{
	t_coor		coor;// coordinates of player with pixels
	double		angle;// angle of player
	double		rotate_speed; 
	double		move_speed; 
	
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width; // width of map
	int		heigth;// height of map
	mlx_image_t *img;// image of map
}	t_map;

typedef	struct s_rgb
{
	int	r;
	int	g;
	int	b;
} t_rgb;

typedef struct s_color
{
	t_rgb		F;
	t_rgb		C;
	u_int16_t	flag;
} t_color;

typedef struct s_texture
{
	char		*NO;
	char		*SO;
	char		*EA;
	char		*WE;
	u_int16_t	flag;
} t_texture;

typedef	struct s_ray
{
	t_coor		 Wall_hit;
	double		distance;
	double top;
	double bottom;
	int flag;
}	t_ray;

typedef struct s_data
{
	t_list		*file_content;// content from map's file
	t_map		map;// struct of infos of map
	t_texture	textures;// textures from file
	t_color		colors;// colors from file
	int		 	header_end; // when I finish to extract colors and colors i pust this flag to it
	t_player	player; // player information
	mlx_t		*mlx;// mlx variable
	mlx_image_t	*ft_3D;// image of 3d vue
	t_ray		*rays;
	double  x_projection;
	mlx_texture_t *texture_img1;
	mlx_texture_t *texture_img2;
	mlx_texture_t *texture_img3;
	mlx_texture_t *texture_img4;
	mlx_image_t *img1;
	mlx_image_t *img2;
	mlx_image_t *img3;
	mlx_image_t *img4;
	double first_player_angle;
}	t_data;



/*------------------------[ prototypes ]-------------------------------*/

/*--[ :: parsing :: ]--*/

void	check_requirements(int ac, char **av, t_data *data);
void	cast_rays(t_data *data);
void	my_mlx_put_pixel(t_data *data, mlx_image_t *img, t_coor coor, u_int32_t color);

/*--[ :: raycasting :: ]--*/

void	ft_loop(void *dataa);// loop hook

#endif
