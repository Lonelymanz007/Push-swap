/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_operation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-09 08:53:19 by tphuwian          #+#    #+#             */
/*   Updated: 2026-07-09 08:53:19 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_rotate(t_stack *stack)
{
	t_node	*old_top;

	if (!stack || stack->size < 2)
		return ;
	old_top = stack->top;
	stack->top = old_top->next;
	stack->top->prev = NULL;
	stack->bottom->next = old_top;
	old_top->prev = stack->bottom;
	old_top->next = NULL;
	stack->bottom = old_top;
}

void	ra(t_stack *stack_a)
{
	do_rotate(stack_a);
	ft_putstr("ra\n", 1);
}

void	rb(t_stack *stack_b)
{
	do_rotate(stack_b);
	ft_putstr("rb\n", 1);
}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	do_rotate(stack_a);
	do_rotate(stack_b);
	ft_putstr("rr\n", 1);
}
