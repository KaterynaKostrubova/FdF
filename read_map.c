/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 11:26:10 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/27 11:39:39 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		validate(t_val *v)
{
	int i;

	i = 0;
	if (!(v->arr = ft_strsplit(v->line, ' ')))
		ft_error();
	while (v->arr[i] != 0)
	{
		if (!(ft_atoi(v->arr[i]) > 0) && !(ft_atoi(v->arr[i]) < 0)
				&& !(is_zero(v->arr[i])))
			ft_error();
		v->len_line++;
		i++;
	}
	if (v->map.width == -1)
		v->len_first = v->len_line;
	else if (v->len_first != v->len_line)
		return (0);
	v->len_line = 0;
	free_arr(v);
	return (v->len_first);
}

static	t_val	*parse_color(t_val *v, t_parse p)
{
	p.i = -1;
	while (++p.i < v->map.width)
	{
		p.c = v->arr[p.i];
		if ((p.c = ft_strchr(v->arr[p.i], ',')))
		{
			p.l = 0;
			while (p.c[p.l + 3] != '\0')
			{
				if (!(ft_isdigit(p.c[p.l + 3])) && !(p.c[p.l + 3] >= 'A'
					&& p.c[p.l + 3] <= 'F') && !(p.c[p.l + 3] >= 'a'
						&& p.c[p.l + 3] <= 'f'))
					ft_error();
				p.l++;
			}
			v->map.map_color[p.j][p.i] = ft_atoi_base(p.c + 3, 16);
		}
		else
			v->map.map_color[p.j][p.i] = 0xffffff;
		v->map.map[p.j][p.i] = ft_atoi(v->arr[p.i]);
	}
	free_arr(v);
	free_line(v);
	return (v);
}

static	int		make_map(t_val *v)
{
	t_parse		p;

	p.j = -1;
	if ((p.fd = open(v->namefile, O_RDONLY)) < 0)
		ft_error();
	while ((v->ret = get_next_line(p.fd, &v->line)) == 1)
	{
		if (!(v->arr = ft_strsplit(v->line, ' ')))
			ft_error();
		if (!(v->map.map_color[++p.j] = (int *)malloc(sizeof(int)
						* v->map.width)))
			ft_error();
		if (!(v->map.map[p.j] = (float *)malloc(sizeof(float) * v->map.width)))
			ft_error();
		parse_color(v, p);
	}
	close(p.fd);
	return (0);
}

static	void	check_color(t_val *fdf)
{
	int flag;
	int i;
	int j;

	i = 0;
	flag = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			if (fdf->map.map_color[i][j] != 0xffffff)
			{
				flag = 1;
				break ;
			}
			j++;
		}
		if (flag == 1)
			break ;
		i++;
		j = 0;
	}
	if (flag == 0)
		set_gradient(fdf);
}

void			read_file(int fd, t_val *v)
{
	v->map.height = 0;
	v->len_first = 0;
	v->len_line = 0;
	v->map.width = -1;
	while ((v->ret = get_next_line(fd, &v->line)) == 1)
	{
		v->map.height++;
		if (!(v->map.width = validate(v)))
			ft_error();
		v->len_first = v->map.width;
		free_line(v);
	}
	close(fd);
	if (v->ret >= 0)
	{
		if (!(v->map.map = (float **)malloc(sizeof(float *) * v->map.height)))
			ft_error();
		if (!(v->map.map_color = (int **)malloc(sizeof(int *) * v->map.height)))
			ft_error();
		make_map(v);
		check_color(v);
	}
	else
		ft_error();
}
