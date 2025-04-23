/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:48:04 by rpontici          #+#    #+#             */
/*   Updated: 2025/01/20 19:51:54 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(char c, va_list x)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar_va(x);
	else if (c == 's')
		count = ft_putstr_va(x);
	else if (c == 'p')
		count = ft_printf_ptr(x);
	else if (c == 'd')
		count = ft_putnbr(x);
	else if (c == 'i')
		count = ft_putnbr(x);
	else if (c == 'u')
		count = ft_putnbr_u(x);
	else if (c == 'x')
		count = ft_puthex_dw(x);
	else if (c == 'X')
		count = ft_puthex_up(x);
	else if (c == '%')
	{
		count = 1;
		write(1, "%", 1);
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_check(str[i], args);
			i++;
		}
		else
		{
			count++;
			write(1, &str[i], 1);
			i++;
		}
	}
	va_end (args);
	return (count);
}
/*
int main(void)
{
    char    *str = "Così parlò Zarathustra";
    char    c = 'R';
    //int n = 42;
    //float   f = 0.42;
    
    printf("%d\n", printf("PRINTF: Ciao  %s %c\n", str, c));
    printf("%d\n", ft_printf("MIO: Ciao %s %c\n", str, c));
    return (0);
}*/
