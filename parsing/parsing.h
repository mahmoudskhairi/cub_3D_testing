/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:24 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/10/11 18:57:58 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "../cub3D.h"

void	check_args(int ac, char *str);
void	fill_map(t_data *data);
void	fill_file_content(t_data *data, int fd);
void	del(void *content);

void	add_texture(char **texture, char *line, u_int16_t *flag);
void	clean_textures(t_texture *textures);
void	fill_textures(t_data *data);

int		is_number(char *str);
int		check_color(char *str);
void	add_color(t_data *data, char **r, char **gb);
void	fill_colors(t_data *data);

void	after_map(t_list *tmp);
t_list	*skip_header(t_list *tmp, int end);
void	fill_map(t_data *data);
int		check_all_line(char *line, char *chars);
int		check_player(t_data *data, char **map);

void	check_edges(char **map, int hight, int width);
void	check_all_map(char **map, int hight, int width);

// testing 
void	print_map(t_data *data);

#endif
