/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:56:00 by asolano-          #+#    #+#             */
/*   Updated: 2022/10/06 08:16:02 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include <math.h>

void	spherize(t_map *map, t_point *points)
{
	int	i;
	int	rad[3];

	//pasamos de angulo a radianes 
	rad[X] = map->ang[X] * M_PI / 180;
	rad[Y] = map->ang[Y] * M_PI / 180;
	rad[Z] = map->ang[Z] * M_PI / 180;
	i = 0;
	//recorremos los puntos y les damos valores en los ejes
	//X: (el radio + el eje Z) * (coseno de la longitud) *
	//(seno de la latitud)
	//Y: (el radio + el eje Z) * (seno de la longitud) *
	//(coseno de la latitud)
	//Z: (el radio + el eje Z) * (coseno de la latitud)
	while (i < map->len)
	{
		points[i].axis[X] = (map->radius + points[i].axis[Z]) * \
			cos(points[i].polar[LONG]) * sin(points[i].polar[LAT]);
		points[i].axis[Y] = (map->radius + points[i].axis[Z] * \
			sin(points[i].polar[LONG]) * sin(points[i].polar[LAT]));
		points[i].axis[Z] = (map->radius + points[i].axis[Z] * \
			cos(points[i].polar[LAT]));
		i++;
	}
}

/*
 * Esta función convierte de coordenadas cartesianas a coordenadas polares
 */
void	go_polar(t_map *map)
{
	int		i;
	float	steps_x;
	float	steps_y;

	//almacenamos los "pasos" en cada eje
	steps_x = (M_PI * 2) / (map->limits.axis[X] - 1);
	steps_y = M_PI / (map->limits.axis[Y]);
	//asignamos un radio al mapa
	map->radius = map->limits.axis[X] / (M_PI * 2);
	i = 0;
	//recorremos cada punto
	while (i < map->len)
	{
		map->points[i].polar[LONG] = -(map->points[i].axis[X]) * steps_x;
		if (map->points[i].axis[Y] > 0)
			map->points[i].polar[LAT] = ((map->points[i].axis[Y]) + \
				(map->limits.axis[Y] / 2)) * steps_y - 0.5 * steps_y;
		else
			map->points[i].polar[LAT] = (map->points[i].axis[Y] + \
				(map->limits.axis[Y] / 2) - 1) * steps_y + 0.5 * steps_y;
		i++;
	}
}
