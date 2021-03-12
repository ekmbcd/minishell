/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-feli <ade-feli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:21:13 by ade-feli          #+#    #+#             */
/*   Updated: 2021/03/12 11:52:38 by ade-feli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_history(char *input)
{
	t_his *new;

	while (g_lo.history && g_lo.history->next)
		g_lo.history = g_lo.history->next;
	if (*input == 0)
		return ;
	if (!(new = malloc(sizeof(t_his))))
		return ;
	new->string = ft_strdup(input);
	new->previus = g_lo.history;
	new->next = 0;
	if (g_lo.history)
		g_lo.history->next = new;
	g_lo.history = new;
}

int		check_ctrl(char c, int *cursor)
{
	int i;

	if (c == '\x7f')
	{
		i = -1;
		if (*cursor == 0)
			return (1);
		while (g_lo.input[++i])
			if (g_lo.input[i] == '\n')
				write(1, "\033[1G\033[K\033[1A\033[K", 16);
		write(1, "\033[1G\033[K\e[32;1mÆ → \e[0m", 26);
		i = *cursor - 2;
		while (g_lo.input[++i])
			g_lo.input[i] = g_lo.input[i + 1];
		write(1, g_lo.input, ft_strlen(g_lo.input));
		while (i-- > *cursor)
			write(1, "\033[1D", 4);
		(*cursor)--;
		return (1);
	}
	if (c == '\x4' && *g_lo.input == 0)
		cute_cat(0);
	return (0);
}

int		copy_paste(char c, int *cursor)
{
	if (c == '\x18')
	{
		g_lo.paste = ft_strdup(&g_lo.input[*cursor]);
		g_lo.input[*cursor] = 0;
		write(1, "\033[1G\033[K", 8);
		write(1, "\e[32;1mÆ → \e[0m", 18);
		write(1, g_lo.input, ft_strlen(g_lo.input));
		return (1);
	}
	if (c == '\x16')
	{
		g_lo.input = ft_strjoin(g_lo.input, g_lo.paste);
		write(1, "\033[1G\033[K", 8);
		write(1, "\e[32;1mÆ → \e[0m", 18);
		write(1, g_lo.input, ft_strlen(g_lo.input));
		*cursor = ft_strlen(g_lo.input);
		return (1);
	}
	if (c == '\x19')
	{
		g_lo.paste = ft_strdup(&g_lo.input[*cursor]);
		return (1);
	}
	return (0);
}
