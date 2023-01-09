/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:51:49 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/28 11:11:58 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/utils.h"
#include "../inc/draw_utils.h"
#include <math.h>
#include <stdlib.h>


/*
 * Esta función asgina el color, dependiendo del endian del sistema
 */
void	set_color(char *buffer, int endian, int color, int alpha)
{
	if (endian == 1)
	{
		buffer[0] = alpha;
		buffer[1] = (color >> 16) & 0xFF;
		buffer[2] = (color >> 8) & 0xFF;
		buffer[3] = (color) & 0xFF;
	}
	else
	{
		buffer[3] = alpha;
		buffer[2] = (color >> 16) & 0xFF;
		buffer[1] = (color >> 8) & 0xFF;
		buffer[0] = (color) & 0xFF;
	}
}

/*
 * Esta función calcula la posición del pixel en el array de la imagen:
 * 		array_pixel_position = pixel.axis[X] * WINX * 4 + 4 * pixel.axis[Y]
 * y llena los 4 bytes de color llamando a set_color
 */
int	my_putpixel(t_meta *meta, t_point pixel)
{
	int	mypixel;
	int	alpha;

	alpha = 0;
	//si el pixel está en el menú le bajamos 10 al alpha
	if (pixel.axis[X] < MENU_WIDTH)
		alpha = -10;
	//si el pixel está fuera de los límites de la pantalla devolvemos un error
	if (pixel.axis[X] >= WINX || pixel.axis[Y] >= WINY || \
			pixel.axis[X] < 0 || pixel.axis[Y] < 0)
		return (-1);
	//asignamos a mypixel el pixel que estamos tratando
	mypixel = ((int)pixel.axis[Y] * WINX * 4) + ((int)pixel.axis[X] * 4);
	//si los bit por pixel no son 32 lo ajustamos a 32
	if (meta->bitmap.bitxpixel != 32)
		pixel.color = mlx_get_color_value(meta->vars.mlx, pixel.color);
	//asignamos el color del pixel
	set_color(&meta->bitmap.buffer[mypixel], \
			meta->bitmap.endian, pixel.color, alpha);
	return (0);
}

/*
 * Esta función ajusta el color a 32 bits en caso de que haga falta
 */
int	get_color(t_meta *meta, int color)
{
	if (meta->bitmap.bitxpixel != 32)
		color = mlx_get_color_value(meta->vars.mlx, color);
	return (color);
}


void	generate_background(t_meta *meta, int backcolor, int menucolor)
{
	int	axis[2];
	int	pixel;
	int	color;

	//asignamos el valor del color de fondo
	backcolor = get_color(meta, backcolor);
	//asignamos el valor del color de menú
	menucolor = get_color(meta, menucolor);
	axis[X] = 0;
	axis[Y] = 0;
	while (axis[Y] < WINY)
	{
		while (axis[X] < WINX)
		{
			//asginamos el color según estemos en el menú o en el fondo
			if (axis[X] < MENU_WIDTH)
				color = menucolor;
			else 
				color = backcolor;
			//asignamos el pixel multiplicando el eje Y por la línea en la que estemos
			//y sumandole el eje X multiplicado por 4 (ya que cada pixel ocupa 4 bytes)
			pixel = (axis[Y] * meta->bitmap.lines) + (axis[X] * 4);
			//asignamos el color al pixel en el buffer
			set_color(&meta->bitmap.buffer[pixel], \
					meta->bitmap.endian, color, 1);
			//avanzamos por el eje X
			axis[X]++;
		}
		//avanzamos por el eje Y y reiniciamos el X
		axis[Y]++;
		axis[X] = 0;
	}
}

/*
 * Esta función genera unas estrellas (decoración)
 */

void	generate_stars(t_meta *meta)
{
	int		i;
	t_point	star;
	int		lim_x[2];
	int		lim_y[2];

	//si el modo geo no está activo salimos de la función
	if (meta->map.b_geo == 0)
		return ;
	//al límite de x[0] le damos el eje x - el radio multiplicado por la escala
	lim_x[0] = meta->map.source.axis[X] - (meta->map.radius * meta->map.scale);
	//al límite de x[0] le damos el eje x + el radio multiplicado por la escala
	lim_x[1] = meta->map.source.axis[X] - (meta->map.radius * meta->map.scale);
	//al límite de x[0] le damos el eje Y - el radio multiplicado por la escala
	lim_y[0] = meta->map.source.axis[Y] - (meta->map.radius * meta->map.scale);
	//al límite de x[0] le damos el eje x + el radio multiplicado por la escala
	lim_y[1] = meta->map.source.axis[Y] - (meta->map.radius * meta->map.scale);
	i = 0;
	//crearemos 200 estrellas
	while (i < 200)
	{
		//asginamos al eje X e Y un número aleatorio dentro de la ventana
		star.axis[X] = rand() % WINX;
		star.axis[Y] = rand() % WINY;
		star.color = WHITE;
		if ((star.axis[X] < lim_x[0] || star.axis[X] > lim_x[1]) \
		|| ((star.axis[Y] < lim_y[0] || star.axis[Y] > lim_y[1])))
		draw_dot(meta, star, 2);
		i++;
	}
}
