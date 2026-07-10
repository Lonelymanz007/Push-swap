/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-04 07:17:15 by tphuwian          #+#    #+#             */
/*   Updated: 2026-05-04 07:17:15 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_split(t_stack *a, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!parse_and_add(a, args[i]))
		{
			free_split(args, -1);
			return (0);
		}
		i++;
	}
	free_split(args, -1);
	return (1);
}

static int	handle_split(t_stack *a, char *str)
{
	char	**args;

	args = ft_split(str);
	if (!args || !args[0])
	{
		if (args)
			free_split(args, -1);
		return (0);
	}
	return (parse_split(a, args));
}

static int	build_stack(t_stack *a, int ac, char **av)
{
	int	i;

	if (ac == 2)
	{
		if (!handle_split(a, av[1]))
			return (0);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if (!parse_and_add(a, av[i]))
				return (0);
			i++;
		}
	}
	if (check_duplicate(a))
		return (0);
	return (1);
}

static void	sort_stacks(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sa(a);
	else if (a->size == 3)
		sort_3(a);
	else if (a->size == 4)
		sort_4(a, b);
	else if (a->size == 5)
		sort_5(a, b);
	else
		k_sort(a, b);
}

int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;

	if (ac < 2)
		return (0);
	init_stack(&a);
	init_stack(&b);
	if (!build_stack(&a, ac, av))
	{
		ft_putstr("Error\n", 2);
		free_stack(&a);
		return (1);
	}
	if (is_sorted(&a))
	{
		free_stack(&a);
		return (0);
	}
	set_index(&a);
	sort_stacks(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
