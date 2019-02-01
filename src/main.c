/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:07:58 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/24 21:07:59 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char				parse_hashtag(char *line)
{
	if (!ft_strcmp("##start", line))
		return (1);
	if (!ft_strcmp("##end", line))
		return (2);
	return (0);
}

static int			get_amount_of_ants(char **res)
{
	char	*line;
	int		i;

	line = NULL;
	get_next_line(0, &line);
	while (line && line[0] == '#')
	{
		if (parse_hashtag(line) == 1 || parse_hashtag(line) == 2)
			print_rooms_error(-1, &line, NULL, res);
		ft_strconcat(res, line, ft_strlen(*res), ft_strlen(line));
		ft_strconcat(res, "\n", ft_strlen(*res), 1);
		ft_strdel(&line);
		get_next_line(0, &line);
	}
	(!line || !line[0]) ? print_rooms_error(-2, &line, NULL, res) : 0;
	i = -1;
	while (++i < (int)ft_strlen(line))
		if (!ft_isdigit(line[i]))
			print_rooms_error(-3, &line, NULL, res);
	i = ft_atoi(line);
	ft_strconcat(res, line, ft_strlen(*res), ft_strlen(line));
	ft_strconcat(res, "\n", ft_strlen(*res), 1);
	ft_strdel(&line);
	(i == 0) ? print_rooms_error(-2, NULL, NULL, res) : 0;
	return (i);
}

static t_str_list	*make_names(t_num_list *head, t_graph **graph)
{
	t_str_list *res;

	res = NULL;
	while (head)
	{
		push_tail_str_list(graph[head->i]->name, &res);
		head = head->next;
	}
	return (res);
}

static t_str_path	*make_paths(t_num_path **paths, t_graph **graph)
{
	t_str_path *str_paths;
	t_num_path *temp_p;
	t_num_path *num_paths;

	str_paths = NULL;
	num_paths = (*paths);
	while (num_paths)
	{
		push_tail_str_path(make_names(num_paths->path, graph), &str_paths);
		temp_p = num_paths->next;
		free_num_list(&(num_paths->path));
		free(num_paths);
		num_paths = temp_p;
	}
	return (str_paths);
}

int					main(void)
{
	int			ants;
	t_graph		**graph;
	t_num_path	*num_paths;
	t_str_path	*str_paths;
	char		*res;

	ants = get_amount_of_ants(&res);
	graph = parse_rooms(&res);
	num_paths = find_paths(graph);
	str_paths = make_paths(&num_paths, graph);
	free_graph(&graph);
	(str_paths) ? ft_printf("%s", res) : 0;
	(res) ? ft_strdel(&res) : 0;
	(str_paths) ? move_ants(str_paths, ants) : 0;
	free_str_paths(&str_paths);
	return (0);
}
