/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:34:01 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/07/18 18:26:36 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*assign_texture(t_data *data, int side)
{
	int	*pixels;

	if (data->ray.rayDirY >= 0.0 && side == 1)
		pixels = (int *)mlx_get_data_addr(data->txt.img_east,
				&data->img.bpp, &data->img.size_line, &data->img.endian);
	else if (data->ray.rayDirY <= 0.0 && side == 1)
		pixels = (int *)mlx_get_data_addr(data->txt.img_west,
				&data->img.bpp, &data->img.size_line, &data->img.endian);
	else if (data->ray.rayDirX <= 0.0 && side == 0)
		pixels = (int *)mlx_get_data_addr(data->txt.img_north,
				&data->img.bpp, &data->img.size_line, &data->img.endian);
	else
		pixels = (int *)mlx_get_data_addr(data->txt.img_south,
				&data->img.bpp, &data->img.size_line, &data->img.endian);
	return (pixels);
}

static void	update_raycasting(t_data *data, int x)
{
	data->ray.rayDirY = data->ray.diry + data->ray.planey * data->ray.cameraX;
	data->ray.rayDirX = data->ray.dirx + data->ray.planex * data->ray.cameraX;
	data->ray.cameraX = (2 * x) / (double)SCREENWIDTH - 1;
	data->ray.mapX = (int)data->player.pos_y;
	data->ray.mapY = (int)data->player.pos_x;
	if (data->ray.rayDirX == 0)
		data->ray.ddist_x = 1e30;
	else
		data->ray.ddist_x = fabs(1 / data->ray.rayDirX);
	if (data->ray.rayDirY == 0)
		data->ray.ddist_y = 1e30;
	else
		data->ray.ddist_y = fabs(1 / data->ray.rayDirY);
}

static int	hit_detection(t_data *data, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.sd_x < data->ray.sd_y)
		{
			data->ray.sd_x += data->ray.ddist_x;
			data->ray.mapX += data->ray.stepx;
			*side = 0;
		}
		else
		{
			data->ray.sd_y += data->ray.ddist_y;
			data->ray.mapY += data->ray.stepy;
			*side = 1;
		}
		if (data->img.map[data->ray.mapX][data->ray.mapY] == '1')
		hit = 1;
	}
	return (hit);
}

static void	draw_pixels(t_data *data, int *pixels, int x, int side)
{
	double	step;
	int		g;
	int		color;
	int		tex_y;

	g = 0;
	step = 1.0 * TEXHEIGHT / data->ray.line_height;
	extra_draw_pixels(data, x, step);
	g = data->ray.draw_start;
	while (g < data->ray.draw_end)
	{
		tex_y = (int)data->ray.tex_pos & (TEXHEIGHT - 1);
		data->ray.tex_pos += step;
		color = pixels[TEXHEIGHT * tex_y + data->ray.tex_x];
		my_mlx_pixel_put2(data, x, g, color);
		g++;
	}
	g = data->ray.draw_end;
	while (g < SCREENHEIGHT)
	{
		if (g >= 0)
			my_mlx_pixel_put2(data, x, g, data->txt.f_color);
		g++;
	}
}

void	raycasting(t_data *data)
{
	int	x;
	int	*pixels;
	int	hit;
	int	side;

	x = 0;
	while (x < SCREENWIDTH)
	{
		update_raycasting(data, x);
		calculate_side_distances(data);
		if (!hit_detection(data, &side))
			continue ;
		pixels = assign_texture(data, side);
		if (side == 0)
			data->ray.pw_dist = (data->ray.sd_x - data->ray.ddist_x);
		else
			data->ray.pw_dist = (data->ray.sd_y - data->ray.ddist_y);
		calculate_line_height_and_draw_start_end(data);
		calculate_wall_x(data, side);
		calculate_tex_x(data, side);
		draw_pixels(data, pixels, x, side);
		x++;
	}
	mlx_put_image_to_window(data->img.mlx_ptr, data->img.win2_ptr,
		data->img.img2_ptr, 0, 0);
}
