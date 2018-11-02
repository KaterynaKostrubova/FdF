/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 12:01:46 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/27 12:01:56 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		check_num(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	if (s1[0] == '0' && s1[1] == ',')
		return (0);
	return (1);
}

int				is_zero(char *c)
{
	if (check_num(c, "0") == 0)
		return (1);
	return (0);
}

int				find_max(t_val *fdf)
{
	int max;
	int i;
	int j;

	j = 0;
	i = 0;
	max = 0;
	while (j < fdf->map.height)
	{
		i = 0;
		while (i < fdf->map.width)
		{
			if (fdf->map.map[j][i] > max)
				max = fdf->map.map[j][i];
			i++;
		}
		j++;
	}
	return (max);
}

int				find_min(t_val *fdf)
{
	int min;
	int i;
	int j;

	j = 0;
	min = 0;
	while (j < fdf->map.height)
	{
		i = 0;
		while (i < fdf->map.width)
		{
			if (fdf->map.map[j][i] < min)
				min = fdf->map.map[j][i];
			i++;
		}
		j++;
	}
	return (min);
}

void			identify_color(t_val *fdf, t_grad value, int r)
{
	fdf->j = -1;
	while (++fdf->j < fdf->map.height)
	{
		fdf->i = -1;
		while (++fdf->i < fdf->map.width)
		{
			if (fdf->map.map[fdf->j][fdf->i] == value.min_z)
				fdf->map.map_color[fdf->j][fdf->i] = 0xff0000;
			else if (fdf->map.map[fdf->j][fdf->i] > value.min_z
					&& fdf->map.map[fdf->j][fdf->i] < value.min_z + r)
				fdf->map.map_color[fdf->j][fdf->i] = 0xff3333;
			else if (fdf->map.map[fdf->j][fdf->i] > value.min_z
					&& fdf->map.map[fdf->j][fdf->i] < value.min_z + (r * 2))
				fdf->map.map_color[fdf->j][fdf->i] = 0xff6666;
			else if (fdf->map.map[fdf->j][fdf->i] > value.min_z
					&& fdf->map.map[fdf->j][fdf->i] < value.min_z + (r * 3))
				fdf->map.map_color[fdf->j][fdf->i] = 0xff9999;
			else if (fdf->map.map[fdf->j][fdf->i] > value.min_z
					&& fdf->map.map[fdf->j][fdf->i] < value.min_z + (r * 4))
				fdf->map.map_color[fdf->j][fdf->i] = 0xffcccc;
			else
				fdf->map.map_color[fdf->j][fdf->i] = 0xffffff;
		}
	}
}
