/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:43:09 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/09 11:15:38 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/utils.h"

#define CONTROL_BOX			620
#define DRAWINFO_BOX		30
#define MAPINFO_BOX			250
#define COLORSCHEME_BOX		450
#define LINE_SIZE			30
#define MENU_TAB			20

static void	draw_colorscheme(t_meta *meta)
{
	int	line;
	
	line = COLORSCHEME_BOX;
	print_str(meta, MENU_TAB, line, "/// COLORSCHEME ///");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "1: TERRAIN");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "2: BLACK & WHITE");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "3: WHITE & BLACK");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "4: EARTH");
	line += LINE_SIZE;
}

static void	draw_mapinfo(t_meta *meta)
{
		int		line;

	line = MAPINFO_BOX;
	print_str(meta, MENU_TAB, line, "/// MAP INFO ///");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Size:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.len);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Xmax:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.limits.axis[X]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Ymax:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.limits.axis[Y]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Zmax:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.limits.axis[Z]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Zmin:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.zmin);
	line += LINE_SIZE;
}

static void	draw_controls(t_meta *meta)
{
	int	line;

	line = CONTROL_BOX;
	print_str(meta, MENU_TAB, line, "/// CONTROLS ///");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Scroll: Zoom In/Out");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Left Click/Arrows: Rotate");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Right Click: Move");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Q/W: Rotate Z axis");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "+/-: Z Divisor");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "B/Ctrl + B: Blending");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "P/I/F/C Paral/Iso/Fit/Center");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "D/L/X: Dots/Lines/Extra Lines");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "R/ESC: Reset/Close");
}

static void	draw_info(t_meta *meta)
{
	int	line;

	line = DRAWINFO_BOX;
	print_str(meta, MENU_TAB, line, "/// DRAW INFO ///");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Renders:");
	print_nbr(meta, MENU_TAB + 100, line, meta->map.renders);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Performance(ms):");
	print_nbr(meta, MENU_TAB + 170, line, meta->map.performance * 1000);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "X, Y, Z: [   ] [   ] [   ]");
	print_nbr(meta, MENU_TAB + 100, line, meta->map.ang[X]);
	print_nbr(meta, MENU_TAB + 160, line, meta->map.ang[Y]);
	print_nbr(meta, MENU_TAB + 220, line, meta->map.ang[Z]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Zoom:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.scale);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Z Divisor");
	print_nbr(meta, MENU_TAB + 110, line, meta->map.zdivisor);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Blending:");
	print_nbr(meta, MENU_TAB + 100, line, meta->map.brange * 10000);
}

void	draw_menu(t_meta *meta)
{
	draw_controls(meta);
	draw_info(meta);
	draw_mapinfo(meta);
	draw_colorscheme(meta);
}
