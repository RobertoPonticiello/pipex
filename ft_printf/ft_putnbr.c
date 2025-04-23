/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:46:42 by rpontici          #+#    #+#             */
/*   Updated: 2025/01/16 17:30:54 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int_recursive(int n)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n > 9)
		count += ft_print_int_recursive(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	return (count + 1);
}

int	ft_putnbr(va_list x)
{
	int	n;

	n = va_arg(x, int);
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	return (ft_print_int_recursive(n));
}
