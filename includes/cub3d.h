/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:02:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/02 16:38:09 by ikaismou         ###   ########.fr       */
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
# include <unistd.h>

typedef struct s_tmpmap
{
	char *line;
	struct s_tmpmap *next;
}				t_tmpmap;

typedef struct	s_file
{
	char	**map;
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
	void	*grass;
	void	*wall;
	void	*perso;
	int		img_width;
	int		img_height;
}						t_winmlx;

typedef struct	s_player
{
	int posx;
	int	posy;
	int	startposx;
	int	startposy;
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
