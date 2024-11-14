/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:16:33 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/10/10 15:30:49 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_color(char *str)
{
	char	**tmp;
	int		words;
	int		nb;

	words = 0;
	tmp = ft_split_ws(str, " \t\b\r", &words);
	if (words == 1 && is_number(tmp[0]))
	{
		
		nb = ft_atoi(tmp[0]);
		if (nb >= 0 && nb <= 255)
		{
			ft_free(tmp);
			return (nb);
		}
	}
	ft_free(tmp);
	return (-1);
}
// check_if_they are numbers and store them in an array to put it here      [ ---,---,---  ]

void	add_color(t_data *data, char **r, char **gb)
{
	if (check_color(r[1]) != -1 && check_color(gb[1]) != -1 && check_color(gb[2]) != -1)
	{
		if (!ft_strcmp(r[0], "F"))
		{
			data->colors.F.r = ft_atoi(r[1]);
			data->colors.F.g = ft_atoi(gb[1]);
			data->colors.F.b = ft_atoi(gb[2]);
			data->colors.flag++;
		}
		else if (!ft_strcmp(r[0], "C"))
		{
			// printf("Ceiling scheme color\n");
			data->colors.C.r = ft_atoi(r[1]);
			data->colors.C.g = ft_atoi(gb[1]);
			data->colors.C.b = ft_atoi(gb[2]);
			data->colors.flag++;	
		}
	}
}

void	fill_colors(t_data *data)
{
	t_list *tmp;
	char **split_1;
	char **split_2;
	int		words;

	tmp = data->file_content;
	data->colors.flag = 0;
	while (tmp)
	{
		if (data->colors.flag == 2 && tmp->i > data->header_end)// it's not valid\n
		{
			data->header_end = tmp->i;
			return ;
		}
		split_1 = ft_split_ws(tmp->content, ",\n", &words);
		if (words == 3)
		{
			split_2 = ft_split_ws(split_1[0], "\t ", &words);
			if (words == 2)
				add_color(data, split_2, split_1);
			ft_free(split_2);
		}
		ft_free(split_1);	
		tmp = tmp->next;
	}
	if (data->colors.flag != 2)
	{
		ft_strerr("Colors are not valid");
		exit(EXIT_FAILURE);
	}
}
	// printf("F == [%d][%d][%d]\n", data->colors.F.r, data->colors.F.g, data->colors.F.b);
	// printf("C == [%d][%d][%d]\n", data->colors.C.r, data->colors.C.g, data->colors.C.b);

