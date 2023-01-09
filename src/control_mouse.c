/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:47:42 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/28 11:26:39 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/keycodes.h"
#include "../inc/control_utils.h"

/*
 * Esta función maneja cada vez que el ratón se mueve
 */

int	mouse_move(int x, int y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	//si el ratón se mueve fuera de los límites de la ventana
	//se acaba la función
	if (x >  WINX || x < 0 || y > WINY || y < 0)
		return (0);
	//si pulsamos y el ratón se mueve ajustamos los ángulos y 
	//volvemos a dibujar el mapa
	if (meta->keys.b_mouse_l)
	{
		angle(&meta->map.ang[X], (int)meta->keys.last_click_l.axis[Y] - y);
		angle(&meta->map.ang[Y], (int)-meta->keys.last_click_l.axis[X] + x);
		meta->keys.last_click_l.axis[X] = x;
		meta->keys.last_click_l.axis[Y] = y;
		draw_map(meta, FREE);
	}
	//si hacemos click derecho cambiaremos el eje para mover
	//la figura por la pantalla
	if (meta->keys.b_mouse_r)
	{
		meta->map.source.axis[X] -= ((int)meta->keys.last_click_r.axis[X] - x);
		meta->map.source.axis[Y] -= ((int)meta->keys.last_click_r.axis[Y] - y);
		meta->map.source.axis[Z] = 0;
		meta->keys.last_click_r.axis[X] = x;
		meta->keys.last_click_r.axis[Y] = y;
		draw_map(meta, FREE);
	}
	return (0);
}

/*
 * Esta función maneja cuando soltamos algún botón del ratón
 */
int	mouse_release(int button, int x, int y, void *param)
{
	t_meta	*meta;

	x++;
	y++;
	meta = (t_meta *)param;
	if (button == 1)
		meta->keys.b_mouse_l = 0;
	if (button == 2)
		meta->keys.b_mouse_r = 0;
	return (0);
}

/*
 * Esta función maneka cuando un botón del ratón es pulsado
 */
int	mouse_press(int button, int x, int y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	//si pulsamos el botón izquierdo guardamos la posición que
	//hemos pulsado y activamos el falso booleano de left click
	if (button == 1)
	{
		meta->keys.b_mouse_l = 1;
		meta->keys.last_click_l.axis[X] = x;
		meta->keys.last_click_l.axis[Y] = y;
	}	
	//si pulsamos el botón derecho guardamos la posición que
	//hemos pulsado y activamos el falso booleano de right click
	if (button == 2)
	{
		meta->keys.b_mouse_r = 1;
		meta->keys.last_click_r.axis[X] = x;
		meta->keys.last_click_r.axis[Y] = y;
	}
	//si hacemos scroll abajo bajamos la escala si es mayor que 2 
	if (button == 4)
	{
		if (meta->map.scale > 2)
			meta->map.scale = meta->map.scale / 1.5;
	}
	//si hacemos scroll arriba aumentamos la escala
	if (button == 5)
		meta->map.scale = meta->map.scale * 1.5;
	//dibujamos el mapa
	draw_map(meta, FREE);
	return (0);
}
