/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_bon_flag.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 14:20:58 by dmonfrin      #+#    #+#                 */
/*   Updated: 2021/12/13 14:21:01 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_function.h"

int	is_flag(char c)
{
	return (c == ' ' || c == '+' || c == '-' || c == '#' || c == '0');
}

void	is_flag_dot(const char *str, t_flag *bonus)
{
	if (str[bonus->index] == '.')
	{
		bonus->dot = 1;
		bonus->spc_zr = ' ';
		bonus->index++;
		bonus->precision = ft_atoi(&str[bonus->index]);
		while (ft_isdigit(str[bonus->index]))
			bonus->index++;
	}
}

void	is_width(const char *str, t_flag *bonus)
{
	if (ft_isdigit(str[bonus->index]))
	{
		bonus->width = ft_atoi(&str[bonus->index]);
		while (ft_isdigit(str[bonus->index]))
			bonus->index++;
	}
}

void	is_flag_c(const char c, t_flag *bonus)
{
	bonus->width -= 1;
	if (!bonus->padding_right)
		print_padding(bonus->width, ' ', &bonus->printed_char);
	ft_putchar_fd(c, 1);
	if (bonus->padding_right)
		print_padding(bonus->width, ' ', &bonus->printed_char);
	bonus->printed_char += 1;
}
