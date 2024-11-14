/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:25:44 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/10/12 13:49:51 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_all_line(char *line, char *chars)
{
	int	i;

	i = 0;

	while (line[i])
	{
		if (!ft_strchr(chars, line[i]))
			return (1);
		i++;
	}
	return (0);
}
t_list *skip_header(t_list *tmp, int end)
{
	while (tmp)
	{
		if (tmp->i == end)
		{
			while (tmp && !ft_strlen(tmp->content))
				tmp = tmp->next;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_max_len(t_list *tmp)
{
	int	max;
	int	len;

	if (tmp)
		max = ft_strlen(tmp->content);
	while (tmp)
	{
		len = ft_strlen(tmp->content);
		if ( len > max)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}
int	get_height(t_list *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		if (!ft_strlen(tmp->content))
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	fill_map(t_data *data)
{
	t_list *tmp;
	int		i;

	i = 0;
	tmp = skip_header(data->file_content, data->header_end);
	data->map.heigth = get_height(tmp);
	if (!data->map.heigth)
	{
		ft_strerr("ther is not map in this file or map in the middle");
		exit(EXIT_FAILURE);
	}
	data->map.width = ft_max_len(tmp);
	data->map.grid = ft_calloc(data->map.heigth + 1 , sizeof(char *));
	if (!data->map.grid)
		return;
	while (tmp)
	{
		if (check_all_line(tmp->content, "NSEW10 "))
		{
			ft_strerr("invalid map's element");
			exit(EXIT_FAILURE);
		}
		if (!ft_strlen(tmp->content))// if there is an empty  line check if there is something after it
		{
			after_map(tmp);
			break;
		}
		data->map.grid[i] = ft_calloc(data->map.width + 1 , sizeof(char));
		if (!data->map.grid[i])
			return;
		ft_memset(data->map.grid[i], ' ', data->map.width);
		ft_memcpy(data->map.grid[i++], tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
	}
	if (check_player(data, data->map.grid) != 1)
	{
		ft_strerr("more or less than player in map");
		exit(EXIT_FAILURE);
	}
	check_edges(data->map.grid, data->map.heigth, data->map.width);
	check_all_map(data->map.grid, data->map.heigth, data->map.width);
}

void	after_map(t_list *tmp)
{
	while (tmp)
	{
		if (ft_strlen(tmp->content))
		{
			ft_strerr("something after map's Grid");
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
}

