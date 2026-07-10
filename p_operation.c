/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_operation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-09 08:52:49 by tphuwian          #+#    #+#             */
/*   Updated: 2026-07-09 08:52:49 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_push(t_stack *src, t_stack *dst)
{
	t_node	*node_to_move;

	if (!src || src->size == 0)
		return ;
	node_to_move = src->top;
	src->top = src->top->next;
	if (src->top != NULL)
		src->top->prev = NULL;
	else
		src->bottom = NULL;
	src->size--;
	if (dst->size == 0)
	{
		dst->top = node_to_move;
		dst->bottom = node_to_move;
		node_to_move->next = NULL;
	}
	else
	{
		node_to_move->next = dst->top;
		dst->top->prev = node_to_move;
		dst->top = node_to_move;
	}
	node_to_move->prev = NULL;
	dst->size++;
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	do_push(stack_b, stack_a);
	ft_putstr("pa\n", 1);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	do_push(stack_a, stack_b);
	ft_putstr("pb\n", 1);
}
