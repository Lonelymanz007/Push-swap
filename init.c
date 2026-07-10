/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-04 16:37:33 by tphuwian          #+#    #+#             */
/*   Updated: 2026-05-04 16:37:33 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack(t_stack *stack)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}

t_node	*new_node(int add_value)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = add_value;
	node->index = -1;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	add_node(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->size == 0)
	{
		stack->top = new_node;
		stack->bottom = new_node;
	}
	else
	{
		new_node->prev = stack->bottom;
		stack->bottom->next = new_node;
		stack->bottom = new_node;
	}
	stack->size++;
}

void	set_index(t_stack *stack)
{
	t_node	*current;
	t_node	*minimum_node;
	int		i;

	i = 0;
	while (i < stack->size)
	{
		current = stack->top;
		minimum_node = NULL;
		while (current != NULL)
		{
			if (current->index == -1)
			{
				if (minimum_node == NULL
					|| current->value < minimum_node->value)
					minimum_node = current;
			}
			current = current->next;
		}
		if (minimum_node != NULL)
			minimum_node->index = i;
		i++;
	}
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || stack->top == NULL)
		return (1);
	current = stack->top;
	while (current->next != NULL)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}
