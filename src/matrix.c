/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:22:19 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/23 10:37:10 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/utils.h"
#include <math.h>

/*
 * Multiplicamos una coordenada de 3 puntos por una matriz de [3][3] y devolvemos
 * el resultado, que será una coordenada de 3 puntos
 */
t_point	mul_mat(float matrix[3][3], t_point point)
{
	int		i;
	int		j;
	t_point	result;

	result = point;
	i = 0;
	while (i < 3)
	{
		result.axis[i] = 0;
		result.color = point.color;
		j = 0;
		while (j < 3)
		{
			result.axis[i] += matrix[i][j] * point.axis[j];
			j++;
		}
		i++;
	}
	return (result);
}
/*
 * Calculamos 'len' puntos del array con la rotacion en el eje X y lo guardamos
 * en el array 'proyection'
 */
void	rotate_x(t_point *points, t_point *proyection, float ang, int len)
{
	int		i;
	float	rad;
	float	proyect_matrix[3][3];

	//conseguimos los radianes del ángulo recibido
	rad = ang * M_PI / 180;
	//inicializamos la matriz
	matrix_init(proyect_matrix);
	//preparamos la matriz de rotación para hacer la rotación de cada punto
	//(matriz de rotación en wikipedia) + apuntes de Bernardo
	proyect_matrix[0][0] = 1;
	proyect_matrix[1][1] = cos(rad);
	proyect_matrix[1][2] = -sin(rad);
	proyect_matrix[2][1] = sin(rad);
	proyect_matrix[2][2] = cos(rad);
	i = 0;
	//para cada punto asignamos a proyeccion el resultado de la multiplicación
	//de la matriz
	while (i < len)
	{
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}

/*
 * Calculamos 'len' puntos del array con la rotacion en el eje Y y lo guardamos
 * en el array 'proyection'
 */
void	rotate_y(t_point *points, t_point *proyection, float ang, int len)
{
	int		i;
	float	rad;
	float	proyect_matrix[3][3];

	//conseguimos los radianes del ángulo recibido
	rad = ang * M_PI / 180;
	//inicializamos la matriz
	matrix_init(proyect_matrix);
	//preparamos la matriz de rotación para hacer la rotación de cada punto
	//(matriz de rotación en wikipedia) + apuntes de Bernardo
	proyect_matrix[0][0] = cos(rad);
	proyect_matrix[1][1] = 1;
	proyect_matrix[0][2] = sin(rad);
	proyect_matrix[2][0] = -sin(rad);
	proyect_matrix[2][2] = cos(rad);
	i = 0;
	//para cada punto asignamos a proyeccion el resultado de la multiplicación
	//de la matriz
	while (i < len)
	{
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}
/*
 * Calculamos 'len' puntos del array con la rotacion en el eje Z y lo guardamos
 * en el array 'proyection'
 */
void	rotate_z(t_point *points, t_point *proyection, float ang, int len)
{
	int		i;
	float	rad;
	float	proyect_matrix[3][3];

	//conseguimos los radianes del ángulo recibido
	rad = ang * M_PI / 180;
	//inicializamos la matriz
	matrix_init(proyect_matrix);
	//preparamos la matriz de rotación para hacer la rotación de cada punto
	//(matriz de rotación en wikipedia) + apuntes de Bernardo
	proyect_matrix[0][0] = cos(rad);
	proyect_matrix[0][1] = -sin(rad);
	proyect_matrix[1][0] = sin(rad);
	proyect_matrix[1][1] = cos(rad);
	proyect_matrix[2][2] = 1;
	i = 0;
	//para cada punto asignamos a proyeccion el resultado de la multiplicación
	//de la matriz
	while (i < len)
	{
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}

/*
 * Esta función calcula 'len' puntos del array para una proyección ortonormal
 * y los almacena en el array 'proyection'
 */
void	orto_proyection(t_point *points, t_point *proyection, int len)
{
	int		i;
	float	proyect_matrix[3][3];

	//inicializamos la matriz
	matrix_init(proyect_matrix);
	proyect_matrix[0][0] = 1;
	proyect_matrix[1][1] = 1;
	i = 0;
	while (i < len)
	{
		//multiplicamos cada punto por la matriz que hemos hecho
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}
