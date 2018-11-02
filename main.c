/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 11:19:34 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/27 11:25:21 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	ft_usage(void)
{
	ft_putendl("usage: ./fdf [Enter the input file]");
	exit(0);
}

void			ft_error(void)
{
	ft_putendl("error");
	exit(0);
}

void			free_arr(t_val *v)
{
	int i;

	if (v->arr)
	{
		i = -1;
		while (v->arr[++i])
			ft_strdel(&v->arr[i]);
		free(v->arr);
		v->arr = NULL;
	}
}

void			free_line(t_val *v)
{
	if (v->line)
	{
		free(v->line);
		v->line = NULL;
	}
}

int				main(int argc, char **argv)
{
	int		fd;
	t_val	fdf;

	if (argc != 2)
		ft_usage();
	fdf.namefile = ft_strdup(argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error();
	read_file(fd, &fdf);
	ft_mlx(&fdf);
	return (0);
}
