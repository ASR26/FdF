/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:22:45 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/10 08:51:20 by asolano-         ###   ########.fr       */
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
	if (key == KEY_B)
	{
		if (meta->keys.b_keyctrl)
			meta->map.brange -= 0.001;
		else
			meta->map.brange += 0.001;
	}
	if (key == KEY_SUM || key == KEY_SUM2)
	{
		if (meta->keys.b_keyctrl)
			meta->map.scale = meta->map.scale * 1.5;
		if (meta->map.zdivisor > 1)
			meta->map.zdivisor -= 1;
	}
	if (key == KEY_RES || key == KEY_RES2)
	{
		if (meta->keys.b_keyctrl)
			meta->map.scale = meta->map.scale / 1.5;
		meta->map.zdivisor += 1;
	}
	if (key == KEY_I)
	{
		isometric(&meta->map);
		draw_map(meta, FIT);
	}			
}

void	control_keys2(int key, t_meta *meta)
{
	if (key == KEY_D)
		meta->map.b_dots = !meta->map.b_dots;
	if (key == KEY_L)
		meta->map.b_lines = !meta->map.b_lines;
	if (key == KEY_X)
		meta->map.b_pluslines = !meta->map.b_pluslines;
	if (key == KEY_F)
		draw_map(meta, FIT);
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 1;
}

void	control_keys1(int key, t_meta *meta)
{
	if (key == KEY_ESC)
		terminate_program(meta);
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
	if (key == KEY_C)
	{
		meta->map.source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
		meta->map.source.axis[Y] = WINY / 2;
	}
	if (key == KEY_P)
	{
		parallel(&meta->map);
		draw_map(meta, FIT);
	}
}

int	key_press(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	angle_control(key, meta);
	control_keys1(key, meta);
	control_keys2(key, meta);
	control_keys3(key, meta);
	if (key >= KEY_1 && key <= KEY_4)
		control_colorscheme(key, &meta->map);
	draw_map(meta, FREE);
	return (0);
}

int	key_release(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 0;
	return (0);
}
