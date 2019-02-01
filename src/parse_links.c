/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:22:20 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/25 20:22:21 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_links_error(int index, t_graph **graph,
	char **line, char **res)
{
	char	**errors;
	int		i;

	errors = (char **)malloc(7 * sizeof(char *));
	errors[0] = ft_strdup("ERROR - THERE SHOULD BE EXACTLY TWO ROOM NAMES \
IN THE LINK");
	errors[1] = ft_strdup("ERROR - WRONG ROOM1 NAME");
	errors[2] = ft_strdup("ERROR - WRONG ROOM2 NAME");
	errors[3] = ft_strdup("ERROR - THERE CAN BE NO EMPTY LINES");
	errors[4] = ft_strdup("ERROR - NO ROOM AFTER COMMAND");
	errors[5] = ft_strdup("ERROR - START ROOM DOESN'T HAVE CONNECTIONS");
	errors[6] = ft_strdup("ERROR - END ROOM DOESN'T HAVE CONNECTIONS");
	ft_printf("%s\n", errors[-1 * index - 1]);
	i = -1;
	while (++i < 7)
		ft_strdel(&errors[i]);
	free(errors);
	(line) ? ft_strdel(line) : 0;
	(res) ? ft_strdel(res) : 0;
	free_graph(&graph);
	exit(0);
}

static t_graph	*find_room(t_graph **graph, char *name)
{
	int i;

	if (!name)
		return (NULL);
	i = 0;
	while (graph[i]->name)
	{
		if (ft_strcmp(graph[i]->name, name) == 0)
			return (graph[i]);
		i++;
	}
	return (NULL);
}

static void		add_links(char *name1, char *name2, t_graph **graph)
{
	size_t i1;
	size_t i2;
	size_t i;

	i1 = 0;
	i2 = 0;
	i = 0;
	while (graph[i]->name)
	{
		if (ft_strcmp(graph[i]->name, name1) == 0)
			i1 = i;
		if (ft_strcmp(graph[i]->name, name2) == 0)
			i2 = i;
		i++;
	}
	if (i1 != i2)
	{
		push_head_num_list(i2, &(graph[i1]->connections));
		push_head_num_list(i1, &(graph[i2]->connections));
	}
}

static void		parse_link(t_graph **graph, char *line, char **res)
{
	char	**room_names;
	int		length;
	t_graph	*room1;
	t_graph	*room2;

	room_names = ft_strsplit(line, '-');
	length = 0;
	while (room_names[length])
		length++;
	room1 = find_room(graph, room_names[0]);
	room2 = find_room(graph, room_names[1]);
	free_rooms(&room_names, length);
	(length != 2) ? print_links_error(-1, graph, &line, res) : 0;
	(!room1) ? print_links_error(-2, graph, NULL, res) : 0;
	(!room2) ? print_links_error(-3, graph, NULL, res) : 0;
	add_links(room1->name, room2->name, graph);
}

void			parse_links(t_graph **graph, char *line, char **res)
{
	int i;

	while (line)
	{
		(!line[0]) ? print_links_error(-4, graph, &line, res) : 0;
		if (line[0] == '#')
			(parse_hashtag(line) == 1 || parse_hashtag(line) == 2) ?
					print_links_error(-5, graph, &line, res) : 0;
		else
			parse_link(graph, line, res);
		ft_strdel(&line);
		if (!get_next_line(0, &line))
			break ;
		ft_strconcat(res, line, ft_strlen(*res), ft_strlen(line));
		ft_strconcat(res, "\n", ft_strlen(*res), 1);
	}
	(!(i = 0) && line) ? ft_strdel(&line) : 0;
	(!graph[0]->connections) ? print_links_error(-6, graph, &line, res) : 0;
	while (graph[i]->name)
		i++;
	(!graph[i - 1]->connections) ? print_links_error(-7, graph, &line, res) : 0;
}
