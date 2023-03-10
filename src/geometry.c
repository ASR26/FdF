/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:09:52 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/10 08:44:44 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include <math.h>

void	traslate(t_point *points, t_point move, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		points[i].axis[X] = points[i].axis[X] + move.axis[X];
		points[i].axis[Y] = points[i].axis[Y] + move.axis[Y];
		points[i].axis[Z] = points[i].axis[Z] + move.axis[Z];
		i++;
	}
}

void	scale(t_point *points, int scale, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		points[i].axis[X] = points[i].axis[X] * scale;
		points[i].axis[Y] = points[i].axis[Y] * scale;
		points[i].axis[Z] = points[i].axis[Z] * scale;
		i++;
	}
}

void	isometric(t_map *map)
{
	map->ang[X] = 30;
	map->ang[Y] = 330;
	map->ang[Z] = 30;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
}

void	parallel(t_map *map)
{
	map->ang[X] = 90;
	map->ang[Y] = 0;
	map->ang[Z] = 0;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
}

void	bending(t_point *points, int len, float range)
{
	int		i;
	float	vv;

	i = 0;
	while (i < len)
	{
		vv = ((points[i].axis[X] * points[i].axis[X]) * (range)) + \
			(points[i].axis[Y] * points[i].axis[Y]) * (range);
		points[i].axis[Z] = points[i].axis[Z] - vv;
		i++;
	}
}
