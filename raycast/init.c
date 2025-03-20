/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:42:03 by zserobia          #+#    #+#             */
/*   Updated: 2025/03/19 19:36:03 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/../include/cub3d.h"

void	initialize_ray(t_data *data, t_ray *ray, float angle)
{
	ray->dir_x = cos(angle);
	ray->dir_y = -sin(angle);
	ray->step_x = get_sign(ray->dir_x);
	ray->step_y = get_sign(ray->dir_y);
	ray->next_vertical_x = (int)data->player_x;
	if (ray->step_x > 0)
		ray->next_vertical_x += 1.0f;
	ray->nex_hory = (int)data->player_y;
	if (ray->step_y > 0)
		ray->nex_hory += 1.0f;
}

void	ft_resoures_initialisation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		data->text[i].img = mlx_xpm_file_to_image(data->mlx, data->path_tex[i],
				&data->text[i].width, &data->text[i].height);
		if (!data->text[i].img)
		{
			printf("Error\nCan't read texture file: %s\n", data->path_tex[i]);
			ft_destroy_exit(data);
		}
		data->text[i].addr = mlx_get_data_addr(data->text[i].img,
				&data->text[i].bits_per_pixel, &data->text[i].line_length,
				&data->text[i].endian);
		if (!data->text[i].addr)
		{
			printf("Failed texture: %s\n", data->path_tex[i]);
			ft_destroy_exit(data);
		}
	}
	/* 
	data->door_texture.img = mlx_xpm_file_to_image(data->mlx, "textures/door.xpm",
		&data->door_texture.width, &data->door_texture.height);
	if (!data->door_texture.img)
		return (FAILURE);
	data->door_texture.addr = mlx_get_data_addr(data->door_texture.img,
		&data->door_texture.bpp, &data->door_texture.line_len, &data->door_texture.endian);
	*/
}

void	ft_param_initialisation(t_data *data)
{
	data->map_height = (int)(data->map_lines + 2);
	data->player_x = (float)data->y_pos;
	data->player_y = (float)data->x_pos;
	data->minimap = 0;
	data->mini_x = 0;
	data->mini_y = 0;
	data->temp_x = 0;
	data->temp_y = 0;
	data->time = 0;
    data->old_time = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error: mlx_init() returned NULL\n");
		free_all(data);
		exit(1);
	}
	data->win = mlx_new_window(data->mlx, WINDOW_W, WINDOW_H, "data");
	if (!data->win)
	{
		printf("Error: data.win == NULL\n");
		ft_destroy_exit(data);
	}
}

#include <sys/time.h>

double get_current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

#include <unistd.h> // Для usleep()
/*
int ft_mouse_click(int button, int x, int y, t_data *data) {
    printf("Mouse Clicked at X = %d, Y = %d, Button = %d\n", x, y, button);

    // Сохраняем координаты клика в структуре данных
    if (data != NULL) {
        data->player_x = x;
        data->player_y = y;
    }

    return 0;
}*/

static int loop(t_data *data)
{
    int x, y;
   // static int last_x = -1;

    if (!data)
        return (0);

    // Инициализация времени, если еще не установлено
    if (data->old_time == 0)
        data->old_time = get_current_time();

    data->time = get_current_time();

    // Ограничение FPS (10 кадров в секунду = 100 мс)
    //if ((long long)(data->time * 1000) - (long long)(data->old_time * 1000) > 100)
   // {
        mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
       /* if (last_x == -1) // Инициализация last_x
        {
            //last_x = mlx_mouse_get_pos(data->mlx, data->win, &last_x, &y);;
            return (0);
        }*/

        // Разница с предыдущей позицией мыши
       // int mouse_delta_x = x - data->player_x;
        

        // Позиция мыши по оси X
        int screen_half = WINDOW_W / 2;

        // Проверяем, на какой половине экрана находится мышь
        if (x < screen_half)
        {
            // Мышь слева, поворачиваем игрока влево
            data->player_angle -= 0.001;  // Множитель чувствительности
			data->player_angle += STEP_ANGLE;

            // Нормализация угла
            if (data->player_angle >= 2 * M_PI)
                data->player_angle -= 2 * M_PI;
        }
        else if (x > screen_half)
        {
            // Мышь справа, поворачиваем игрока вправо
            data->player_angle += 0.001;  // Множитель чувствительности
			data->player_angle -= STEP_ANGLE;


			            // Нормализация угла
			if (data->player_angle < 0)
				data->player_angle += 2 * M_PI;
        }

        // Обновление последней позиции мыши
        //last_x = x;

        // Выводим информацию о текущем угле игрока (для отладки)
        // printf("Updated player_angle: %f\n", data->player_angle);

        // Сброс позиции мыши в центр экрана для следующего движения
        mlx_mouse_move(data->mlx, data->win, WINDOW_W / 2, WINDOW_H / 2);

        // Основные игровые обновления (отрисовка сцены)
        ft_draw(data);

        // Обновление времени
        data->old_time = data->time;

        // Дополнительное замедление, чтобы управлять частотой обновления (можно регулировать)
        usleep(5000);  // Задержка в 50 мс (можно уменьшить или увеличить для замедления/ускорения)
   // }

    return (SUCCESS);
}




void part_2(t_data *data)
{
    ft_param_initialisation(data);
    ft_resoures_initialisation(data);
    ft_draw(data);

    if (!data->mlx || !data->win)
    {
        printf("Error: mlx or window is not initialized.\n");
        return;
    }

    // Установка обработчиков событий
    mlx_hook(data->win, KeyPress, KeyPressMask, ft_key, data);
    mlx_hook(data->win, DestroyNotify, NoEventMask, ft_destroy_exit, data);

    // Главный цикл игры
    mlx_loop_hook(data->mlx, loop, data);
    mlx_loop(data->mlx);
}


