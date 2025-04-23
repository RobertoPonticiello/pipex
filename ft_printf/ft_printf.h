/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:48:53 by rpontici          #+#    #+#             */
/*   Updated: 2025/01/20 19:48:56 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(char c);
int	ft_putchar_va(va_list x);
int	ft_putnbr(va_list x);
int	ft_putnbr_u(va_list x);
int	ft_print_unsigned_recursive(unsigned int n);
int	ft_putstr(char *c);
int	ft_putstr_va(va_list x);
int	ft_puthex_dw(va_list x);
int	ft_puthex_up(va_list x);
int	ft_printf_ptr(va_list x);
int	ft_putnbr_hex(unsigned long n);
int	puthex_recursive(unsigned int n, const char *hex);
int	ft_print_int_recursive(int n);

#endif
