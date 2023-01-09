/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:14:56 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/23 10:42:39 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include "../lib/libft/libft.h"
#include "../inc/defines.h"
#include "../inc/utils.h"
#include "../inc/draw_utils.h"
#include "../inc/map_utils.h"
#include "../inc/errors.h"
#include "../inc/geometry.h"
#include <math.h>
#include <fcntl.h>

/*
 * Esta función ajusta el color en función del valor de z del punto
 */
void	load_color(int max, int min, t_point *point, t_colors colors)
{
	//asignamos paint a 1 para que el punto se pinte 
	point->paint = 1;
	//le asignamos el color base
	point->color = DEFAULT_COLOR;
	//si el punto es el más alto se le da el color del punto más alto
	if (point->axis[Z] == max)
		point->color = colors.topcolor;
	//si el punto está a altura 0 le damos color de suelo
	else if (point->axis[Z] == 0)
		point->color = colors.groundcolor;
	//si la altura es el mínimo y el mínimo no es 0 le damos el color de abajo
	else if (point->axis[Z] == min && min != 0)
		point->color = colors.bottomcolor;
	//si la altura es mayor que 0 usaremos la función gradiente para calcular
	//que tono debería tener segun la distancia entre el punto más alto y el suelo
	else if (point->axis[Z] > 0)
		point->color = gradient(colors.groundcolor, colors.topcolor, \
		max, point->axis[Z]);
	else
	//si el punto está entre el suelo y el mínimo haremos lo mismo, un gradiente
	//entre el suelo y el mínimo, para calcular el tono según la altura
		point->color = gradient(colors.bottomcolor, colors.groundcolor, \
		-min, - (min - point->axis[Z]));
}

/*
 * Esta función carga los colores hexadecimales
 */
void	load_hexcolors(t_map *map, char *line)
{
	char	**color;

	// si hay ',' en la línea...
	if (ft_strchr(line, ',') != 0)
	{
		//hacemos split a la línea
		color = ft_split(line, ',');
		//al color del punto le asignamos un long que conseguimos con la funcion strtol
		//strtol convierte un string a long, el primer argumento es el string (le sumamos
		//2 porque el formato es 0xFFFFFF, el segundo argumento es un puntero al char* es decir
		//*(char *) al que le daremos el valor numérico obtenido, como ya lo estamos igualando
		//manualmente lo asignamos como NULL, el último argumento es un int que asginará la base
		//que utilizaremos que puede ir de 2 a 36 o ser el valor especial 0, en este caso, al ser
		//un valor hexadecimal usaremos 16
		map->points[map->len].color = strtol(color[1] + 2, NULL, 16);
		//liberamos el split
		dbl_free(color);
	}
}


/*
 * Esta función asigna cada punto del archivo del mapa a la variable map->points
 * usando map->len como indice del array
 */
static void load_points(char *line, t_map *map, int numline)
{
	char	**splitted;
	int		i;

	//separamos los puntos de la línea
	splitted = ft_split(line, ' ');
	i = 0;
	//mientras haya un punto...
	while (splitted[i] && splitted[i][0] != '\n')
	{
		//si hay un punto no válido salimos con error
		if (!valid_point(&splitted[i][0]))
			terminate(ERR_EMPTY);
		//guardamos el eje z del punto
		map->points[map->len].axis[Z] = ft_atoi(&splitted[i][0]);
		//guardamos el eje x del punto
		map->points[map->len].axis[X] = i - map->limits.axis[X] / 2;
		//guardamos el eje y del punto
		map->points[map->len].axis[Y] = numline - map->limits.axis[Y] / 2;
		//cargamos el color según la altura
		load_color((int)map->limits.axis[Z], map->zmin, \
		&map->points[map->len], map->colors);
		load_hexcolors(map, splitted[i]);
		i++;
		map->len++;
	}
	dbl_free(splitted);
}

/*
 * Determinamos los valores máximos de x, y, z en el mapa y devolvemos -1 si
 * el mapa tiene diferente tamaño de líneas
 */
static void	map_size(char *path, t_map *map)
{
	char	*line;
	char	**splitted;
	int		linelen;
	int		fd;

	//abrimos el archivo dado como argumento en modo lectura
	fd = open(path, O_RDONLY);
	//si el archivo no se puede abrir devolverá un error y fd valdrá -1
	if (fd < 2)
		terminate(ERR_OPEN);
	//asignamos a line la siguiente línea
	line = get_next_line(fd);
	//mientras haya otra línea...
	while (line != NULL)
	{
		//separamos la línea por espacios para tener los números
		splitted = ft_split(line, ' ');
		//calculamos los límites de la línea
		z_limits(splitted, map);
		//calculamos la longitud de la línea
		linelen = line_elems(splitted);
		//si el limite en x es 0 le damos la longitud del array
		if (map->limits.axis[X] == 0)
			map->limits.axis[X] = linelen;
		//si el límite en x es diferente de la longitud significa que ha
		//habido algun error y nos salimos
		if (map->limits.axis[X] != linelen)
			terminate(ERR_LINE);
		//sumamos a la longitud del mapa el límite en x
		map->len += map->limits.axis[X];
		//aumentamos en 1 el tamaño en Y
		map->limits.axis[Y]++;
		//liberamos el doble puntero
		dbl_free(splitted);
		//liberamos la línea
		free(line);
		//cogemos la siguiente línea para seguir trabajando
		line = get_next_line(fd);
	}
	//cerramos el file descriptor
	close (fd);
}
/*
 * Inicializamos la estructura
 * Conseguimos el tamaño del mapa
 * Comprobamos que el mapa sea válido
 * Leemos el mapa
 * Cargamos cada punto en la estructura
 */
void	load_map(t_map *map, char *path)
{
	int		fd;
	char	*line;
	int		numline;

	//inicializamos el mapa
	map_ini(map, 1);
	//asignamos el tamaño del mapa
	map_size(path, map);
	//guardamos memoria para los puntos del mapa
	map->points = ft_calloc (map->len, sizeof(t_point));
	//si la memoria para los puntos no se ha hecho cerramos con error
	if (map->points == NULL)
		terminate(ERR_MEM);
	//abrimos el archivo del mapa
	fd = open(path, O_RDONLY);
	//si la apertura da error terminamos cerramos el programa con error
	if (fd < 2)
		terminate(ERR_OPEN);
	numline = 0;
	map->len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		numline++;
		//metemos los puntos en su variable
		load_points(line, map, numline);
		free(line);
		line = get_next_line(fd);
	}
	//convertimos a coordenadas polares
	go_polar(map);
}
