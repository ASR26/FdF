/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:34:35 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 09:01:26 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función copia de forma no destructiva, si el recurso y el destino se
 * solapan lo hará de forma que se pueda completar la copia*/
/*si el src es menor que el destino empezamos a copiar desde detrás hacia 
 * adelante (primera condición)*/
/* si no simplemente copiamos de izquierda a derecha*/
#include"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*ret;

	ret = (char *)dest;
	if (dest == src)
		return (ret);
	if (src < dest)
	{
		while (len--)
			*(char *)(dest + len) = *(char *)(src + len);
	}
	else
	{
		while (len--)
		{
			*(char *)dest++ = *(char *)src++;
		}
	}
	return (ret);
}
