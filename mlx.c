/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 11:41:11 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/27 11:50:03 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	ft_rotate(t_val *fdf, int j, int i)
{
	double	shift_x;
	double	shift_y;

	shift_x = (fdf->map.width / 2);
	shift_y = (fdf->map.height / 2);
	fdf->rx1 = j - shift_x;
	fdf->ry1 = (i - shift_y) * cos(fdf->alpha) +
		(fdf->map.map[i][j] * fdf->map.k) * sin(fdf->alpha);
	fdf->rz1 = -(i - shift_y) * sin(fdf->alpha) +
		(fdf->map.map[i][j] * fdf->map.k) * cos(fdf->alpha);
	fdf->rx2 = fdf->rx1 * cos(fdf->beta) + fdf->rz1 * sin(fdf->beta);
	fdf->ry2 = fdf->ry1;
	fdf->rz2 = -(fdf->rx1) * sin(fdf->beta) - fdf->rz1 * cos(fdf->beta);
	fdf->rx3 = fdf->rx2 * cos(fdf->gamma) + fdf->ry2 * sin(fdf->gamma);
	fdf->ry3 = fdf->rx2 * sin(fdf->gamma) + fdf->ry2 * cos(fdf->gamma);
	fdf->rz3 = fdf->rz2;
	fdf->rx3 = (fdf->rx3 * fdf->scale_x) + (SIZE_W / 2) + fdf->map.move_x;
	fdf->ry3 = (fdf->ry3 * fdf->scale_y) + (SIZE_H / 2) + fdf->map.move_y;
}

static	t_val	*ft_addr_img(t_val *fdf)
{
	fdf->bpp = 5;
	fdf->sl = 1;
	fdf->end = (SIZE_W * SIZE_H);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, SIZE_W, SIZE_H);
	fdf->img_data_addr = mlx_get_data_addr(fdf->img_ptr,
			&fdf->bpp, &fdf->sl, &fdf->end);
	return (fdf);
}

void			ft_draw_img(t_val *fdf)
{
	fdf->i = -1;
	while (++(fdf->i) < (fdf->map.height))
	{
		fdf->j = -1;
		while (++(fdf->j) < (fdf->map.width))
		{
			ft_rotate(fdf, fdf->j, fdf->i);
			fdf->x1 = fdf->rx3;
			fdf->y1 = fdf->ry3;
			if (fdf->j < (fdf->map.width - 1))
			{
				ft_rotate(fdf, fdf->j + 1, fdf->i);
				fdf->x2 = fdf->rx3;
				fdf->y2 = fdf->ry3;
				ft_line(fdf, 1);
			}
			if (fdf->i < (fdf->map.height - 1))
			{
				ft_rotate(fdf, fdf->j, fdf->i + 1);
				fdf->x2 = fdf->rx3;
				fdf->y2 = fdf->ry3;
				ft_line(fdf, 2);
			}
		}
	}
}

int				ft_mlx(t_val *fdf)
{
	fdf->scale_x = (SIZE_W * 0.7) / (fdf->map.width);
	fdf->scale_y = (SIZE_H * 0.7) / (fdf->map.height);
	fdf->alpha = -0.5;
	fdf->beta = -0.5;
	fdf->gamma = 0;
	fdf->map.k = 1;
	fdf->map.move_x = 0;
	fdf->map.move_y = 0;
	fdf->hints = 1;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, SIZE_W, SIZE_H, "fdf");
	ft_addr_img(fdf);
	ft_draw_img(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	hints(fdf);
	mlx_hook(fdf->win_ptr, 2, (1L << 0), deal_key, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
