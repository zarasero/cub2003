/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:23:28 by zserobia          #+#    #+#             */
/*   Updated: 2025/03/19 13:36:14 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/../include/cub3d.h"

void	ft_move(t_data *data, int direction)
{
	float	dist;
	float	move_x;
	float	move_y;
	float	angle;

	angle = data->player_angle + direction * M_PI / 2;
	move_x = STEP_LINE * cos(angle);
	move_y = STEP_LINE * sin(angle);
	dist = trace_ray(data, get_sign(move_y) * M_PI / 2);
	if (dist < fabs(move_y))
		move_y = 0;
	dist = trace_ray(data, (1 - (get_sign(move_x) + 1) / 2) * M_PI);
	if (dist < fabs(move_x))
		move_x = 0;
	data->player_x += move_x;
	data->player_y -= move_y;
}

void	ft_key_2(int key, t_data *data)
{
	if (key == 65307)
	{
		ft_destroy_exit(data);
		mlx_loop_end(data->mlx);
	}
	else if (key == 65362 || key == 119)
		ft_move(data, 0);
	else if (key == 65364 || key == 115)
		ft_move(data, 2);
	else if (key == 97)
		ft_move(data, 1);
	else if (key == 100)
		ft_move(data, -1);
}

int	ft_key(int key, t_data *data)
{
	if (key == 65307 || key == 65362 || key == 119
		|| key == 65364 || key == 115 || key == 97 || key == 100)
		ft_key_2(key, data);
	else if (key == 65361 || key == 65363)
	{
		if (key == 65361)
			data->player_angle += STEP_ANGLE;
		else
			data->player_angle -= STEP_ANGLE;
		if (data->player_angle >= 2 * M_PI)
			data->player_angle -= 2 * M_PI;
		if (data->player_angle < 0)
			data->player_angle += 2 * M_PI;
	}
	else if (key == 113)
		data->minimap = 1 - data->minimap;
	/* else if (key == KEY_E)
		toggle_door(game);*/
	else
		return (0);
	ft_draw(data);
	return (0);
}
