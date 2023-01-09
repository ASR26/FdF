/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 08:46:42 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/28 11:51:19 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/draw_utils.h"
#include "../inc/utils.h"
#include <math.h>

/*
 * Esta función sera auxiliar para dibujar un círculo
 */
static void	dot_util(t_meta *meta, t_point pixel, t_point point, int coord)
{
	int	i;

	i = point.axis[X];
	while (i <= point.axis[X] + coord)
	{
		pixel.axis[X] = i;
		pixel.axis[Y] = (int)point.axis[Y] + coord;
		my_putpixel(meta, pixel);
		pixel.axis[X] = i;
		pixel.axis[Y] = (int)point.axis[Y] - coord;
		my_putpixel(meta, pixel);
		i++;
	}
}

/*
 * Esta función dibuja un círculo en la posición point con el radio radius
 */
void	draw_dot(t_meta *meta, t_point point, int radius)
{
	int		axis[2];
	int		change[2];
	int		radius_error;
	t_point	pixel;

	axis[X] = radius;
	axis[Y] = 0;
	change[X] = 1 - (radius << 1);
	change[Y] = 0;
	radius_error = 0;
	pixel.color = point.color;
	while (axis[X] >= axis[Y])
	{
		dot_util(meta, pixel, point, axis[Y]);
		dot_util(meta, pixel, point, axis[X]);
		axis[Y]++;
		radius_error += change[Y];
		change[Y] += 2;
		if (((radius_error << 1) + change[X]) > 0)
		{
			axis[X]--;
			radius_error += change[X];
			change[X] += 2;
		}
	}
}

/*
 * Esta función hará el gradiente para variar el color según la altura
 * */
int gradient(int startcolor, int endcolor, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;
	
	//haremos modificaciones de bits para encontrar el incremento de color,
	//restando el color inicial al color final y dividiendo por la longitud
	//para cada uno de los 3 bytes de rgb
	increment[0] = (double)((endcolor >> 16) - \
			(startcolor >> 16)) / (double)len;
	increment[1] = (double)(((endcolor >> 8) & 0xFF) - \
			((startcolor >> 8) & 0xFF)) / (double)len;
	increment[2] = (double)((endcolor & 0xFF) - \
			(startcolor & 0xFF)) / (double)len;
	//a cada byte de rgb le sumamos el valor redondeado del incremento 
	//multiplicado por el valor de z (pix)
	new[0] = (startcolor >> 16) + ft_round(pix * increment[0]);
	new[1] = ((startcolor >> 8) & 0xFF) + ft_round(pix * increment[1]);
	new[2] = (startcolor & 0xFF) + ft_round(pix * increment[2]);
	//asignamos el nuevo color a sus bytes correspondientes y lo devolvemos
	newcolor = (new[0] << 16) + (new[1] << 8) + new[2];
	return (newcolor);
}

void	shadow(t_point *points, int len)
{
	int	i;
	
	i = 0;
	while (i < len)
	{
		if (points[i].axis[Z] < 0)
			points[i].paint = 0;
		else
			points[i].paint = 1;
		i++;
	}
}

/*
 * Esta función comprueba si los puntos están en la ventana para evitar
 * cáculos innecesarios y luego calcula todos los puntos de la línea mediante el
 * algoritmo de Bresenham
 */
int	draw_line(t_meta *meta, t_point start, t_point end)
{
	//delta serán los incrementos entre puntos
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;

	//si los puntos no son válidos no hacemos nada
	if (valid_pixel(start) == 0 && valid_pixel(end) == 0)
		return (0);
	delta.axis[X] = end.axis[X] - start.axis[X];
	delta.axis[Y] = end.axis[Y] - start.axis[Y];
	//haremos la raíz cuadrada de la suma de los incrementos al cuadrado
	pixels = sqrt((delta.axis[X] * delta.axis[X]) + \
			(delta.axis[Y] * delta.axis[Y]));
	len = pixels;
	//dividimos los incrementos entre la raíz que hemos calculado
	delta.axis[X] /= pixels;
	delta.axis[Y] /= pixels;
	//asignamos a los ejes del pixel los puntos de origen
	pixel.axis[X] = start.axis[X];
	pixel.axis[Y] = start.axis[Y];
	while (pixels > 0)
	{
		//asignamos el valor según el gradiente
		pixel.color = gradient(start.color, end.color, len, len - pixels);
		//pintamos el pixel
		my_putpixel(meta, pixel);
		//incrementamos los píxeles
		pixel.axis[X] += delta.axis[X];
		pixel.axis[Y] += delta.axis[Y];
		//reducimos en 1 los píxeles restantes por dibujar
		pixels = pixels - 1;
	}
	return (1);
}
