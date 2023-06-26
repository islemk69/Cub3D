/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:02:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/20 16:28:21 by ikaismou         ###   ########.fr       */
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
	t_tmpmap *head_map;
	char	**map;
	char	*path_to_n;
	char	*path_to_s;
	char	*path_to_w;
	char	*path_to_e;
	int		[3]color_floor;
	int		[3]color_sky;
}						t_file;

typedef struct s_data
{
	t_file	*head_file;
}				t_data;

int	parsing(char *file, t_data *data);
int	fill_param(char *line, t_file *file, int *flg);
int	complete_param(t_file *file);
void    fill_struct_map(t_tmpmap **map, char *line);

//////////////////LIST////////////////////////
t_tmpmap	*lstlast(t_tmpmap *lst);
t_tmpmap	*create_cell(char *line);
void	ft_lstad_back(t_tmpmap **lst, t_tmpmap *new);
int		lstsize(t_tmpmap *lst);
void	lstclear(t_tmpmap **lst);

#endif