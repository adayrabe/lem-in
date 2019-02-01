/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:00:13 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/26 17:00:14 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_leaf		*find_leaf(t_leaf *tree, size_t num)
{
	t_leaves_stack	*temp_stack;
	t_leaf			*res;

	if (tree->room_num == num)
		return (tree);
	temp_stack = tree->children;
	while (temp_stack)
	{
		res = find_leaf(temp_stack->leaf, num);
		if (res)
			return (res);
		temp_stack = temp_stack->next;
	}
	return (NULL);
}

static void	add_child(t_leaves_stack **stack, t_leaf **parent, size_t num)
{
	stack[0]->leaf = (t_leaf *)malloc(sizeof(t_leaf));
	stack[0]->next = NULL;
	stack[0]->leaf->parent = parent[0];
	stack[0]->leaf->children = NULL;
	stack[0]->leaf->room_num = num;
}

void		add_leaf(size_t num, t_leaf **parent)
{
	t_leaves_stack *temp;

	if (!(*parent))
	{
		*parent = (t_leaf *)malloc(sizeof(t_leaf));
		(*parent)->parent = NULL;
		(*parent)->room_num = num;
		(*parent)->children = NULL;
		return ;
	}
	if (!parent[0]->children)
	{
		parent[0]->children = (t_leaves_stack *)malloc(sizeof(t_leaves_stack));
		temp = parent[0]->children;
	}
	else
	{
		temp = parent[0]->children;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_leaves_stack *)malloc(sizeof(t_leaves_stack));
		temp = temp->next;
	}
	add_child(&temp, parent, num);
}
