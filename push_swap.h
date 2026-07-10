/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-03 19:19:42 by tphuwian          #+#    #+#             */
/*   Updated: 2026-05-03 19:19:42 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	int				value;
	int				index;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
	t_node			*bottom;
	int				size;
}					t_stack;

// for_free
char				**free_split(char **box, int j);
void				free_stack(t_stack *stack);

// init
void				init_stack(t_stack *stack);
t_node				*new_node(int add_value);
void				add_node(t_stack *stack, t_node *new_node);
void				set_index(t_stack *stack);
int					is_sorted(t_stack *stack);

// main
// static int			build_stack(t_stack *a, int ac, char **av);
// static void			sort_stacks(t_stack *a, t_stack *b);
int					main(int ac, char **av);

// p_operation
// static void			do_push(t_stack *src, t_stack *dst);
void				pa(t_stack *stack_a, t_stack *stack_b);
void				pb(t_stack *stack_a, t_stack *stack_b);

// r_operation
// static void			do_rotate(t_stack *stack);
void				ra(t_stack *stack_a);
void				rb(t_stack *stack_b);
void				rr(t_stack *stack_a, t_stack *stack_b);

// rr_operation
// static void			do_rev_rotate(t_stack *stack);
void				rra(t_stack *stack_a);
void				rrb(t_stack *stack_b);
void				rrr(t_stack *stack_a, t_stack *stack_b);

// s_operation
// static void			do_swap(t_stack *stack);
void				sa(t_stack *stack_a);
void				sb(t_stack *stack_b);
void				ss(t_stack *stack_a, t_stack *stack_b);

// small_sort
// static int			get_min_pos(t_stack *a);
void				sort_3(t_stack *a);
void				sort_4(t_stack *a, t_stack *b);
void				sort_5(t_stack *a, t_stack *b);

// k_sort
void				k_sort(t_stack *a, t_stack *b);

// split
char				is_space(char c);
int					count_word(char *str);
char				*ft_substr(const char *str, int start, int len);
char				**ft_split(char *str);

// utils
void				ft_putstr(char *str, int fd);
int					check_duplicate(t_stack *stack);
long				ft_atol(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					is_valid_number(char *str);

// utils2
int					parse_and_add(t_stack *stack, char *str);
void				add_node_bottom(t_stack *stack, t_node *new_node);

#endif