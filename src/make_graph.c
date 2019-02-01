/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:44:31 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/24 20:44:33 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		count_rooms(t_room **head, char **line)
{
	int		res;
	t_room	*temp;
	int		start;
	int		end;

	res = 0;
	temp = *head;
	start = 0;
	end = 0;
	while (temp)
	{
		res++;
		if (temp->start && temp->end)
			print_rooms_error(-15, NULL, head, line);
		(temp->start) ? start++ : 0;
		(temp->end) ? end++ : 0;
		temp = temp->next;
	}
	if (!start)
		print_rooms_error(-12, NULL, head, line);
	if (!end)
		print_rooms_error(-13, NULL, head, line);
	return (res);
}

static t_graph	*add_to_graph(t_room *room)
{
	t_graph *res;

	res = (t_graph *)malloc(sizeof(t_graph));
	if (room)
	{
		res->name = ft_strdup(room->name);
		res->x = room->x;
		res->y = room->y;
		res->connections = NULL;
		res->temp_visited = 0;
		res->visited = 0;
	}
	else
	{
		res->name = NULL;
		res->connections = NULL;
	}
	return (res);
}

static void		remove_last_room(t_room **head)
{
	t_room *temp;

	temp = *head;
	while (temp->next && !ft_strchr(temp->next->name, '-'))
		temp = temp->next;
	ft_strdel(&temp->next->name);
	free(temp->next);
	temp->next = NULL;
}

t_graph			**make_graph(t_room **head, char **line)
{
	t_graph	**graph;
	int		i;
	int		len;
	t_room	*temp;
	int		start_end;

	remove_last_room(head);
	len = count_rooms(head, line);
	graph = (t_graph **)malloc((len + 1) * sizeof(t_graph *));
	i = 0;
	temp = *head;
	start_end = 0;
	while (++i <= len)
	{
		if (temp->start && ++start_end)
			graph[0] = add_to_graph(temp);
		else if (temp->end && ++start_end)
			graph[len - 1] = add_to_graph(temp);
		else
			graph[i - start_end] = add_to_graph(temp);
		temp = temp->next;
	}
	graph[len] = add_to_graph(NULL);
	return (graph);
}
