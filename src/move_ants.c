/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:43:48 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/26 14:43:49 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	push_ant(t_ant **head, t_str_list *path, int num)
{
	t_ant *temp;

	if (!(*head))
	{
		*head = (t_ant *)malloc(sizeof(t_ant));
		temp = *head;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_ant *)malloc(sizeof(t_ant));
		temp = temp->next;
	}
	temp->num = num;
	temp->path = path;
	temp->next = NULL;
}

static void	print_ant(t_ant *ant)
{
	((ant->num % 6) == 0) ? ft_printf(URED) : 0;
	((ant->num % 6) == 1) ? ft_printf(UGRN) : 0;
	((ant->num % 6) == 2) ? ft_printf(UYEL) : 0;
	((ant->num % 6) == 3) ? ft_printf(UMAG) : 0;
	((ant->num % 6) == 4) ? ft_printf(UCYN) : 0;
	((ant->num % 6) == 5) ? ft_printf(UWHT) : 0;
	ft_printf("L%d-%s", ant->num, ant->path->name);
	ft_printf(RESET);
}

static void	move_available_ants(t_ant **ants)
{
	t_ant *temp_ants;
	t_ant *temp_ant;

	while ((*ants) && (*ants)->path == NULL)
	{
		temp_ants = (*ants)->next;
		free(*ants);
		*ants = temp_ants;
	}
	temp_ants = *ants;
	while (temp_ants)
	{
		if (temp_ants->next && !(temp_ants->next->path))
		{
			temp_ant = temp_ants->next->next;
			free(temp_ants->next);
			temp_ants->next = temp_ant;
		}
		if (temp_ants->path)
			print_ant(temp_ants);
		(temp_ants->path) ? (temp_ants->path = temp_ants->path->next) : 0;
		temp_ants = temp_ants->next;
		(temp_ants) ? ft_printf(" ") : 0;
	}
	(*ants) ? ft_printf("\n") : 0;
}

void		move_ants(t_str_path *paths, int ants)
{
	int			i;
	t_ant		*head_ants;
	t_str_path	*temp;

	i = 1;
	head_ants = NULL;
	ft_printf("\n");
	while (i <= ants || head_ants)
	{
		move_available_ants(&head_ants);
		temp = paths;
		while (temp && i <= ants)
		{
			push_ant(&head_ants, temp->path, i);
			temp = temp->next;
			i++;
		}
	}
}
