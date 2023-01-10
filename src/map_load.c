/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:14:56 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/10 08:50:48 by asolano-         ###   ########.fr       */
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

void	load_color(int max, int min, t_point *point, t_colors colors)
{
	point->paint = 1;
	point->color = DEFAULT_COLOR;
	if (point->axis[Z] == max)
		point->color = colors.topcolor;
	else if (point->axis[Z] == 0)
		point->color = colors.groundcolor;
	else if (point->axis[Z] == min && min != 0)
		point->color = colors.bottomcolor;
	else if (point->axis[Z] > 0)
		point->color = gradient(colors.groundcolor, colors.topcolor, \
		max, point->axis[Z]);
	else
		point->color = gradient(colors.bottomcolor, colors.groundcolor, \
		-min, - (min - point->axis[Z]));
}

void	load_hexcolors(t_map *map, char *line)
{
	char	**color;

	if (ft_strchr(line, ',') != 0)
	{
		color = ft_split(line, ',');
			map->points[map->len].color = strtol(color[1] + 2, NULL, 16);
		dbl_free(color);
	}
}

static void	load_points(char *line, t_map *map, int numline)
{
	char	**splitted;
	int		i;

	splitted = ft_split(line, ' ');
	i = 0;
	while (splitted[i] && splitted[i][0] != '\n')
	{
		if (!valid_point(&splitted[i][0]))
			terminate(ERR_EMPTY);
		map->points[map->len].axis[Z] = ft_atoi(&splitted[i][0]);
		map->points[map->len].axis[X] = i - map->limits.axis[X] / 2;
		map->points[map->len].axis[Y] = numline - map->limits.axis[Y] / 2;
		load_color((int)map->limits.axis[Z], map->zmin, \
		&map->points[map->len], map->colors);
		load_hexcolors(map, splitted[i]);
		i++;
		map->len++;
	}
	dbl_free(splitted);
}

static void	map_size(char *path, t_map *map)
{
	char	*line;
	char	**splitted;
	int		linelen;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 2)
		terminate(ERR_OPEN);
	line = get_next_line(fd);
	while (line != NULL)
	{
		splitted = ft_split(line, ' ');
		z_limits(splitted, map);
		linelen = line_elems(splitted);
		if (map->limits.axis[X] == 0)
			map->limits.axis[X] = linelen;
		if (map->limits.axis[X] != linelen)
			terminate(ERR_LINE);
		map->len += map->limits.axis[X];
		map->limits.axis[Y]++;
		dbl_free(splitted);
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}

void	load_map(t_map *map, char *path)
{
	int		fd;
	char	*line;
	int		numline;

	map_ini(map, 1);
	map_size(path, map);
	map->points = ft_calloc (map->len, sizeof(t_point));
	if (map->points == NULL)
		terminate(ERR_MEM);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		terminate(ERR_OPEN);
	numline = 0;
	map->len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		numline++;
		load_points(line, map, numline);
		free(line);
		line = get_next_line(fd);
	}
}
