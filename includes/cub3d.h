/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:02:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/04 13:01:08 by ikaismou         ###   ########.fr       */
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
#define PI 3.14159265
#define TILE_SIZE 30
#define FOV_ANGLE 60
#define mapX 8      // map width
#define mapY 8      // map height
#define P2 PI / 2
#define P3 3 * PI / 2
# define DR 0.0174533 //one degre in radiant




typedef struct s_tmpmap
{
	char *line;
	struct s_tmpmap *next;
}				t_tmpmap;

typedef struct	s_file
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
}						t_file;

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
	float px;
	float	py;
	float	pdx;
	float	pdy;
	float pa;
}						t_player;

typedef struct s_data
{
	t_file	*head_file;
	t_winmlx *head_winmlx;
	t_player *head_player;
}				t_data;

int	parsing(char *file, t_data *data);
int	fill_param(char *line, t_file *file, int *flg);
int	complete_param(t_file *file);
void    fill_struct_map(t_tmpmap **map, char *line);
void	fill_map_tab(t_tmpmap **list, t_file *file);
int parse_map(t_file *file);
int complete_param(t_file *file);

//////////////////LIST////////////////////////
t_tmpmap	*lstlast(t_tmpmap *lst);
t_tmpmap	*create_cell(char *line);
void	ft_lstad_back(t_tmpmap **lst, t_tmpmap *new);
int		lstsize(t_tmpmap *lst);
void	lstclear(t_tmpmap **lst);


int ft_init(t_winmlx *winmlx, t_data *data);

#endif
