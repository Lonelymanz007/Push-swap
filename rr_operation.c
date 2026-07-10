/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-09 08:55:11 by tphuwian          #+#    #+#             */
/*   Updated: 2026-07-09 08:55:11 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_rev_rotate(t_stack *stack)
{
	t_node	*old_bottom;

	if (!stack || stack->size < 2)
		return ;
	old_bottom = stack->bottom;
	stack->bottom = old_bottom->prev;
	stack->bottom->next = NULL;
	old_bottom->next = stack->top;
	old_bottom->prev = NULL;
	stack->top->prev = old_bottom;
	stack->top = old_bottom;
}

void	rra(t_stack *stack_a)
{
	do_rev_rotate(stack_a);
	ft_putstr("rra\n", 1);
}

void	rrb(t_stack *stack_b)
{
	do_rev_rotate(stack_b);
	ft_putstr("rrb\n", 1);
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	do_rev_rotate(stack_a);
	do_rev_rotate(stack_b);
	ft_putstr("rrr\n", 1);
}
