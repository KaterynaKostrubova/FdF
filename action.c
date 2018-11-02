/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 12:02:21 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/27 12:09:58 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		ft_zoom(t_val *fdf, int key)
{
	if (key == ZOOM_P)
	{
		if (fdf->scale_x >= SIZE_W * 0.7 || fdf->scale_y >= SIZE_H * 0.7)
			return (2);
		fdf->scale_x *= 1.1;
		fdf->scale_y *= 1.1;
	}
	else if (key == ZOOM_N)
	{
		if (fdf->scale_x <= 0.3 || fdf->scale_y <= 0.3)
			return (1);
		else
		{
			fdf->scale_x /= 1.1;
			fdf->scale_y /= 1.1;
		}
	}
	return (0);
}

static	int		ft_moov(t_val *fdf, int key)
{
	if (key == DOWN)
	{
		if (fdf->map.move_y >= SIZE_H)
			return (1);
		fdf->map.move_y += 20;
	}
	if (key == UP)
	{
		if (fdf->map.move_y <= -SIZE_H)
			return (2);
		fdf->map.move_y -= 20;
	}
	if (key == LEFT)
	{
		if (fdf->map.move_x <= -SIZE_W)
			return (3);
		fdf->map.move_x -= 20;
	}
	if (key == RIGHT)
	{
		if (fdf->map.move_x >= SIZE_W)
			return (4);
		fdf->map.move_x += 20;
	}
	return (0);
}

static	t_val	*ft_conditions(t_val *fdf, int key)
{
	if (key == ROT_X_N)
		fdf->alpha -= ROTATE;
	if (key == ROT_X_P)
		fdf->alpha += ROTATE;
	if (key == ROT_Y_N)
		fdf->beta -= ROTATE;
	if (key == ROT_Y_P)
		fdf->beta += ROTATE;
	if (key == COLOR)
		change_color(fdf);
	if (key == LARGE)
		fdf->map.k += 0.1;
	if (key == LESS)
		fdf->map.k -= 0.1;
	if (key == HIDE)
		fdf->hints = 0;
	if (key == SHOW)
		fdf->hints = 1;
	return (fdf);
}

static	t_val	*calc_move(t_val *fdf, int key)
{
	int zoom;
	int moov;

	moov = 0;
	zoom = 0;
	ft_conditions(fdf, key);
	if (key == ZOOM_P || key == ZOOM_N)
		zoom = ft_zoom(fdf, key);
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		moov = ft_moov(fdf, key);
	ft_draw_img(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	ft_put_string(fdf, zoom, moov);
	return (fdf);
}

int				deal_key(int key, t_val *fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	else
	{
		ft_bzero(fdf->img_data_addr, SIZE_W * SIZE_H * 5);
		calc_move(fdf, key);
	}
	return (0);
}
