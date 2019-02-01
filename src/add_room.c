/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:48:48 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/26 15:48:50 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		add_coordinate(char **line, t_room **head, char **res)
{
	size_t i;

	if (!line[0][0] || (line[0][0] == '-' && !line[0][1]))
		print_rooms_error(-5, line, head, res);
	i = 0;
	while (i < ft_strlen(*line))
	{
		if (!ft_isdigit(line[0][i]) && !(line[0][i] == '-' && i == 0))
			print_rooms_error(-6, line, head, res);
		i++;
	}
	return (ft_atoi(*line));
}

static t_room	*make_room(t_room **head)
{
	t_room *temp_room;

	if (!(*head))
	{
		*head = (t_room *)malloc(sizeof(t_room));
		temp_room = *head;
		temp_room->next = NULL;
	}
	else
	{
		temp_room = (*head);
		while (temp_room->next)
			temp_room = temp_room->next;
		temp_room->next = (t_room *)malloc(sizeof(t_room));
		temp_room = temp_room->next;
		temp_room->next = NULL;
	}
	return (temp_room);
}

static void		check_rooms(t_room *temp_room, t_room **head, char **res)
{
	t_room	*temp;
	int		starts;
	int		ends;

	temp = *head;
	starts = 0;
	ends = 0;
	while (temp->next)
	{
		if (!ft_strcmp(temp_room->name, temp->name))
			print_rooms_error(-8, NULL, head, res);
		if (temp_room->x == temp->x && temp_room->y == temp->y)
			print_rooms_error(-9, NULL, head, res);
		(starts && temp->start) ? print_rooms_error(-10, NULL, head, res) : 0;
		(temp->start) ? starts++ : 0;
		(ends && temp->end) ? print_rooms_error(-11, NULL, head, res) : 0;
		(temp->end) ? ends++ : 0;
		temp = temp->next;
	}
	(starts && temp_room->start) ? print_rooms_error(-10, NULL, head, res) : 0;
	(ends && temp_room->end) ? print_rooms_error(-11, NULL, head, res) : 0;
}

static void		add_start_end(t_room *temp_room, int next)
{
	temp_room->start = 0;
	temp_room->end = 0;
	(next == 1 || next == 3) ? temp_room->start = 1 : 0;
	(next == 2 || next == 3) ? temp_room->end = 1 : 0;
}

int				add_room(char *line, t_room **head, int next, char **res)
{
	char	*temp_x;
	char	*temp_y;
	t_room	*temp_room;

	temp_room = make_room(head);
	temp_room->name = ft_strdup_until(line, ' ');
	if (ft_strchr(temp_room->name, '-'))
		return (0);
	(!temp_room->name[0]) ? print_rooms_error(-17, &line, head, res) : 0;
	(temp_room->name[0] == 'L') ? print_rooms_error(-7, &line, head, res) : 0;
	if (line[ft_strlen(temp_room->name) + 1] == ' ')
		print_rooms_error(-18, &line, head, res);
	temp_x = ft_strdup_until(line + ft_strlen(temp_room->name) + 1, ' ');
	temp_room->x = add_coordinate(&temp_x, head, res);
	if (line[ft_strlen(temp_room->name) + ft_strlen(temp_x) + 2] == ' ')
		print_rooms_error(-4, &temp_x, head, res);
	temp_y = ft_strdup(line + ft_strlen(temp_room->name) +
		ft_strlen(temp_x) + 2);
	ft_strdel(&temp_x);
	temp_room->y = add_coordinate(&temp_y, head, res);
	ft_strdel(&temp_y);
	add_start_end(temp_room, next);
	check_rooms(temp_room, head, res);
	return (1);
}
