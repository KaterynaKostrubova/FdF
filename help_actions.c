/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 12:42:02 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/31 12:42:09 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	show_hints(t_val *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			950, 10, 0x00FFFF, "Show hints: X");
}

void			hints(t_val *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			950, 10, 0x00FFFF, "Hide hints: Z");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			10, 730, 0x00FFFF, "MOOV UP/DOWN: NUM 8 , NUM 2");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			10, 750, 0x00FFFF, "MOOV LEFT/RIGHT: NUM 4 , NUM 6");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			950, 730, 0x00FFFF, "Change Z: Q , W");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			950, 710, 0x00FFFF, "ZOOM: NUM - , NUM +");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			550, 730, 0x00FFFF, "Rotate X: <, >");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			550, 750, 0x00FFFF, "Rotate Y: ^, v");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			950, 750, 0x00FFFF, "Change color: [space]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
			10, 10, 0x00FFFF, "Exit: [esc]");
}

void			ft_put_string(t_val *fdf, int zoom, int moov)
{
	if (zoom == 1)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
				500, 700, 0xFF0000, "ATTENTION: minimum size!");
	if (zoom == 2)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
				500, 700, 0xFF0000, "ATTENTION: maximum size!");
	if (moov == 1)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 400,
				400, 0xFF0000, "ATTENTION: image is hidden at the bottom!");
	if (moov == 2)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
				400, 400, 0xFF0000, "ATTENTION: image is hidden at the top!");
	if (moov == 3)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
				400, 400, 0xFF0000, "ATTENTION: image is hidden on the left!");
	if (moov == 4)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
				400, 400, 0xFF0000, "ATTENTION: image is hidden on the right!");
	if (fdf->hints == 1)
		hints(fdf);
	if (fdf->hints == 0)
		show_hints(fdf);
}

void			change_color(t_val *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			if (fdf->map.map_color[i][j] == 0xffffff)
				fdf->map.map_color[i][j] = 0xff0000;
			else if (fdf->map.map_color[i][j] == 0xff0000)
				fdf->map.map_color[i][j] = 0x00ff00;
			else if (fdf->map.map_color[i][j] == 0x00ff00)
				fdf->map.map_color[i][j] = 0xff;
			else if (fdf->map.map_color[i][j] == 0xff)
				fdf->map.map_color[i][j] = 0xffffff;
			else if (fdf->map.map_color[i][j] == 0x00)
				fdf->map.map_color[i][j] = 0xffffff;
			else
				fdf->map.map_color[i][j] = fdf->map.map_color[i][j] << 4;
			j++;
		}
		i++;
	}
}
