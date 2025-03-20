/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:37:00 by zserobia          #+#    #+#             */
/*   Updated: 2025/03/19 18:30:37 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	text_info(t_data *data, float distance,
	int texture_index, float text_x)
{
	data->textur_index = texture_index;
	data->textur_shift = text_x;
	return (distance);
}

void	calculate_next_intersection(t_data *data, t_ray *ray)
{
	if (ray->step_x != 0)
	{
		ray->next_vertical_y = data->player_y + ray->dir_y
			/ ray->dir_x * (ray->next_vertical_x - data->player_x);
		ray->vert_dist = sqrt(pow(data->player_x - ray->next_vertical_x, 2.0)
				+ pow(data->player_y - ray->next_vertical_y, 2.0));
		ray->text_x = ray->next_vertical_y - (int) ray->next_vertical_y;
		if (ray->step_x > 0)
			ray->text_x = 1 - ray->text_x;
	}
	else
		ray->vert_dist = INFINITY;
	if (ray->step_y != 0)
	{
		ray->nex_horx = data->player_x + ray->dir_x / ray->dir_y
			* (ray->nex_hory - data->player_y);
		ray->horiz_dist = sqrt(pow(data->player_x - ray->nex_horx, 2.0)
				+ pow(data->player_y - ray->nex_hory, 2.0));
		ray->text_y = ray->nex_horx - (int) ray->nex_horx;
		if (ray->step_y < 0)
			ray->text_y = 1 - ray->text_y;
	}
	else
		ray->horiz_dist = INFINITY;
}

float	trace_vert(t_data *data, float angle, t_ray *ray)
{
	int	check_x;

	if (ray->step_x == 1)
		check_x = ray->next_vertical_x;
	else
		check_x = ray->next_vertical_x - 1;
	if (data->new_map[(int)ray->next_vertical_y][(int)check_x] == '1')
		return (text_info(data, ray->vert_dist, ray->step_x + 1, ray->text_x));
	else
	{
		ray->next_vertical_x += ray->step_x;
		ray->next_vertical_y += ray->step_x * tan(angle);
		return (-1.0);
	}
}

float	trace_horiz(t_data *data, float angle, t_ray *ray)
{
	int	check_y;

	if (ray->step_y == 1)
		check_y = ray->nex_hory;
	else
		check_y = ray->nex_hory - 1;
	if (data->new_map[(int)check_y][(int)ray->nex_horx] == '1')
		return (text_info(data, ray->horiz_dist, ray->step_y + 2, ray->text_y));
	else
	{
		ray->nex_hory += ray->step_y;
		ray->nex_horx += ray->step_y / tan(angle);
		return (-1.0);
	}
}

float	trace_ray(t_data *data, float angle)
{
	t_ray		ray;
	float	result;

	initialize_ray(data, &ray, angle);
	while (1)
	{
		calculate_next_intersection(data, &ray);
		if (ray.vert_dist < ray.horiz_dist)
		{
			result = trace_vert(data, angle, &ray);
			if (result != -1.0)
				return (result);
		}
		else
		{
			result = trace_horiz(data, angle, &ray);
			if (result != -1.0)
				return (result);
		}
	}
}
