/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:47:37 by rpontici          #+#    #+#             */
/*   Updated: 2025/01/20 19:47:39 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(unsigned long n)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hex(n / 16);
	}
	count += ft_putchar(hex[n % 16]);
	return (count);
}

int	ft_printf_ptr(va_list x)
{
	void	*ptr;
	int		count;

	count = 0;
	ptr = va_arg(x, void *);
	if (!ptr)
	{
		count += ft_putstr("(nil)");
	}
	else
	{
		count += ft_putstr("0x");
		count += ft_putnbr_hex((unsigned long)ptr);
	}
	return (count);
}

int	puthex_recursive(unsigned int n, const char *hex)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += puthex_recursive(n / 16, hex);
	count += ft_putchar(hex[n % 16]);
	return (count);
}

int	ft_puthex_dw(va_list x)
{
	unsigned int	n;
	char			*hex;
	int				count;

	hex = "0123456789abcdef";
	n = va_arg(x, unsigned int);
	count = 0;
	count += puthex_recursive(n, hex);
	return (count);
}

int	ft_puthex_up(va_list x)
{
	unsigned int	n;
	char			*hex;
	int				count;

	hex = "0123456789ABCDEF";
	n = va_arg(x, unsigned int);
	count = 0;
	count += puthex_recursive(n, hex);
	return (count);
}
