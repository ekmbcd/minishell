/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-feli <ade-feli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:46:41 by ade-feli          #+#    #+#             */
/*   Updated: 2021/03/12 11:50:34 by ade-feli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_left(int *cursor)
{
	if ((!g_lo.input[*cursor]) || (g_lo.input[*cursor]
		&& !(is_spaces(g_lo.input[*cursor]))))
	{
		(*cursor)--;
		write(1, "\033[1D", 4);
	}
	while ((is_spaces(g_lo.input[*cursor])))
	{
		(*cursor)--;
		write(1, "\033[1D", 4);
	}
	while (g_lo.input[*cursor] && !(is_spaces(g_lo.input[*cursor])))
	{
		(*cursor)--;
		write(1, "\033[1D", 4);
	}
	(*cursor)++;
	write(1, "\033[1C", 4);
}

void	skip_right(int *cursor)
{
	if ((g_lo.input[*cursor] && !(is_spaces(g_lo.input[*cursor]))))
	{
		(*cursor)++;
		write(1, "\033[1C", 4);
	}
	while ((is_spaces(g_lo.input[*cursor])))
	{
		(*cursor)++;
		write(1, "\033[1C", 4);
	}
	while (g_lo.input[*cursor] && !(is_spaces(g_lo.input[*cursor])))
	{
		(*cursor)++;
		write(1, "\033[1C", 4);
	}
}

int		skip_world(int *cursor, char c)
{
	if (c == '\xC')
	{
		skip_left(cursor);
		return (1);
	}
	if (c == '\x12')
	{
		skip_right(cursor);
		return (1);
	}
	return (0);
}

int		home_end(char c, int *cursor)
{
	if (c == '\x48')
	{
		while (*cursor > 0)
		{
			(*cursor)--;
			write(1, "\033[1D", 4);
		}
		return (1);
	}
	if (c == '\x46')
	{
		while (g_lo.input[*cursor])
		{
			(*cursor)++;
			write(1, "\033[1C", 4);
		}
		return (1);
	}
	return (0);
}
