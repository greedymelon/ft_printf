/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 14:22:15 by dmonfrin      #+#    #+#                 */
/*   Updated: 2021/12/13 14:22:17 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_function.h"

static void	cleaning(const char *str, t_flag *bonus)
{
	int	i;
	int	zero;

	zero = 0;
	i = bonus->index;
	initialize(bonus);
	while (bonus->index < i && is_flag(str[bonus->index]))
	{
		if (str[bonus->index] == '+')
			bonus->plus_space = 1;
		if (str[bonus->index] == '-')
			bonus->padding_right = 1;
		if (str[bonus->index] == '#')
			bonus->prefix = 1;
		if (str[bonus->index] == '0')
			zero = 1;
		if (str[bonus->index] == ' ' && !bonus->plus_space)
			bonus->plus_space = 2;
		bonus->index++;
	}
	is_width(str, bonus);
	is_flag_dot(str, bonus);
	print_cleaning(str[i], bonus, zero);
}

static int	sort(const char *str, va_list ptr_variable, t_flag *bonus)
{
	if (str[bonus->index] == 'd' || str[bonus->index] == 'i')
		is_flag_d_i(va_arg(ptr_variable, int), bonus);
	else if (str[bonus->index] == 'u')
		is_flag_u(va_arg(ptr_variable, unsigned int), bonus);
	else if (str[bonus->index] == 'x' || str[bonus->index] == 'X')
		is_flag_x(str[bonus->index], va_arg(ptr_variable, unsigned int), bonus);
	else if (str[bonus->index] == 'p')
		is_flag_p(va_arg(ptr_variable, void *), bonus);
	else if (str[bonus->index] == 'c')
		is_flag_c(va_arg(ptr_variable, int), bonus);
	else if (str[bonus->index] == 's')
		is_flag_s(va_arg(ptr_variable, char *), bonus);
	else
		cleaning(str, bonus);
	return (bonus->index + 1);
}

static int	sort_bonus(const char *str, va_list ptr, t_flag *bonus)
{
	while (is_flag(str[bonus->index]))
	{
		if (str[bonus->index] == '+')
			bonus->plus_space = 1;
		if (str[bonus->index] == ' ' && bonus->plus_space != 1)
			bonus->plus_space = 2;
		if (str[bonus->index] == '-')
			bonus->padding_right = 1;
		if (str[bonus->index] == '#')
			bonus->prefix = 2;
		if (str[bonus->index] == '0')
			bonus->spc_zr = '0';
		bonus->index++;
	}
	is_width(str, bonus);
	is_flag_dot(str, bonus);
	return (sort(str, ptr, bonus));
}

static int	print_flag(va_list ptr, const char **str, t_flag *bonus, int s_pos)
{
	const char	*s;
	int			new_position;

	s = *str;
	initialize(bonus);
	bonus->printed_char += s_pos;
	new_position = 0;
	if (s[s_pos + 1] != '%')
	{
		new_position = sort_bonus(&s[s_pos + 1], ptr, bonus);
		s += s_pos + 1 + new_position;
	}
	else
	{
		write(1, "%", 1);
		s += s_pos + 2;
		bonus->printed_char += 1;
	}
	*str = s;
	if (new_position < 0)
		return (0);
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	t_flag	bonus;
	int		i;

	va_start(ptr, str);
	i = 0;
	bonus.printed_char = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			write(1, str, i);
			i = print_flag(ptr, &str, &bonus, i);
		}
		i++;
	}
	write(1, str, i);
	va_end(ptr);
	return (bonus.printed_char + i);
}
