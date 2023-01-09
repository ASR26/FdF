/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:40:44 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/23 10:44:56 by asolano-         ###   ########.fr       */
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

/*
 * Esta función se encarga de modificar los puntos en el espacio
 */
static void	parse_map(t_meta *meta, t_point *proyect)
{
	//Escalamos Z según el tamaño del mapa
	z_division(proyect, meta->map.zdivisor, meta->map.len);
	//doblamos el mapa la cantidad que sea
	bending(proyect, meta->map.len, meta->map.brange);
	//si esta en modo geo hacemos el mapa esférico
	if (meta->map.b_geo)
		spherize(&meta->map, proyect);
	//rotamos los ejes
	rotate_x(proyect, proyect, meta->map.ang[X], meta->map.len);
	rotate_y(proyect, proyect, meta->map.ang[Y], meta->map.len);
	rotate_z(proyect, proyect, meta->map.ang[Z], meta->map.len);
	//si está en modo geo y tiene el modo shadow llamamos a la función shadow
	//que eliminará la parte que no sería visible si el objeto fuera opaco
	if (meta->map.b_geo && meta->map.b_shadow)
		shadow (proyect, meta->map.len);
	orto_proyection (proyect, proyect, meta->map.len);
	scale(proyect, meta->map.scale, meta->map.len);
	traslate(proyect, meta->map.source, meta->map.len);
}

/*
 *  Esta función comprueba si algún punto está fuera de los límites de la pantalla
 */
static int limits(t_point *points, int len)
{
	int	i;

	i = 0;
	//recorriendo todos los puntos
	while (i < len)
	{
		//si algún punto esta fuera de los límites de la pantalla devolvemos 1,
		//si no devolvemos 0
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

/*
 * Esta función se repite hasta que consigamos la escala necesaria para que
 * el mapa quede ajustado a la pantalla
 */
static void go_fit(t_meta *meta, t_point *proyect)
{
	//al eje x de source le damos el valor del pixel central respecto a x
	meta->map.source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	//al eje y de source le damos el valor del pixel central respecto a y
	meta->map.source.axis[Y] = WINY / 2;
	//la altura la ponemos a 0
	meta->map.source.axis[Z] = 0;
	//copiamos len puntos desde el mapa a proyect
	copy_map(meta->map.points, proyect, meta->map.len);
	//modificamos los puntos en el espacio
	parse_map(meta, proyect);
	//mientras el mapa no esté en los límites cambiamos la escala para ajustarlo
	while (!(limits(proyect, meta->map.len)))
	{
		copy_map(meta->map.points, proyect, meta->map.len);
		parse_map(meta, proyect);
		meta->map.scale = meta->map.scale + 0.2;
	}
}


void	drawing(t_meta *meta, t_point *proyect, int fit)
{
	//si las estrellas están activas las dibujamos
	if (meta->map.b_stars)
		generate_stars(meta);
	//si fit es 1 lo ajustamos a la pantalla
	if (fit)
		go_fit(meta, proyect);
	//si el modo líneas está activado dibujamos las aristas
	if (meta->map.b_lines)
		wired(meta, proyect);
	//si el modo puntos esta activado dibujamos los vértices
	if (meta->map.b_dots)
		doted(meta, proyect);
}


int	draw_map(t_meta *meta, int fit)
{
	t_point	*proyect;
	//la variable tipo clock_t se usa para almacenar el tiempo usado por el
	//procesador
	clock_t	t;

	//la funcion clock() retorna el tiempo empleado por el procesador desde 
	//que empieza el programa hasta que acaba
	t = clock();
	//reservamos memoria para cada punto del mapa
	proyect = malloc (meta->map.len * sizeof(t_point));
	//si hay un error al reservar memoria salimos con un error
	if (proyect == NULL)
		terminate(ERR_MEM);
	//aumentamos el numero de renders en 1 cada vez que se llame a esta función
	meta->map.renders = meta->map.renders + 1;
	//generamos el fondo primero para no pisar nada que dibujemos después
	generate_background(meta, meta->map.colors.backcolor, \
			meta->map.colors.menucolor);
	//copiamos los puntos de meta->map.points en proyect
	copy_map(meta->map.points, proyect, meta->map.len);
	//parseamos y normalizamos el mapa haciendole la proyección y escala que requiera
	parse_map(meta, proyect);
	//dibujamos según los modos que tengamos activos
	drawing(meta, proyect, fit);
	//ponemos la imagen en la ventana
	mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, \
			meta->bitmap.img, 0, 0);
	//dibujamos el menú
	draw_menu(meta);
	//liberamos memoria
	free(proyect);
	//calculamos el tiempo transcurrido
	t = clock() - t;
	meta->map.performance = ((double)t) / CLOCKS_PER_SEC;
	return (1);
}
