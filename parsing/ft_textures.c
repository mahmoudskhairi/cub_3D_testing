/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:36:59 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/10/12 13:59:07 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_texture(char **texture, char *line, u_int16_t *flag)
{

	if (*texture)
	{
		ft_strerr("duplicate texture");
		exit (EXIT_FAILURE);
	}
	*texture = ft_strdup(line);
	(*flag)++;
}
void	clean_textures(t_texture *textures)
{
	textures->EA = NULL;
	textures->WE = NULL;
	textures->SO = NULL;
	textures->NO = NULL;
	textures->flag = 0;
}

void	fill_textures(t_data *data)
{
	t_list *tmp;
	char **split;
	int		words;

	tmp = data->file_content;
	clean_textures(&data->textures);
	while (tmp && data->textures.flag < 4)
	{
		// printf("%s\n", data->textures.EA);
		if (!ft_strlen(tmp->content))
		{
			tmp = tmp->next;
			continue;
		}
		if (!check_all_line(tmp->content, "NSWE10 "))
		{
			ft_strerr("this line is a part of map");
			exit(EXIT_FAILURE);	
		}
		split = ft_split_ws(tmp->content, " ", &words);
		if (words >= 2)
		{
			if (!ft_strcmp(split[0], "SO"))
				add_texture(&data->textures.SO, split[1], &data->textures.flag);
			else if (!ft_strcmp(split[0], "NO"))
				add_texture(&data->textures.NO, split[1], &data->textures.flag);
			else if (!ft_strcmp(split[0], "WE"))
				add_texture(&data->textures.WE, split[1], &data->textures.flag);
			else if (!ft_strcmp(split[0], "EA"))
				add_texture(&data->textures.EA, split[1], &data->textures.flag);
			else if (ft_strcmp(split[0], "F") && ft_strcmp(split[0], "C"))
			{
				ft_strerr("invalid line");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			ft_strerr("invalid line");
			exit(EXIT_FAILURE);
		}
		ft_free(split);
		tmp = tmp->next;
	}
	data->header_end = tmp->i;
	if (data->textures.flag != 4)
	{
		ft_strerr("Textures are not valid");
		exit(EXIT_FAILURE);	
	}
	// printf("%s\n", data->textures.EA);
	// printf("%s\n", data->textures.SO);
	// printf("%s\n", data->textures.WE);
	// printf("%s\n", data->textures.NO);
}
