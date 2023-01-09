/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:40:44 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/09 11:16:07 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/matrix.h"
#include "../inc/geometry.h"
#include "../inc/errors.h"
#include "../inc/map_utils.h"
#include "../inc/draw_utils.h"
#include "../inc/utils.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

static void	parse_map(t_meta *meta, t_point *proyect)
{
	z_division(proyect, meta->map.zdivisor, meta->map.len);
	bending(proyect, meta->map.len, meta->map.brange);
	rotate_x(proyect, proyect, meta->map.ang[X], meta->map.len);
	rotate_y(proyect, proyect, meta->map.ang[Y], meta->map.len);
	rotate_z(proyect, proyect, meta->map.ang[Z], meta->map.len);
	orto_proyection (proyect, proyect, meta->map.len);
	scale(proyect, meta->map.scale, meta->map.len);
	traslate(proyect, meta->map.source, meta->map.len);
}

static int limits(t_point *points, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (points[i].axis[X] < (MENU_WIDTH + FIT_MARGIN) || \
				points[i].axis[X] > (WINX - FIT_MARGIN))
			return (1);
		if (points[i].axis[Y] < FIT_MARGIN || \
				points[i].axis[Y] > (WINY - FIT_MARGIN))
			return (1);
		i++;
	}
	return (0);
}

static void go_fit(t_meta *meta, t_point *proyect)
{
	meta->map.source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	meta->map.source.axis[Y] = WINY / 2;
	meta->map.source.axis[Z] = 0;
	copy_map(meta->map.points, proyect, meta->map.len);
	parse_map(meta, proyect);
	while (!(limits(proyect, meta->map.len)))
	{
		copy_map(meta->map.points, proyect, meta->map.len);
		parse_map(meta, proyect);
		meta->map.scale = meta->map.scale + 0.2;
	}
}


void	drawing(t_meta *meta, t_point *proyect, int fit)
{
	if (fit)
		go_fit(meta, proyect);
	if (meta->map.b_lines)
		wired(meta, proyect);
	if (meta->map.b_dots)
		doted(meta, proyect);
}


int	draw_map(t_meta *meta, int fit)
{
	t_point	*proyect;
	clock_t	t;

	t = clock();
	proyect = malloc (meta->map.len * sizeof(t_point));
	if (proyect == NULL)
		terminate(ERR_MEM);
	meta->map.renders = meta->map.renders + 1;
	generate_background(meta, meta->map.colors.backcolor, \
			meta->map.colors.menucolor);
	copy_map(meta->map.points, proyect, meta->map.len);
	parse_map(meta, proyect);
	drawing(meta, proyect, fit);
	mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, \
			meta->bitmap.img, 0, 0);
	draw_menu(meta);
	free(proyect);
	t = clock() - t;
	meta->map.performance = ((double)t) / CLOCKS_PER_SEC;
	return (1);
}
