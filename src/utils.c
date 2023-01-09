/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:47:58 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/22 13:43:21 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "../lib/minilibx_macos/mlx.h"
#include "../inc/defines.h"

void	print_nbr(t_meta *meta, int x, int y, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	mlx_string_put(meta->vars.mlx, meta->vars.win, x, y, NUMBER_COLOR, str);
	free (str);
}

void	print_str(t_meta *meta, int x, int y, char *str)
{
	mlx_string_put(meta->vars.mlx, meta->vars.win, x, y, TEXT_COLOR, str);
}

/*
 * Esta función redondea un double para devolver un int
 */
int	ft_round(double num)
{
	int	rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
}



/*
 * función que libera un doble puntero (double free)
 */
void	dbl_free(char **ptr)
{
	int	i;

	if (!ptr)
		return;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

/*
 * Esta función inicializa una matriz
 */
void	matrix_init(float (*matrix)[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}
