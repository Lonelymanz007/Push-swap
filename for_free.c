/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-08 09:57:30 by tphuwian          #+#    #+#             */
/*   Updated: 2026-07-08 09:57:30 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	**free_split(char **box, int j)
{
	while (j > 0)
	{
		j--;
		free(box[j]);
	}
	free(box);
	return (NULL);
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*temp;

	if (!stack || stack->top == NULL)
		return ;
	current = stack->top;
	while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}
