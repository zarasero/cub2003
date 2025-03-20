#include "../include/cub3d.h"

/*void toggle_door(t_data *data)
{
    int px = (int)data->player.x;
    int py = (int)data->player.y;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int nx = px + dx;
            int ny = py + dy;

            if (nx >= 0 && ny >= 0 && ny < data->map_height && nx < data->map_width)
            {
                if (data->map[ny][nx] == 'D' && fabs(data->player.x - nx) < 1.2 && fabs(data->player.y - ny) < 1.2)
                {
                    data->doors[ny][nx] = !data->doors[ny][nx];
                    return;
                }
            }
        }
    }
}*/


int ft_mouse_click(int button, int x, int y, t_data *data) {
    printf("Mouse Clicked at X = %d, Y = %d, Button = %d\n", x, y, button);
    
    if (data != NULL) {
        data->player_x = x;
        data->player_y = y;
    }

    return 0;
}

/*
int ft_mouse(t_data *data) {

    int x, y;
    mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
    printf("mouse x = %d\n", x);
    int mouse_delta_x = x - (WINDOW_W / 2);
    printf("Mouse X position: %d\n", x);
    printf("Mouse delta X: %d\n", mouse_delta_x);
    printf("player angle = %f\n", data->player_angle);

    if (mouse_delta_x > 400)
    {
        printf ("HERE\n");
        if (data->player_angle >= 2 * M_PI) {
            data->player_angle -= 2 * M_PI;
        }
        if (data->player_angle < 0) {
            data->player_angle += 2 * M_PI;
        }
		ft_move(data, -1);
        ft_draw(data);
    }
    else if (mouse_delta_x != 0) {
        printf("11111\n");
        //printf("Before update, player_angle: %f\n", data->player_angle);//122
        //data->player_angle += mouse_delta_x * STEP_ANGLE;  // STEP_ANGLE контролирует чувствительность
        if (data->player_angle >= 2 * M_PI) {
            data->player_angle -= 2 * M_PI;
        }
        if (data->player_angle < 0) {
            data->player_angle += 2 * M_PI;
        }
        printf("After update, player_angle: %f\n", data->player_angle);  // Отладочная информация
    }

    if (!data->mlx || !data->win) {
        printf("Error: mlx or win is NULL before mlx_mouse_move\n");
        return -1;
    }

    printf("Resetting mouse position to center: (%d, %d)\n", WINDOW_W / 2, WINDOW_H / 2);
    mlx_mouse_move(data->mlx, data->win, x, y);
    // mlx_mouse_move(data->mlx, data->win, WINDOW_W / 2, WINDOW_H / 2);
    return 0;
}*/





