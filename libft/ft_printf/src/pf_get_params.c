/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:38:38 by nalexand          #+#    #+#             */
/*   Updated: 2019/05/28 12:06:33 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_flags(char fmt, t_task *task)
{
	if (fmt == '#')
		return (task->flags.sharp = 1);
	else if (fmt == '-')
		return (task->flags.minus = 1);
	else if (fmt == '+')
		return (task->flags.plus = 1);
	else if (fmt == ' ')
		return (task->flags.space = 1);
	else if (fmt == '0')
		return (task->flags.zero = 1);
	return (0);
}

void		get_width(char **fmt, t_task *task, va_list *args)
{
	long	tmp;

	if (**fmt == '*')
	{
		if ((tmp = va_arg(*args, int)) < INT32_MAX && tmp > INT32_MIN + 1L)
		{
			if (tmp < 0)
			{
				task->width = -tmp;
				task->flags.minus = 1;
			}
			else
				task->width = tmp;
		}
		while (**fmt && **fmt == '*')
			(*fmt)++;
	}
	else
	{
		task->width = ft_atoi(*fmt);
		while (**fmt && ft_isdigit(**fmt))
			(*fmt)++;
		if (task->width < 0)
			task->width = 0;
	}
}

void		get_prc(char **fmt, int *prc, va_list *args)
{
	long	tmp;

	while (**fmt == '.')
		(*fmt)++;
	if (**fmt == '*')
	{
		if ((tmp = va_arg(*args, int)) < INT32_MAX && tmp > INT32_MIN + 1L)
			*prc = tmp;
		else
			*prc = 0;
	}
	else
		*prc = ft_atoi(*fmt);
	if (*prc < 0)
		*prc = -1;
	while (ft_isdigit(**fmt) || **fmt == '*')
		(*fmt)++;
}

static void	set_params_size(t_size *size, char **fmt, char chr, size_t value)
{
	size->chr = chr;
	size->value = value;
	(*fmt) += (chr > 76 || chr == 70) ? 1 : 2;
}

void		get_size(char **fmt, t_size *size)
{
	t_size	tmp_size;

	tmp_size.chr = 0;
	tmp_size.value = 4;
	if (**fmt == 'h' && *(*fmt + 1) != 'h')
		set_params_size(&tmp_size, fmt, 'h', sizeof(short));
	else if (**fmt == 'h' && *(*fmt + 1) == 'h')
		set_params_size(&tmp_size, fmt, 'H', sizeof(char));
	else if (**fmt == 'l' && *(*fmt + 1) != 'l')
		set_params_size(&tmp_size, fmt, 'l', sizeof(long));
	else if (**fmt == 'l' && *(*fmt + 1) == 'l')
		set_params_size(&tmp_size, fmt, 'L', sizeof(long long));
	else if (**fmt == 'L')
		set_params_size(&tmp_size, fmt, 'f', sizeof(long double));
	else if (**fmt == 'j')
		set_params_size(&tmp_size, fmt, 'j', sizeof(intmax_t));
	else if (**fmt == 'z')
		set_params_size(&tmp_size, fmt, 'z', sizeof(size_t));
	if (size->chr)
	{
		if (size->value < tmp_size.value)
			*size = tmp_size;
	}
	else
		*size = tmp_size;
}
