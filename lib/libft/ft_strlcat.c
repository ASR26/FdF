/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:00:08 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/21 12:34:03 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función concatena 2 strings hasta un límite de caracteres, coge el src y
 * lo copia a partir del final del dest, pero la longitud empieza al principio
 * del dest, es decir, va a contar los caracteres de dest, va a copiar los que 
 * falten para llegar al size - 1 y ese último caracter será el final de línea
 * */
#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dest_len;

	i = 0;
	j = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = dest_len;
	if (size == 0)
		return (src_len);
	if (size < dest_len)
		return (src_len + size);
	else
	{
		while (src[j] && (dest_len + j) < size)
			dest[i++] = src[j++];
		if ((dest_len + j) == size && dest_len < size)
			dest[--i] = '\0';
		else
			dest[i] = '\0';
		return (src_len + dest_len);
	}
}
