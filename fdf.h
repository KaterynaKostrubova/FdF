/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 12:10:34 by kkostrub          #+#    #+#             */
/*   Updated: 2018/07/27 12:19:03 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "math.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define SIZE_W 1200
# define SIZE_H 800
# define ROTATE 0.1
# define ROT_X_P 125
# define ROT_X_N 126
# define ROT_Y_P 124
# define ROT_Y_N 123
# define ZOOM_P 69
# define ZOOM_N 78
# define LARGE 12
# define LESS 13
# define COLOR 49
# define UP 91
# define DOWN 84
# define LEFT 86
# define RIGHT 88
# define HIDE 6
# define SHOW 7

typedef struct		s_map
{
	float			**map;
	int				**map_color;
	int				x;
	int				y;
	int				height;
	int				width;
	float			k;
	int				move_x;
	int				move_y;
}					t_map;

typedef struct		s_val
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			*img_data_addr;
	void			*img_ptr;
	int				bpp;
	int				sl;
	int				end;
	int				hints;
	float			x1;
	float			y1;
	float			x2;
	float			y2;
	float			rx1;
	float			ry1;
	float			rz1;
	float			rx2;
	float			ry2;
	float			rz2;
	float			rx3;
	float			ry3;
	float			rz3;
	int				dx;
	int				dy;
	int				len_x;
	int				len_y;
	int				len;
	int				ret;
	char			**arr;
	char			*line;
	int				len_line;
	int				len_first;
	char			*namefile;
	float			scale_x;
	float			scale_y;
	float			scale_z;
	float			alpha;
	float			beta;
	float			gamma;
	int				i;
	int				j;
	struct s_map	map;
}					t_val;

typedef struct		s_color
{
	float			x;
	float			y;
	float			d;
	float			z;
	unsigned int	color;
	int				r;
	int				g;
	int				b;
	float			prc;
	int				start;
	int				finish;
}					t_color;

typedef struct		s_parse
{
	int				fd;
	int				j;
	int				i;
	char			*c;
	int				l;
}					t_parse;

typedef struct		s_grad
{
	int max_z;
	int min_z;
	int range;
	int tmp_min;
	int n;
	int next;
}					t_grad;

void				ft_error(void);
void				free_arr(t_val *v);
void				free_line(t_val *v);
void				read_file(int fd, t_val *v);
int					ft_mlx(t_val *fdf);
void				ft_draw_img(t_val *fdf);
void				ft_line(t_val *v, int flag);
int					deal_key(int key, t_val *fdf);
void				change_color(t_val *fdf);
void				ft_put_string(t_val *fdf, int zoom, int moov);
void				hints(t_val *fdf);
int					set_color(t_val *v, t_color c, int flag);
t_val				*set_gradient(t_val *fdf);
int					is_zero(char *c);
int					find_max(t_val *fdf);
int					find_min(t_val *fdf);
void				identify_color(t_val *fdf, t_grad value, int r);

#endif
