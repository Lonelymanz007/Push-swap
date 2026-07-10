/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-10 18:50:55 by tphuwian          #+#    #+#             */
/*   Updated: 2026-07-10 18:50:55 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_pos(t_stack *b, int max_idx)
{
	t_node	*curr;
	int		pos;

	curr = b->top;
	pos = 0;
	while (curr)
	{
		if (curr->index == max_idx)
			return (pos);
		pos++;
		curr = curr->next;
	}
	return (0);
}

static void	k_sort_phase1(t_stack *a, t_stack *b, int size)
{
	int	i;
	int	k;

	i = 0;
	k = 15;
	if (size > 100)
		k = 35;
	while (a->size > 0)
	{
		if (a->top->index <= i)
		{
			pb(a, b);
			i++;
		}
		else if (a->top->index <= i + k)
		{
			pb(a, b);
			rb(b);
			i++;
		}
		else
			ra(a);
	}
}

void	k_sort(t_stack *a, t_stack *b)
{
	int	max;
	int	pos;

	k_sort_phase1(a, b, a->size);
	max = b->size - 1;
	while (b->size > 0)
	{
		pos = get_max_pos(b, max);
		while (pos > 0 && pos <= b->size / 2)
		{
			rb(b);
			pos--;
		}
		while (pos > b->size / 2 && pos < b->size)
		{
			rrb(b);
			pos++;
		}
		pa(a, b);
		max--;
	}
}
