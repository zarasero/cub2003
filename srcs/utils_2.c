/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:11:01 by morgane           #+#    #+#             */
/*   Updated: 2025/03/19 17:42:17 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_starting_point(char **map, int i, int j)
{
	if (map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'N')
		return (true);
	else
		return (false);
}

void	check_colors(char *file, t_data *data)
{
	int	i;
	int	coma;

	i = 1;
	coma = 0;
	while (file[i])
	{
		if (file[i] == ',')
		{
			coma++;
			i++;
		}
		else if (file[i] == '-')
			err(data, RGB_SUP);
		else if (file[i] == '\t' || file[i] == ' ' || file[i] == '\n'
			|| (file[i] >= '0' && file[i] <= '9'))
			i++;
		else
			err(data, RGB_COMA_FORMAT);
	}
	if (coma != 2)
		err(data, RGB_COMA_FORMAT);
	return ;
}

void	color_is_valid(int *color, t_data *data)
{
	int	i;

	i = 0;
	if (color)
	{
		while (i < 3)
		{
			if (color[i] > 255)
				err(data, RGB_SUP);
			i++;
		}
	}
	return ;
}

int	skip_whitespaces(char **save, int i, int j, int *start)
{
	while (save[i][j] && (save[i][j] < '0' || save[i][j] > '9'))
		j++;
	*start = j;
	while (save[i][j] && (save[i][j] >= '0' && save[i][j] <= '9'))
		j++;
	return (j);
}

void	set_player_position_and_angle(char start_char, t_data *data)
{
	if (start_char == 'E')
		data->player_angle = 0;
	else if (start_char == 'N')
		data->player_angle = M_PI / 2;
	else if (start_char == 'W')
		data->player_angle = M_PI;
	else if (start_char == 'S')
		data->player_angle = 3 * M_PI / 2;
}
