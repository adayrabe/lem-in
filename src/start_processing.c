/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:01:46 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/24 21:01:49 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_num_list	*make_list(t_leaf **tree, t_num_list **head_queue,
				t_leaf *end, size_t last)
{
	t_num_list *res;

	res = NULL;
	push_head_num_list(last, &res);
	while (end->parent)
	{
		push_head_num_list(end->room_num, &res);
		end = end->parent;
	}
	free_tree(tree);
	free_num_list(head_queue);
	return (res);
}

static t_num_list	*do_next(t_num_list *temp, t_num_list **head_queue,
		t_leaf **temp_leaf, t_graph **graph)
{
	if (!graph[temp->i]->temp_visited && !graph[temp->i]->visited)
	{
		push_tail_num_list(temp->i, head_queue);
		add_leaf(temp->i, temp_leaf);
		graph[temp->i]->temp_visited = 1;
	}
	temp = temp->next;
	return (temp);
}

static t_num_list	*find_path(t_graph **graph)
{
	t_num_list	*head_queue;
	t_leaf		*head_tree;
	t_num_list	*temp;
	t_leaf		*temp_leaf;

	head_queue = NULL;
	head_tree = NULL;
	push_tail_num_list(0, &head_queue);
	add_leaf(head_queue->i, &head_tree);
	while (head_queue)
	{
		temp = graph[head_queue->i]->connections;
		temp_leaf = find_leaf(head_tree, head_queue->i);
		while (temp)
		{
			if (graph[temp->i + 1]->name == NULL)
				return (make_list(&head_tree, &head_queue, temp_leaf, temp->i));
			temp = do_next(temp, &head_queue, &temp_leaf, graph);
		}
		pop_num_list(&head_queue);
	}
	free_tree(&head_tree);
	return (NULL);
}

static void			push_tail_num_path(t_num_list *list, t_num_path **head)
{
	t_num_path *temp;

	if (!(*head))
	{
		*head = (t_num_path *)malloc(sizeof(t_num_path));
		temp = *head;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_num_path *)malloc(sizeof(t_num_path));
		temp = temp->next;
	}
	temp->path = list;
	temp->next = NULL;
}

t_num_path			*find_paths(t_graph **graph)
{
	t_num_path	*num_paths;
	t_num_list	*temp_num_list;
	size_t		i;

	num_paths = NULL;
	graph[0]->visited = 1;
	while ((temp_num_list = find_path(graph)))
	{
		push_tail_num_path(temp_num_list, &num_paths);
		if (!(temp_num_list->next))
			break ;
		while (temp_num_list)
		{
			graph[temp_num_list->i]->visited = 1;
			temp_num_list = temp_num_list->next;
		}
		i = 0;
		while (graph[i]->name && ++i)
			graph[i - 1]->temp_visited = 0;
	}
	(!num_paths) ? ft_printf("ERROR - NO POSSIBLE SOLUTIONS\n") : 0;
	return (num_paths);
}
