/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:38:28 by morgane           #+#    #+#             */
/*   Updated: 2025/03/19 17:03:41 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	free_all(t_data *data)
{
	if (data == NULL)
		return ;
	if (data->c_color != NULL)
		free(data->c_color);
	if (data->f_color != NULL)
		free(data->f_color);
	if (data->path_tex[0] != NULL)
		free(data->path_tex[0]);
	if (data->path_tex[1] != NULL)
		free(data->path_tex[1]);
	if (data->path_tex[2] != NULL)
		free(data->path_tex[2]);
	if (data->path_tex[3] != NULL)
		free(data->path_tex[3]);
	if (data->map)
		free_char_tab(data->map);
	if (data->new_map)
		free_char_tab(data->new_map);
	if (data->file)
		free_char_tab(data->file);
	free(data);
}

void	error_color(int *colors, char **save, t_data *data)
{
	free(colors);
	free_char_tab(save);
	err(data, RGB_SUP);
}
