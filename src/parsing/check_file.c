#include "../../includes/cub3d.h"

static int	handle_line_error(t_file *file, char *line, t_tmpmap **listmap);
static void	handle_line_map(int *flg, t_tmpmap **listmap, char *line);
static int	process_line(int *flg, t_file *file, char *line, \
t_tmpmap **listmap);

int	check_file(int fd, t_file *file)
{
	char		*line;
	int			flg;
	t_tmpmap	*listmap;

	flg = 0;
	line = NULL;
	listmap = NULL;
	while (42)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		if (!line)
			return (handle_line_error(file, line, &listmap));
		if (process_line(&flg, file, line, &listmap))
			return (1);
	}
}

static int	handle_line_error(t_file *file, char *line, t_tmpmap **listmap)
{
	if (complete_param(file))
		return (ft_putstr_fd("Error Parameters\n", 2), free(line), 1);
	fill_map_tab(listmap, file);
	return (free(line), lstclear(listmap), 0);
}

static int	process_line(int *flg, t_file *file, char *line, t_tmpmap **listmap)
{
	handle_line_map(flg, listmap, line);
	if (!*flg && fill_param(line, file, flg))
		return (ft_putstr_fd("Error Parameters\n", 2), free(line), 1);
	return (0);
}

static void	handle_line_map(int *flg, t_tmpmap **listmap, char *line)
{
	if (*flg)
	{
		if (line[0] == '\n')
			return ;
		fill_struct_map(listmap, line);
	}
}
