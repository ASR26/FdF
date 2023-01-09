/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:03:38 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/21 12:40:08 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/draw_utils.h"

/*
 * Esta función recorre los puntes de la malla del array y dibuja lineas entre:
 * - wire[i] y wire[i + 1]
 * - wire[i] y wire[i + mapsize] (mapsize es cuantos puntos hay por fila)
 */
void	wired(t_meta *meta, t_point *wire)
{
	int	i;

	i = 0;
	//recorremos los puntos
	while (i < meta->map.len)
	{
		//si el punto tiene que ser pintado...
		if (wire[i].paint)
		{
			//si el siguiente punto está en los límites...
			if ((i + 1) % (int)meta->map.limits.axis[X] != 0)
			{
				//dibujamos una línea entre los dos puntos
				draw_line(meta, wire[i], wire[i + 1]);
				//si el modo líneas extra está activado...
				if (meta->map.b_pluslines)
				{
					// si los puntos están en dos filas diferentes
					// dibujamos una línea entre ambos
					if ((i / (int)meta->map.limits.axis[X]) != \
							(meta->map.limits.axis[Y] - 1))
						draw_line(meta, wire[i], wire[i + \
								(int)meta->map.limits.axis[X] + 1]);
				}
			}
			//si los puntos están en la misma columna dibujamos una línea
			//entre ellos
			if ((i / (int)meta->map.limits.axis[X]) != \
			(meta->map.limits.axis[Y] - 1))
				draw_line(meta, wire[i], wire[i + \
				(int)meta->map.limits.axis[X]]);
		}
		i++;
	}
}

/*
 * Esta función da color a todos los puntos del mapa
 */
void	colorize(t_map *map)
{
	int	i;

	i = 0;
	//recorremos todos los puntos y les damos un color según su altura
	while (i < map->len)
	{
		load_color((int)map->limits.axis[Z], map->zmin, \
				&map->points[i], map->colors);
		i++;
	}
}

/*
 * Esta función recorre los puntos del array y dibuja un punto por cada uno
 */
void	doted(t_meta *meta, t_point *proyect)
{
	int	i;

	i = 0;
	//recorremos todos los puntos
	while (i < meta->map.len)
	{
		//si tenemos que pintarlo dibujamos un punto
		if (proyect[i].paint)
			draw_dot(meta, proyect[i], 1);
		i++;
	}
}

/*
 * Esta función sirve para escalar z en caso de que sea necesario
 */
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
