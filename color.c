/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <kkostrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 11:56:55 by kkostrub          #+#    #+#             */
/*   Updated: 2018/10/10 17:05:53 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	float	calc_percent(t_val *v, t_color c)
{
	if (v->len_x > v->len_y)
	{
		if (c.x == v->x1)
			return (0.0);
		else if (c.x == v->x2)
			return (1.0);
		else
			return ((c.x - v->x1) / (v->x2 - v->x1));
	}
	else
	{
		if (c.y == v->y1)
			return (0.0);
		else if (c.y == v->y2)
			return (1.0);
		else
			return ((c.y - v->y1) / (v->y2 - v->y1));
	}
	return (0);
}

static	int		ft_calc(t_color c, int shift)
{
	int start_tmp;
	int finish_tmp;

	start_tmp = (c.start >> shift) & 0x0000FF;
	finish_tmp = (c.finish >> shift) & 0x0000FF;
	if (start_tmp == finish_tmp)
		return (start_tmp);
	return (start_tmp + (finish_tmp - start_tmp) * c.prc);
}

static	int		bitwise_shift(t_color c)
{
	c.r = ft_calc(c, 16);
	c.g = ft_calc(c, 8);
	c.b = ft_calc(c, 0);
	return (c.r << 16 | c.g << 8 | c.b);
}

int				set_color(t_val *v, t_color c, int flag)
{
	c.start = v->map.map_color[v->i][v->j];
	if (flag == 1)
	{
		if (v->j + 1 >= v->map.width)
			return (v->map.map_color[v->i][v->j]);
		if (v->map.map_color[v->i][v->j] == v->map.map_color[v->i][v->j + 1])
			return (v->map.map_color[v->i][v->j]);
		c.finish = v->map.map_color[v->i][v->j + 1];
	}
	else
	{
		if (v->i + 1 >= v->map.height)
			return (v->map.map_color[v->i][v->j]);
		if (v->map.map_color[v->i][v->j] == v->map.map_color[v->i + 1][v->j])
			return (v->map.map_color[v->i][v->j]);
		c.finish = v->map.map_color[v->i + 1][v->j];
	}
	c.prc = calc_percent(v, c);
	return (bitwise_shift(c));
}

t_val			*set_gradient(t_val *fdf)
{
	t_grad	value;
	int		r;

	value.max_z = find_max(fdf);
	value.min_z = find_min(fdf);
	r = 2;
	value.range = value.max_z - value.min_z;
	if (value.range > 10 && value.range < 100)
		r *= 2;
	if (value.range > 100 && value.range < 1000)
		r *= 20;
	identify_color(fdf, value, r);
	return (fdf);
}
