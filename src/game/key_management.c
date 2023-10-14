#include "../../includes/cub3d.h"

int	key_press_hook(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < 65365)
		data->player->key_states[keycode] = true;
	return (0);
}

int	key_release_hook(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < 65365)
		data->player->key_states[keycode] = false;
	return (0);
}

bool	is_collision(t_data *data, float newx, float newy)
{
	int	map_posx;
	int	map_posy;

	map_posx = newx / 30;
	map_posy = newy / 30;
	if (map_posx >= 0 && map_posy >= 0 && \
	map_posy < data->file->hmap && map_posx < data->file->wmap && \
	data->file->map[map_posy][map_posx] == '1')
		return (true);
	return (false);
}
