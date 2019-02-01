/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:48:03 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/24 20:48:04 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_room(t_room **head)
{
	t_room *temp;

	while (head && *head)
	{
		temp = (*head)->next;
		ft_strdel(&(*head)->name);
		free(*head);
		*head = temp;
	}
}

static void	add_errors(char ***errors)
{
	errors[0][0] = ft_strdup("ERROR - NO ROOM AFTER COMMAND");
	errors[0][1] = ft_strdup("ERROR - NO NUMBER OF ANTS");
	errors[0][2] = ft_strdup("ERROR - WRONG AMOUNT OF ANTS");
	errors[0][3] = ft_strdup("ERROR - THERE SHOULD BE ONE SPACE BETWEEN \
TWO COORDINATES");
	errors[0][4] = ft_strdup("ERROR - NOT ENOUGH COORDINATES FOR ROOM");
	errors[0][5] = ft_strdup("ERROR - ROOM COORDINATES MUST BE ONLY \
TWO INTEGERS");
	errors[0][6] = ft_strdup("ERROR - ROOM NAME CAN NOT START WITH L");
	errors[0][7] = ft_strdup("ERROR - TWO ROOMS WITH THE SAME NAME");
	errors[0][8] = ft_strdup("ERROR - TWO ROOMS ON THE SAME COORDINATES");
	errors[0][9] = ft_strdup("ERROR - TWO ROOMS CAN NOT BE START AT \
THE SAME TIME");
	errors[0][10] = ft_strdup("ERROR - TWO ROOMS CAN NOT BE END AT \
THE SAME TIME");
	errors[0][11] = ft_strdup("ERROR - NO START ROOM");
	errors[0][12] = ft_strdup("ERROR - NO END ROOM");
	errors[0][13] = ft_strdup("ERROR - NO ROOMS");
	errors[0][14] = ft_strdup("ERROR - ALL ANTS ARE ALREADY IN THE END ROOM");
	errors[0][15] = ft_strdup("ERROR - THERE CAN BE NO EMPTY LINES");
	errors[0][16] = ft_strdup("ERROR - ROOM MUST HAVE A NAME AND IT SHOULDN'T \
START WITH A SPACE");
	errors[0][17] = ft_strdup("ERROR - THERE SHOULD BE ONE SPACE BETWEEN \
NAME AND COORDINATES");
	errors[0][18] = ft_strdup("ERROR - NO LINKS");
}

void		print_rooms_error(int index, char **line, t_room **head, char **res)
{
	char	**errors;
	int		i;

	(line) ? ft_strdel(line) : 0;
	(res) ? ft_strdel(res) : 0;
	free_room(head);
	errors = (char **)malloc(19 * sizeof(char *));
	add_errors(&errors);
	ft_printf("%s\n", errors[-1 * index - 1]);
	i = -1;
	while (++i < 19)
		ft_strdel(&errors[i]);
	free(errors);
	exit(0);
}

static int	parse_line(char *line, t_room **head, char **res, char *next)
{
	int ret;

	ret = 1;
	if (line[0] == '#')
		*next += parse_hashtag(line);
	else
	{
		(!line[0]) ? print_rooms_error(-16, &line, head, res) : 0;
		ret = add_room(line, head, *next, res);
		(ret == 0 && *next) ? print_rooms_error(-1, &line, head, res) : 0;
		*next = 0;
	}
	return (ret);
}

t_graph		**parse_rooms(char **res)
{
	char	*line;
	t_graph	**graph;
	int		ret;
	char	next;
	t_room	*head;

	ret = 1;
	next = 0;
	head = NULL;
	while (ret && get_next_line(0, &line))
	{
		ft_strconcat(res, line, ft_strlen(*res), ft_strlen(line));
		ft_strconcat(res, "\n", ft_strlen(*res), 1);
		ret = parse_line(line, &head, res, &next);
		(ret == 1) ? ft_strdel(&line) : 0;
	}
	(!head) ? print_rooms_error(-14, &line, NULL, res) : 0;
	(!line) ? print_rooms_error(-19, &line, &head, res) : 0;
	graph = make_graph(&head, res);
	free_room(&head);
	parse_links(graph, line, res);
	return (graph);
}
