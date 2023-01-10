/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:03:38 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/10 08:47:13 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/draw_utils.h"

void	wired(t_meta *meta, t_point *wire)
{
	int	i;

	i = 0;
	while (i < meta->map.len)
	{
		if (wire[i].paint)
		{
			if ((i + 1) % (int)meta->map.limits.axis[X] != 0)
			{
				draw_line(meta, wire[i], wire[i + 1]);
				if (meta->map.b_pluslines)
				{
					if ((i / (int)meta->map.limits.axis[X]) != \
							(meta->map.limits.axis[Y] - 1))
						draw_line(meta, wire[i], wire[i + \
								(int)meta->map.limits.axis[X] + 1]);
				}
			}
			if ((i / (int)meta->map.limits.axis[X]) != \
			(meta->map.limits.axis[Y] - 1))
				draw_line(meta, wire[i], wire[i + \
				(int)meta->map.limits.axis[X]]);
		}
		i++;
	}
}

void	colorize(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->len)
	{
		load_color((int)map->limits.axis[Z], map->zmin, \
				&map->points[i], map->colors);
		i++;
	}
}

void	doted(t_meta *meta, t_point *proyect)
{
	int	i;

	i = 0;
	while (i < meta->map.len)
	{
		if (proyect[i].paint)
			draw_dot(meta, proyect[i], 1);
		i++;
	}
}

void	z_division(t_point *proyect, float divisor, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		proyect[i].axis[Z] = proyect[i].axis[Z] / divisor;
		i++;
	}
}
