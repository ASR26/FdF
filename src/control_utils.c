/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:08:08 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/28 10:53:24 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx_macos/mlx.h"
#include "../lib/libft/libft.h"
#include "../inc/defines.h"
#include "../inc/keycodes.h"
#include "../inc/map.h"
#include "../inc/map_utils.h"
#include <errno.h>
#include <stdio.h>

/*
 * Esta función ajusta el ángulo para que esté en los límites 0-359
 */
void	angle(float *ang, float value)
{
	*ang += value;
	if (*ang < 0)
		*ang = 360 + *ang;
	if (*ang >= 360)
		*ang = *ang - 360;
}

/*
 * Esta función añade grados a la estructura de control dependiendo de
 * la tecla pulsada
 */
void	angle_control(int key, t_meta *meta)
{
	int	ang;

	ang = 10;
	if (meta->keys.b_keyctrl)
		ang = 90;
	if (key == KEY_DOWN)
		angle (&meta->map.ang[X], ang);
	if (key == KEY_UP)
		angle (&meta->map.ang[X], -ang);
	if (key == KEY_LEFT)
		angle (&meta->map.ang[Y], ang);
	if (key == KEY_RIGHT)
		angle (&meta->map.ang[Y], -ang);
	if (key == KEY_Q)
		angle (&meta->map.ang[Z], ang);
	if (key == KEY_W)
		angle (&meta->map.ang[Z], -ang);
}

/*
 * Esta función cierra el programa
 */

int	terminate_program(void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	mlx_destroy_window(meta->vars.mlx, meta->vars.win);
	free(meta->map.points);
	exit(0);
}

/* Esta función cierra el programa si ocurre algun error*/
void	terminate(char *str)
{
	//si el return recibido es 0 escribimos nosotros el mensaje
	if (errno == 0)
		ft_putendl_fd(str, 2);
	//si el return es un código de error lo escribimos con la funcion perror
	else
		perror(str);
	exit(1);
}

/*
 * Esta función maneja las paletas de colores según el botón que se pulse
 */
void	control_colorscheme(int key, t_map *map)
{
	map->colors.backcolor = CARBON;
	map->colors.bottomcolor = AZUL;
	map->colors.topcolor = BRICK_RED;
	map->colors.groundcolor = SAFFRON;
	if (key == KEY_2)
	{
		map->colors.backcolor = WHITE;
		map->colors.bottomcolor = CARBON;
		map->colors.topcolor = CARBON;
		map->colors.groundcolor = CARBON;
	}
	if (key == KEY_3)
	{
		map->colors.bottomcolor = WHITE;
		map->colors.topcolor = WHITE;
		map->colors.groundcolor = WHITE;
	}
	if (key == KEY_4)
	{
		map->colors.bottomcolor = SUPERAZUL;
		map->colors.topcolor = ROJO;
		map->colors.groundcolor = VERDE;
	}
	colorize(map);
}
