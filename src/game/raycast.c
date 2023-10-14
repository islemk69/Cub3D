/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:29:27 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/14 14:23:39 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float dist(float ax, float ay, float bx, float by, float ang)
{
    (void)ang;
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void ray_cast(t_data *data, t_scene *scene)
{
    int dof, mx, my, r;
    float ra, xo, yo;
    ra = data->player->pa - DR * 30;
    xo = 0;
    yo = 0;
    for (r = 0; r < 1920; r++)
    {
        dof = 0;
        scene->disH = 100000000;
        scene->hx=data->player->px;
        scene->hy=data->player->py;
        float aTan = -1 / tan(ra);
        if (ra > PI) // looking up
        {
            scene->ry = (float)(((int)data->player->py / 30) * 30) - 0.0001;
            scene->rx = (data->player->py - scene->ry) * aTan + data->player->px;
            yo = -30;
            xo = -yo * aTan;
        }
        else if (ra < PI) // looking down
        {
            scene->ry = (float)(((int)data->player->py / 30) * 30) + 30;
            scene->rx = (data->player->py - scene->ry) * aTan + data->player->px;
            yo = 30;
            xo = -yo * aTan;
        }
        else //looking straight left or right
        {
            scene->rx = data->player->px;
            scene->ry = data->player->py;
            dof = data->file->greather;
        }
        while (dof < data->file->greather)
        {
            mx = (int)(scene->rx / 30);
            my = (int)(scene->ry / 30);

            if (mx >= 0 && mx < data->file->wmap && my >= 0 && my < data->file->hmap && data->file->map[my][mx] == '1')
            {
                scene->hx = scene->rx;
                scene->hy = scene->ry;
                scene->disH = dist(data->player->px, data->player->py, scene->hx, scene->hy, ra); // Corrigé ici
                dof = data->file->greather;
            }
            else
            {
                scene->rx += xo;
                scene->ry += yo;
                dof += 1;
            }
        }
        // Check vertical lines
        dof = 0;
        scene->vx=data->player->px;
        scene->vy=data->player->py;
        scene->disV = 1000000;
        
        float nTan = -tan(ra);
        if (ra > P2 && ra < P3) // looking left
        {
            scene->rx = (float)(((int)data->player->px / 30) * 30) - 0.0001;
            scene->ry = (data->player->px - scene->rx) * nTan + data->player->py;
            xo = -30;
            yo = -xo * nTan;
        }
        else if (ra < P2 || ra > P3) // looking right
        {
            scene->rx = (float)(((int)data->player->px / 30) * 30) + 30;
            scene->ry = (data->player->px - scene->rx) * nTan + data->player->py;
            xo = 30;
            yo = -xo * nTan;
        }
        else // looking straight up and down
        {
            scene->rx = data->player->px;
            scene->ry = data->player->py;
            dof = data->file->greather;
        }

        while (dof < data->file->greather)
        {
            mx = (int)(scene->rx / 30);
            my = (int)(scene->ry / 30);

            if (mx >= 0 && mx < data->file->wmap && my >= 0 && my < data->file->hmap && data->file->map[my][mx] == '1')
            {
                scene->vx = scene->rx;
                scene->vy = scene->ry;
                scene->disV = dist(data->player->px, data->player->py, scene->vx, scene->vy, ra); // Corrigé ici
                break ;
            }
            else
            {
                scene->rx += xo;
                scene->ry += yo;
                dof += 1;
            }
        }
        scene->h_redded = 1;
        if (scene->disV < scene->disH)
        {
            scene->rx = scene->vx;
            scene->ry = scene->vy;
            scene->disT = scene->disV;
            scene->h_redded = 0;
        }
        else
        {
            scene->rx = scene->hx;
            scene->ry = scene->hy;
            scene->disT = scene->disH;
        }
        draw_scene(data, scene, r , ra);
        ra += DR * (60.0 / 1920.0);
        if (ra < 0)   
            ra += 2 * PI;       
        if (ra > 2 * PI)
            ra -= 2 * PI;
    }
}