/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:23:08 by zserobia          #+#    #+#             */
/*   Updated: 2025/03/19 19:48:53 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_draw_ceiling_and_floor(t_data *data)
{
	unsigned int	*dst;
	unsigned int	i;
	unsigned int	mid_height;

	mid_height = WINDOW_W * (WINDOW_H / 2);
	dst = (unsigned int *) data->img.addr;
	i = mid_height;
	while (i > 0)
	{
		*dst++ = data->color_ceiling;
		i--;
	}
	i = WINDOW_W * WINDOW_H - mid_height;
	while (i > 0)
	{
		*dst++ = data->color_floor;
		i--;
	}
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_W || y < 0 || y >= WINDOW_H)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_image *img, t_data *data, int color, int scale)
{
	int	j;
	int	i;

	if (data->mini_x < 0 || data->mini_y < 0
		|| data->mini_x + scale > WINDOW_W || data->mini_y + scale > WINDOW_H)
		return ;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel(img, data->mini_x + i, data->mini_y + j, color);
			j++;
		}
		i++;
	}
}

void	init_mini(t_data *data)
{
	data->npc_color = 0xFF0000;
	data->wall_color = 0x000000;
	data->map_scal = fmin(WINDOW_W / data->map_width,
			WINDOW_H / data->map_height) / 5;
}

void	draw_minimap(t_data *data)
{
	if (data->minimap == 0)
		return ;
	init_mini(data);
	data->temp_y = 0;
	while (data->temp_y < data->map_height)
	{
		data->temp_x = 0;
		while (data->temp_x < data->map_width)
		{
			if (data->new_map[data->temp_y][data->temp_x] == '1')
			{
				data->mini_x = data->temp_x * data->map_scal;
				data->mini_y = data->temp_y * data->map_scal;
				draw_square(&data->img, data, data->wall_color, data->map_scal);
			}
			data->temp_x++;
		}
		data->temp_y++;
	}
	if (data->player_x >= 0 && data->player_y >= 0)
	{
		data->mini_x = (int)((data->player_x) * data->map_scal);
		data->mini_y = (int)((data->player_y) * data->map_scal);
		draw_square(&data->img, data, data->npc_color, data->map_scal / 2);
	}
}
