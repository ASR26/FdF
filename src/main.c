/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:04:03 by asolano-          #+#    #+#             */
/*   Updated: 2022/10/03 08:30:35 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/control_keys.h"
#include "../inc/control_mouse.h"
#include "../inc/control_utils.h"
#include "../inc/errors.h"
#include <stdlib.h>

/*
 * Esta función inicializa algunas variabels que necesitaremos para el funcionamiento de mlx
 */
void	system_init(t_meta *meta)
{
	//ajustamos el número de renders a 0, ya que no se ha renderizado ninguna imagen
	meta->map.renders = 0;
	//asignamos la proporción dividiendo el límite del eje z entre el límite
	//del eje x
	meta->map.proportion = meta->map.limits.axis[Z] / meta->map.limits.axis[X];
	//si la proporción es mayor a 0.5 (el mapa es muy alto en relación al ancho)
	//le aumentamos el divisor de z por 30 para hacerlo mas plano
	if (meta->map.proportion > 0.5)
		meta->map.zdivisor = meta->map.proportion * 30;
	//ajustamos los botones a "false" porque no estamos pulsando ninguno
	meta->keys.b_keyctrl = 0;
	meta->keys.b_mouse_l = 0;
	meta->keys.b_mouse_r = 0;
	//iniciamos la mlx y la guardamos en vars.mlx
	meta->vars.mlx = mlx_init();
	//iniciamos la ventana y la guardamos en vars.win
	meta->vars.win = mlx_new_window(meta->vars.mlx, WINX, WINY, \
		"FDF - asolano-");
	//iniciamos una imagen y la guardamos en bitmap.img
	meta->bitmap.img = mlx_new_image(meta->vars.mlx, WINX, WINY);
	//iniciamos el buffer donde guardaremos la imagen, los bits por pixel la longitud
	//de lineas y el endian
	meta->bitmap.buffer = mlx_get_data_addr(meta->bitmap.img, \
		&meta->bitmap.bitxpixel, &meta->bitmap.lines, &meta->bitmap.endian);
}

int	main(int argc, char **argv)
{
	t_meta	meta;
	//comprobamos si hay un número válido de argumentos
	if (argc != 2)
		terminate(ERR_ARGS);
	//cargamos el mapa en la variable map dentro de meta y le damos
	//el valor del argumento dado, es decir el archivo del mapa
	load_map(&meta.map, argv[1]);
	//inicializamos las principales variables que necesitaremos
	system_init(&meta);
	//si no podemos dibujar el mapa terminamos el programa con error
	if (draw_map(&meta, FIT) < 0)
		terminate(ERR_MAP);
	//todos los hooks para registrar eventos de teclado/ratón
	mlx_hook(meta.vars.win, 2, 0, key_press, &meta);
	mlx_hook(meta.vars.win, 3, 0, key_release, &meta);
	mlx_hook(meta.vars.win, 4, 0, mouse_press, &meta);
	mlx_hook(meta.vars.win, 5, 0, mouse_release, &meta);
	mlx_hook(meta.vars.win, 6, 0, mouse_move, &meta);
	mlx_hook(meta.vars.win, 17, 0, terminate_program, &meta);
	//el loop para mantener la ventana abierta
	mlx_loop(meta.vars.mlx);
	//cuando el loop acaba liberamos los puntos del mapa para evitar leaks
	free(meta.map.points);
	return (0);
}
