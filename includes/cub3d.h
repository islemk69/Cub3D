/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:02:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/18 19:24:58 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>

# define H_WHITE	0xffffff
# define H_BLACK 0x000000
# define H_PINK 0xffc0cb
# define H_GREY 0x808080
# define PI 3.14159265
# define TILE_SIZE 32
# define FOV_ANGLE 60.0
# define DR 0.0174533
# define WINHEIGHT 1080

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct s_scene
{
	float	dis_v;
	float	dis_h;
	float	dist;
	float	rx;
	float	ry;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	int		r;
	float	ra;
	float	h_redded;
	int		line_h;
	float	ca;
	float	ty_step;
	float	ty_off;
	int		line_off;
	float	ty;
	float	tx;
	int		dof;
	int		mx;
	int		my;
	float	xo;
	float	yo;

}				t_scene;

typedef struct s_tmpmap
{
	char			*line;
	struct s_tmpmap	*next;
}				t_tmpmap;

typedef struct s_file
{
	char			**map;
	int				hmap;
	int				wmap;
	int				greather;
	char			*path_to_n;
	char			*path_to_s;
	char			*path_to_w;
	char			*path_to_e;
	char			*color_f_tmp;
	char			*color_s_tmp;
	int				color_floor[3];
	unsigned int	color_floor_hex;
	int				color_sky[3];
	unsigned int	color_sky_hex;
	char			orientation;
}					t_file;

typedef struct s_winmlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}						t_winmlx;

typedef struct s_player
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	bool	key_states[65365];
}						t_player;

typedef struct s_data
{
	t_file		*file;
	t_winmlx	*winmlx;
	t_player	*player;
	t_scene		*scene;
	t_texture	*ntex;
	t_texture	*stex;
	t_texture	*wtex;
	t_texture	*etex;
	t_texture	*skytex;
}				t_data;

/////////////////UTILS////////////////////////
int			is_empty(char *line);
int			check_char(char *str, int *p, t_file *file);
void		replace_space(char *line);
int			only_wall(char *str);
void		reset_player_position_on_map(t_data *data);
void		drawsquare(t_data *data, int color, int x, int y);
int			is_player(char p);
int			only_wall(char *str);
void		ft_free_all(t_data *data, int flg);
//////////////////LIST////////////////////////
t_tmpmap	*lstlast(t_tmpmap *lst);
t_tmpmap	*create_cell(char *line);
void		ft_lstad_back(t_tmpmap **lst, t_tmpmap *new);
int			lstsize(t_tmpmap *lst);
void		lstclear(t_tmpmap **lst);
////////////////////PARSING////////////////////////
int			parsing(char *file, t_data *data);
int			param(char *line, t_file *file, int *flg);
int			check_player(char **map);
int			complete_param(t_file *file);
int			fill_struct_map(t_tmpmap **map, char *line);
int			fill_map_tab(t_tmpmap **list, t_file *file);
int			parse_map(t_file *file);
int			complete_param(t_file *file);
int			open_file(char *file, t_data *data, int flg);
int			check_path(t_data *data);
int			check_map(char **map);
int			check_file(int fd, t_file *file);
int			fill_param(t_file *file, char **l_split);
int			check_color(char **color_split, char *color, int i, int nb);
int			get_colors(char *color, int mod, t_file *file);
size_t		ft_tablen(char **arr);
//////////////////INIT STUCT//////////////////////
int			init_struct(t_data *data, int flg);
void		my_mlx_pixel_put(t_winmlx *draw, int x, int y, int color);
//////////////////MOVEMENTS//////////////////////
int			key_press_hook(int keycode, t_data *data);
int			key_release_hook(int keycode, t_data *data);
void		move(t_data *data);
/////////////////DRAWMAP////////////////////////
void		drawmap(t_data *data, int i, int j, int x);
/////////////////SCENE//////////////////////////
void		draw_scene(t_data *data, t_scene *scene, int r, float ra);
///////////////////RAYCASTING////////////////////
int			init_game(t_winmlx *winmlx, t_data *data);
void		ray_cast(t_data *data, t_scene *scene);
void		looking_vertical(t_scene *scene, t_data *data);
void		looking_horizontal(t_scene *scene, t_data *data);
void		check_vertical_line(t_scene *s, t_data *d);
void		check_horizontal_line(t_scene *s, t_data *d);
float		dist(float ax, float ay, float bx, float by);
int			key_press_hook(int keycode, t_data *data);
int			key_release_hook(int keycode, t_data *data);
bool		is_collision(t_data *data, float newx, float newy);

#endif
