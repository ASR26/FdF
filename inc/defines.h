/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:08:24 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/09 11:14:18 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# include <stdbool.h>

# define WINX 1920
# define WINY 1080

# define X 0
# define Y 1
# define Z 2

# define LAT 0
# define LONG 1

# define ROJO 		0xE34523
# define VERDE		0x1FC644
# define FUCSIA 	0xFF2599
# define AZUL		0x1683E9
# define SUPERAZUL	0x0000FF
# define CARBON		0x151515
# define WHITE		0xCBCBCB
# define DISCO		0x9C1869
# define BRICK_RED	0xB6274A
# define FLAMINGO	0xE83E18
# define JAFFA		0xE78335
# define SAFFRON	0xF3B244

# define DEFAULT_COLOR	JAFFA
# define BOTTOM_COLOR	AZUL
# define TOP_COLOR		BRICK_RED
# define GROUND_COLOR	SAFFRON
# define BACK_COLOR		CARBON
# define MENU_COLOR		0x202020
# define TEXT_COLOR		0xEAEAEA
# define NUMBER_COLOR	SAFFRON

# define MENU_WIDTH	350
# define FIT_MARGIN	50

# define FIT		1
# define FREE		0

typedef struct s_point {
	float	axis[3];
	int		color;
	bool	paint;
}	t_point;

typedef struct m_colors {
	int	topcolor;
	int	groundcolor;
	int	bottomcolor;
	int	backcolor;
	int	menucolor;
}	t_colors;

typedef struct s_bitmap {
	void	*img;
	char	*buffer;
	int		bitxpixel;
	int		lines;
	int		endian;
}	t_bitmap;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_keys{
	bool	b_mouse_l;
	bool	b_mouse_r;
	bool	b_keyctrl;
	t_point	last_click_l;
	t_point	last_click_r;
}	t_keys;

typedef struct m_map {
	t_point		*points;
	t_point		limits;
	t_point		source;
	t_colors	colors;
	int			zmin;
	float		ang[3];
	float		zdivisor;
	float		scale;
	int			len;
	float		brange;
	int			renders;
	bool		b_lines;
	bool		b_dots;
	bool		b_pluslines;
	double		performance;
	float		proportion;
	float		radius;
}	t_map;

typedef struct s_meta {
	t_vars		vars;
	t_bitmap	bitmap;
	t_map		map;
	t_keys		keys;
}	t_meta;
#endif
