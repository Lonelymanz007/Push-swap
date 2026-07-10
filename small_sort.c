/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-10 18:00:43 by tphuwian          #+#    #+#             */
/*   Updated: 2026-07-10 18:00:43 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_pos(t_stack *a)
{
	t_node	*curr;
	int		min_val;
	int		min_pos;
	int		pos;

	curr = a->top;
	min_val = curr->value;
	pos = 0;
	min_pos = 0;
	while (curr)
	{
		if (curr->value < min_val)
		{
			min_val = curr->value;
			min_pos = pos;
		}
		pos++;
		curr = curr->next;
	}
	return (min_pos);
}

void	sort_3(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	if (!a || a->size != 3)
		return ;
	top = a->top->value;
	mid = a->top->next->value;
	bot = a->top->next->next->value;
	if (top > mid && top > bot)
		ra(a);
	else if (mid > top && mid > bot)
		rra(a);
	top = a->top->value;
	mid = a->top->next->value;
	if (top > mid)
		sa(a);
}

void	sort_4(t_stack *a, t_stack *b)
{
	int	pos;

	if (!a || a->size != 4)
		return ;
	pos = get_min_pos(a);
	while (pos > 0 && pos <= a->size / 2)
	{
		ra(a);
		pos--;
	}
	while (pos > a->size / 2 && pos < a->size)
	{
		rra(a);
		pos++;
	}
	pb(a, b);
	sort_3(a);
	pa(a, b);
}

void	sort_5(t_stack *a, t_stack *b)
{
	int	pos;

	if (!a || a->size != 5)
		return ;
	while (a->size > 3)
	{
		pos = get_min_pos(a);
		while (pos > 0 && pos <= a->size / 2)
		{
			ra(a);
			pos--;
		}
		while (pos > a->size / 2 && pos < a->size)
		{
			rra(a);
			pos++;
		}
		pb(a, b);
	}
	sort_3(a);
	pa(a, b);
	pa(a, b);
}
