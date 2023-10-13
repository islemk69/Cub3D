/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:02:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/13 17:40:35 by ikaismou         ###   ########.fr       */
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


# define H_WHITE            0xffffff
# define H_BLACK            0x000000
# define H_RED                0xff0000
# define H_REDDED            0xCC0000
# define H_GREEN            0x00ff00
# define H_DARKGREEN        0x01452c
# define H_BLUE                0x0000ff
# define H_YELLOW            0xffff00
# define H_ORANGE            0xffa500
# define H_PINK                0xffc0cb
# define H_PURPLE            0x800080
# define H_GREY                0x808080
# define SKY				0x77B5FE
#define PI 3.14159265
#define TILE_SIZE 30
#define FOV_ANGLE 60
#define mapX 8      // map width
#define mapY 8      // map height
#define P2 PI / 2
#define P3 3 * PI / 2
# define DR 0.0174533 //one degre in radiant
# define winHeight 1080
# define midHeight winHeight / 2

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
	float	disV;
	float	disH;
	float	disT;
	float	rx;
	float	ry;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	int		r;
	float	ra;
	float   h_redded;
    int     lineH;
    float   ca;
    float   ty_step;
    float   ty_off;
    int     lineOff;
    float   ty;
    float   tx;
}				t_scene;

typedef struct s_tmpmap
{
	char *line;
	struct s_tmpmap *next;
}				t_tmpmap;

typedef struct    s_file
{
	char	**map;
	int		hmap;
	int		wmap;
	int		greather;
	char	*path_to_n;
	char	*path_to_s;
	char	*path_to_w;
	char	*path_to_e;
	char	*color_f_tmp;
	char	*color_s_tmp;
	int		color_floor[3];
	int		color_sky[3];
	char	orientation;
}					t_file;

typedef struct	s_winmlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}						t_winmlx;

typedef struct	s_player
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	bool key_states[65365];
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

//////////////////LIST////////////////////////
t_tmpmap	*lstlast(t_tmpmap *lst);
t_tmpmap	*create_cell(char *line);
void		ft_lstad_back(t_tmpmap **lst, t_tmpmap *new);
int			lstsize(t_tmpmap *lst);
void		lstclear(t_tmpmap **lst);


////////////////////PARSING////////////////////////
int		parsing(char *file, t_data *data);
int		fill_param(char *line, t_file *file, int *flg);
int		complete_param(t_file *file);
void    fill_struct_map(t_tmpmap **map, char *line);
void	fill_map_tab(t_tmpmap **list, t_file *file);
int		parse_map(t_file *file);
int		complete_param(t_file *file);

//////////////////INIT STUCT//////////////////////
int		init_struct(t_data *data, int flg);
void    my_mlx_pixel_put(t_winmlx *draw, int x, int y, int color);


//////////////////MOVEMENTS//////////////////////
int		key_press_hook(int keycode, t_data *data);
int		key_release_hook(int keycode, t_data *data);
void	move(t_data *data);


/////////////////DRAWMAP////////////////////////
void drawmap(t_data *data);

/////////////////SCENE//////////////////////////
void draw_scene(t_data *data, t_scene *scene, int r, float ra);

///////////////////RAYCASTING////////////////////
int		init_game(t_winmlx *winmlx, t_data *data);
void ray_cast(t_data *data, t_scene *scene);

#endif
