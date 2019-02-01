/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:37:22 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/26 16:37:23 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_graph(t_graph ***graph)
{
	int i;

	i = 0;
	while (graph[0][i]->name)
	{
		ft_strdel(&(graph[0][i]->name));
		free_num_list(&graph[0][i]->connections);
		free(graph[0][i]);
		i++;
	}
	free(graph[0][i]);
	free(graph[0]);
}

void	free_rooms(char ***rooms, int length)
{
	int i;

	i = -1;
	while (++i < length)
		ft_strdel(&(rooms[0][i]));
	free(*rooms);
	*rooms = NULL;
}

void	free_leaves_stack(t_leaves_stack **head)
{
	t_leaves_stack *temp;

	while (*head)
	{
		temp = (*head)->next;
		free((*head)->leaf);
		(*head)->leaf = NULL;
		free(*head);
		*head = NULL;
		*head = temp;
	}
}

void	free_tree(t_leaf **tree)
{
	t_leaves_stack *children;

	if (!(*tree)->children && (*tree)->parent)
		return ;
	children = (*tree)->children;
	while (children)
	{
		free_tree(&children->leaf);
		children = children->next;
	}
	free_leaves_stack(&(*tree)->children);
	if (!(*tree)->parent)
	{
		free(*tree);
		*tree = NULL;
	}
}
