/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:04:03 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/10 08:46:24 by asolano-         ###   ########.fr       */
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

void	system_init(t_meta *meta)
{
	meta->map.renders = 0;
	meta->map.proportion = meta->map.limits.axis[Z] / meta->map.limits.axis[X];
	if (meta->map.proportion > 0.5)
		meta->map.zdivisor = meta->map.proportion * 30;
	meta->keys.b_keyctrl = 0;
	meta->keys.b_mouse_l = 0;
	meta->keys.b_mouse_r = 0;
	meta->vars.mlx = mlx_init();
	meta->vars.win = mlx_new_window(meta->vars.mlx, WINX, WINY, \
		"FDF - asolano-");
	meta->bitmap.img = mlx_new_image(meta->vars.mlx, WINX, WINY);
		meta->bitmap.buffer = mlx_get_data_addr(meta->bitmap.img, \
		&meta->bitmap.bitxpixel, &meta->bitmap.lines, &meta->bitmap.endian);
}

int	main(int argc, char **argv)
{
	t_meta	meta;

	if (argc != 2)
		terminate(ERR_ARGS);
	load_map(&meta.map, argv[1]);
	system_init(&meta);
	if (draw_map(&meta, FIT) < 0)
		terminate(ERR_MAP);
	mlx_hook(meta.vars.win, 2, 0, key_press, &meta);
	mlx_hook(meta.vars.win, 3, 0, key_release, &meta);
	mlx_hook(meta.vars.win, 4, 0, mouse_press, &meta);
	mlx_hook(meta.vars.win, 5, 0, mouse_release, &meta);
	mlx_hook(meta.vars.win, 6, 0, mouse_move, &meta);
	mlx_hook(meta.vars.win, 17, 0, terminate_program, &meta);
	mlx_loop(meta.vars.mlx);
	free(meta.map.points);
	return (0);
}
