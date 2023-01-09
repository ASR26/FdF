/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:22:45 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/29 11:12:51 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/keycodes.h"
#include "../inc/geometry.h"
#include "../inc/control_utils.h"
#include "../inc/map_utils.h"

void	control_keys3(int key, t_meta *meta)
{
	// si pulsamos B o CTRL + B doblaremos más o menos el mapa (bend)
	if (key == KEY_B)
	{
		if (meta->keys.b_keyctrl)
			meta->map.brange -= 0.001;
		else
			meta->map.brange += 0.001;
	}
	//si pulsamos + haremos zoom in
	if (key == KEY_SUM || key == KEY_SUM2)
	{
		if (meta->keys.b_keyctrl)
			meta->map.scale = meta->map.scale * 1.5;
		if (meta->map.zdivisor > 1)
			meta->map.zdivisor -= 1;
	}
	//si pulsamos - haremos zoom out
	if (key == KEY_RES || key == KEY_RES2)
	{
		if (meta->keys.b_keyctrl)
			meta->map.scale = meta->map.scale / 1.5;
		meta->map.zdivisor += 1;
	}
	// si pulsamos la I pondremos la vista isométrica
	if (key == KEY_I)
	{
		isometric(&meta->map);
		draw_map(meta, FIT);
	}			
}

void	control_keys2(int key, t_meta *meta)
{
	//si pulsamos D activamos y desactivamos el modo puntos
	if (key == KEY_D)
		meta->map.b_dots = !meta->map.b_dots;
	//si pulsamos L activamos y desactivamos el modo lineas
	if (key == KEY_L)
		meta->map.b_lines = !meta->map.b_lines;
	//si pulsamos X activamos y desactivamos el modo de líneas extra
	if (key == KEY_X)
		meta->map.b_pluslines = !meta->map.b_pluslines;
	//si pulsamos G activamos y desactivamos el modo geo (hacer una esfera del mapa)
	if (key == KEY_G)
		meta->map.b_geo = !meta->map.b_geo;
	//si pulsamos S activamos y desactivamos el modo estrellas
	if (key == KEY_S)
		meta->map.b_stars = !meta->map.b_stars;
	//si pulsamos H activamos y desactivamos el modo sombras
	if (key == KEY_H)
		meta->map.b_shadow = !meta->map.b_shadow;
	//si pulsamos F ajustamos el mapa a la ventana
	if (key == KEY_F)
		draw_map(meta, FIT);
	//si pulsamos CMD será como pulsar ctrl
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 1;
}


/*
 * Esta función maneja algunos eventos de teclas
 */
void	control_keys1(int key, t_meta *meta)
{
	//si pulsamos escape se cierra el programa
	if (key == KEY_ESC)
		terminate_program(meta);
	//si pulsamos la R reiniciamos el mapa
	if (key == KEY_R)
	{
		map_ini(&meta->map, 0);
		meta->map.proportion = \
		meta->map.limits.axis[Z] / meta->map.limits.axis[X];
		if (meta->map.proportion > 0.5)
			meta->map.zdivisor = meta->map.proportion * 30;
		colorize(&meta->map);
		draw_map(meta, FIT);
	}
	//si pulsamos C centramos el mapa
	if (key == KEY_C)
	{
		meta->map.source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
		meta->map.source.axis[Y] = WINY / 2;
	}
	//si pulsamos P hacemos la vista paralela
	if (key == KEY_P)
	{
		parallel(&meta->map);
		draw_map(meta, FIT);
	}
}


/*
 * Esta función maneja cuando se pulsa una tecla
 */
int	key_press(int key, void *param)
{
	t_meta *meta;

	meta = (t_meta *)param;
	angle_control(key, meta);
	control_keys1(key,meta);
	control_keys2(key,meta);
	control_keys3(key,meta);
	if (key >= KEY_1 && key <= KEY_4)
		control_colorscheme(key, &meta->map);
	draw_map(meta, FREE);
	return (0);
}

/*
 * Esta función maneja cuando se suelta una tecla
 */
int	key_release(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 0;
	return (0);
}
