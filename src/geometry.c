/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:09:52 by asolano-          #+#    #+#             */
/*   Updated: 2022/10/03 08:32:28 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include <math.h>


/*
 * Recorre todos los puntos y añade la traslacion de 'move'
 */

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

/*
 * Recorre los puntos y multiplica por la escala
 */
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

/*
 * Esta función ajusta los parámetros para vista isométrica
 */
void	isometric(t_map *map)
{
	map->b_geo = 0;
	map->ang[X] = 30;
	map->ang[Y] = 330;
	map->ang[Z] = 30;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
}

/*
 * Esta función ajusta los parámetros para vista paralela
 */
void	parallel(t_map *map)
{
	map->b_geo = 0;
	map->ang[X] = 90;
	map->ang[Y] = 0;
	map->ang[Z] = 0;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
}

/*
 * esta función permitirá "doblar" la proyección en relación al rango y a la
 * posición en x y en y, cuanto más alejado del centro más se aleja
 */
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
