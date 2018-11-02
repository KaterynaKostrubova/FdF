/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 11:52:13 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/27 11:56:06 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	make_img(t_val *fdf, int x, int y, int color)
{
	if (x >= 0 && x < SIZE_W && y >= 0 && y < SIZE_H)
		*(int*)(fdf->img_data_addr + ((x + y * SIZE_W) * 4)) = color;
}

static	void	if_len_x_bigger(t_val *v, int flag)
{
	t_color	c;

	c.x = v->x1;
	c.y = v->y1;
	c.d = -v->len_x;
	v->len++;
	while (v->len--)
	{
		c.color = set_color(v, c, flag);
		make_img(v, c.x, c.y, c.color);
		c.x += v->dx;
		c.d += 2 * v->len_y;
		if (c.d > 0)
		{
			c.d -= 2 * v->len_x;
			c.y += v->dy;
		}
	}
}

static	void	if_len_y_bigger(t_val *v, int flag)
{
	t_color	c;

	c.x = v->x1;
	c.y = v->y1;
	c.d = -v->len_y;
	v->len++;
	while (v->len--)
	{
		c.color = set_color(v, c, flag);
		make_img(v, c.x, c.y, c.color);
		c.y += v->dy;
		c.d += 2 * v->len_x;
		if (c.d > 0)
		{
			c.d -= 2 * v->len_y;
			c.x += v->dx;
		}
	}
}

void			ft_line(t_val *v, int flag)
{
	v->dx = (v->x2 - v->x1 >= 0 ? 1 : -1);
	v->dy = (v->y2 - v->y1 >= 0 ? 1 : -1);
	v->len_x = ((v->x2 - v->x1) >= 0) ? (v->x2 - v->x1) :
		(v->x2 - v->x1) * (-1);
	v->len_y = ((v->y2 - v->y1) >= 0) ? (v->y2 - v->y1) :
		(v->y2 - v->y1) * (-1);
	v->len = (v->len_x > v->len_y) ? v->len_x : v->len_y;
	if (v->len == 0)
		make_img(v, v->x1, v->y1, v->map.map_color[v->i][v->j]);
	if (v->len_y <= v->len_x)
		if_len_x_bigger(v, flag);
	else
		if_len_y_bigger(v, flag);
}
