/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:29:25 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/13 17:39:29 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int get_pixel_color(t_texture *texture, int x, int y) {
    return *(int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
}

void draw_texture(t_texture *texture, t_data *data, int lineOff, int lineH, int r, float tx, float *ty, float ty_step)
{
	for (int i = 0; i < lineOff; i++) {
		my_mlx_pixel_put(data->winmlx, r, i, SKY);
	}

	for (int i = 0; i < lineH; i++) {
		float c = get_pixel_color(texture, (int)tx, (int)(*ty));
		my_mlx_pixel_put(data->winmlx, r, i + lineOff, c);
		*ty += ty_step;
	}

	for (int i = lineOff + lineH; i < 1080; i++) {
		my_mlx_pixel_put(data->winmlx, r, i, H_GREY);
	}
}



void draw_scene(t_data *data, t_scene *scene, int r, float ra)
{
    float   h_redded;
    int     lineH;
    float   ca;
    float   ty_step;
    float   ty_off;
    int     lineOff;
    float   ty;
    float   tx;

    h_redded = 1;
    if (scene->disV < scene->disH)
    {
        scene->rx = scene->vx;
        scene->ry = scene->vy;
        scene->disT = scene->disV;
        h_redded = 0;
    }
    else
    {
        scene->rx = scene->hx;
        scene->ry = scene->hy;
        scene->disT = scene->disH;
    }

    ca = data->player->pa - ra;
    if (ca < 0)
        ca += 2 * PI;
    if (ca > 2 * PI)
        ca -= 2 * PI;
    scene->disT = scene->disT * cos(ca);

    lineH = (30 * winHeight) / scene->disT;
    ty_step = 120.0 / (float)lineH;
    ty_off = 0;

    if (lineH > winHeight)
    {
        ty_off = (lineH - winHeight) / 2.0;
        lineH = winHeight;
    }

    lineOff = midHeight - (lineH / 2);
    ty = ty_off * ty_step;
    tx = 0;

    if (h_redded == 1)
    {
        tx = (int)(scene->rx / 2.0) % 30;
        if (ra > 180)
            tx = 29 - tx;
    }
    else
    {
        tx = (int)(scene->ry / 2.0) % 30;
        if (ra > 90 && ra < 270)
            tx = 29 - tx;
    }

    if (h_redded == 1)
    {
        if (ra >= 0 && ra < PI)
            draw_texture(data->stex, data, lineOff, lineH, r, tx, &ty, ty_step);
        else
            draw_texture(data->ntex, data, lineOff, lineH, r, tx, &ty, ty_step);
    }
    else
    {
        if (ra >= PI / 2 && ra < 3 * PI / 2)
            draw_texture(data->wtex, data, lineOff, lineH, r, tx, &ty, ty_step);
        else
            draw_texture(data->etex, data, lineOff, lineH, r, tx, &ty, ty_step);
    }
}
