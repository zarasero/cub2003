/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:00:56 by zserobia          #+#    #+#             */
/*   Updated: 2025/03/19 15:03:14 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_sign(float num)
{
	return ((num > 0) - (num < 0));
}

int	ft_destroy_exit(t_data *data)
{
	int	i;

	mlx_clear_window(data->mlx, data->win);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	i = -1;
	while (++i < 4)
	{
		if (data->text[i].img)
			mlx_destroy_image(data->mlx, data->text[i].img);
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_all(data);
	exit(0);
}
/*
void	print_data(t_data *data)
{
	printf("=== t_data Structure ===\n");
	printf("\nmap_height: %d\n", data->map_height);
	printf("map_width: %d\n", data->map_width);
	printf("x_pos: %d\n", data->x_pos);
	printf("y_pos: %d\n", data->y_pos);
	printf("\nplayer_x: %f\n", data->player_x);
	printf("player_y: %f\n", data->player_y);
	printf("player_angle: %f\n", data->player_angle);
	printf("\nNew Map:\n========================\n");
	for (int i = 0; i < data->map_height; i++) {
		for (int j = 0; j < data->map_width; j++) {
			printf("%c", data->new_map[i][j]);
		}
		printf("\n");
	}
}*/
