/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <zserobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:43:36 by zserobia          #+#    #+#             */
/*   Updated: 2025/03/19 18:30:41 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define STEP_LINE 0.1
# define STEP_ANGLE 0.05
# define M_PI 3.14159265358979323846
# define WINDOW_W 800
# define WINDOW_H 600
# define VIEW_ANGLE 1.047
# define EXTENSION "Error: Map extension is not valid. Please use \".cub\" extension.\n"
# define OPENFD "Error: Map file descriptor is not valid\n"
# define MALLOC "Error: Allocation failed\n"
# define ID_TXT "Error: Texture id is not valid \n"
# define ID_COLORS "Error: Color id is not valid \n"
# define NUM_RGB "Error: RGB arguments' number invalid, please respect RGB format\n"
# define RGB_COMA_FORMAT "Error: RGB format is not valid because of comas' or arguments' number\n"
# define CHAR_NOT_VALID "Error: Character invalid in the map\n"
# define STARTING_POINT "Error: Starting point not valid\n"
# define TXT_AFTER_MAP "Error: Textures and colors have to be before your map\n"
# define MAP_OPENED "Error: Map is opened\n"
# define MAP_INVALID "Error : No valid map found\n"
# define RGB_SUP "Error: RGB colors are between 0 and 255\n"
# define CLEAN "Error: Informations have to be separated by empty lines,please clean your file\n"

#define SUCCESS 0


# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h> 
# include "libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
}	t_texture;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_draw_params
{
	float		line_height;
	float		texture_position;
	float		texture_step;
	t_texture	*texture;
}	t_draw_params;

typedef struct s_ray
{
	float	dir_x;
	float	dir_y;
	int		step_x;
	int		step_y;
	float	delta_x;
	float	delta_y;
	float	ray_dir_x;
	float	ray_dir_y;
	float	next_vertical_x;
	float	next_vertical_y;
	float	nex_horx;
	float	nex_hory;
	float	vert_dist;
	float	horiz_dist;
	float	text_x;
	float	text_y;
	int		map_x;
	int		map_y;
}	t_ray;

typedef struct s_data
{
	int			map_lines;
	int			map_start;
	int			end_map;
	int			*f_color;
	int			*c_color;
	char		**file;
	char		*path_tex[4];
	char		**map;
	char		**new_map;
	int			x_pos;
	int			y_pos;
	int			color_ceiling;
	int			color_floor;
	int			map_height;
	int			map_width;
	float		player_x;
	float		player_y;
	float		player_angle;
	void		*mlx;
	void		*win;
	t_image		img;
	int			textur_index;
	float		textur_shift;
	t_image		minimap_img;
	int			npc_color;
	int			wall_color;
	int			map_scal;
	int			minimap;
	int			mini_x;
	int			mini_y;
	int			temp_x;
	int			temp_y;
	int			i;
	double time;
    double old_time;
	t_texture	text[4];
	t_texture	door_texture;
}	t_data;

int		ft_prepare_texture(t_data *data, float distance, t_draw_params *params);
void	ft_draw_column(t_data *data, int x, t_draw_params *params);
void	ft_draw_vertical_line(t_data *data, int x, float distance);
void	ft_init_vertical_line(t_data *data);
void	ft_draw_ceiling_and_floor(t_data *data);
void	put_pixel(t_image *img, int x, int y, int color);
void	draw_square(t_image *img, t_data *data, int color, int scale);
void	init_mini(t_data *data);
void	draw_minimap(t_data *data);
int		ft_draw(t_data *data);

void	ft_resoures_initialisation(t_data *data);
void	ft_param_initialisation(t_data *data);
void	part_2(t_data *data);

void	ft_move(t_data *data, int direction);
void	ft_key_2(int key, t_data *data);
int		ft_key(int key, t_data *data);

float	text_info(t_data *data, float distance,
			int texture_index, float text_x);
float	trace_ray(t_data *data, float angle);
float	trace_horiz(t_data *data, float angle, t_ray *ray);
float	trace_vert(t_data *data, float angle, t_ray *ray);
void	calculate_next_intersection(t_data *data, t_ray *ray);
void	initialize_ray(t_data *data, t_ray *ray, float angle);

int		ft_destroy_exit(t_data *data);
int		get_sign(float value);
void	print_data(t_data *data);
int		ft_mouse(t_data *data);
int		ft_mouse_click(int button, int x, int y, t_data *data);
void	toggle_door(t_data *data);

// MAIN
void	init_data(t_data *data);
void	parsing_cub(char *argv);

// PARSING
bool	is_valid_data_extension(char *argv);
void	copy_cub_file(char *argv, t_data *data);
void	where_is_the_map(t_data *data, char **file, int *map_lines);
void	save_map(t_data *data, char **file, char ***map, int *map_lines);
void	check_starting_point(char **map, int map_lines, t_data *data, int j);

// TEXTURES AND COLORS
char	*find_textures_paths(char *file, t_data *data);
void	extract_textures(t_data *data);
int		*find_rgb_colors(char *file, int *colors, int k, t_data *data);
void	extract_valid_colors(t_data *data);
bool	are_colors_and_textures_before_map(t_data *data, int j);

// PARSING MAP
void	parsing_map(t_data *data);
char	*create_first_and_bottom_lines(int max_len, char *x_lines, t_data *data);
char	*fill_line(char *map, int len, int i);
char	**create_new_map(t_data *data, int max_len, char **new_map, char *x_lines);
bool	is_map_closed(char **map, int len, int rows, int i);
void	set_player_position_and_angle(char start_char, t_data *data);

// CLEAN FILE
bool	line_is_not_texture(t_data *data, int i, int *checker);
bool	line_is_not_color(t_data *data, int i, int *checker);
bool	line_is_not_empty(t_data *data, int i);
bool	file_is_clean(t_data *data);
void	file_end_is_clean(t_data *data);

// UTILS
void	print_char_tab(char **tab);
void	err(t_data *data, char *str);
int		count_lines_fd(char *argv);
int		map_line_max_lenght(char **map);
bool	is_valid_char(char c);

// UITILS 2
void	check_colors(char *file, t_data *data);
bool	is_starting_point(char **map, int i, int j);
void	color_is_valid(int *color, t_data *data);
int		skip_whitespaces(char **save, int i, int j, int *start);

//FREE
void	free_char_tab(char **tab);
void	free_all(t_data *data);
void	error_color(int *colors, char **save, t_data *data);

#endif
