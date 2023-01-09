/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:19:02 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/23 11:47:52 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "../inc/defines.h"
#include "../inc/utils.h"

/*
 * Esta función devuelve el número de elementos en una línea
 */
int	line_elems(char **elems)
{
	int i;

	i = 0;
	while (elems[i] && elems[i][0] != '\n')
		i++;
	return (i);
}

/*
 * Esta función comprueba que el punto es válido
 */
int	valid_point(char *value)
{
	int	valid;

	valid = 0;
	if (*value == '-' || *value == '+' || ft_isdigit(*value))
		valid++;
	value++;
	while (ft_isdigit(*value))
	{
		value++;
		valid++;
	}
	if (valid == 0)
		return (0);
	else
		return (1);
}



/*
 * Esta función nos sirve para ajustar los límites de z que encontremos en el
 * mapa
 */
void	z_limits(char **splitted, t_map *map)
{
	int	i;
	int	valor;

	i = 0;
	//recorremos el array de números (en formato caracter)
	while (splitted[i])
	{
		//a valor le damos el valor numérico del primer elemeto del array
		valor = ft_atoi(&splitted[i][0]);
		//si el límite máximo de z es menor que el valor le asignamos este
		//nuevo valor
		if (map->limits.axis[Z] < valor)
			map->limits.axis[Z] = valor;
		//si el límite menor es mayor que el valor le asignamos este nuevo
		//valor
		if (map->zmin > valor)
			map->zmin = valor;
		i++;
	}
}

//Asignamos los valores de color predeterminados al mapa
static void	map_ini_colors(t_map *map)
{
	map->colors.backcolor = BACK_COLOR;
	map->colors.menucolor = MENU_COLOR;
	map->colors.bottomcolor = BOTTOM_COLOR;
	map->colors.groundcolor = GROUND_COLOR;
	map->colors.topcolor = TOP_COLOR;
}


void	map_ini(t_map *map, int total)
{
	//si total es diferente de 0 inicializamos la longitud y los limites
	//a cero e inicializamos el resto de variables de la estructura
	if (total)
	{
		map->len = 0;
		map->limits.axis[X] = 0;
		map->limits.axis[Y] = 0;
		map->limits.axis[Z] = 0;
		map->zmin = 0;
	}
	map->b_lines = 1;
	map->b_dots = 0;
	map->b_pluslines = 0;
	map->b_geo = 0;
	map->b_stars = 0;
	map->b_shadow = 1;
	map->scale = 1;
	map->zdivisor = 1;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
	map->source.axis[Z] = 0;
	map->ang[X] = 0;
	map->ang[Y] = 0;
	map->ang[Z] = 0;
	map_ini_colors(map);
}
