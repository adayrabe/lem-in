/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_str_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:11:46 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/26 17:11:47 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		push_tail_str_list(char *name, t_str_list **head)
{
	t_str_list *temp;

	if (!(*head))
	{
		*head = (t_str_list *)malloc(sizeof(t_str_list));
		temp = *head;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_str_list *)malloc(sizeof(t_str_list));
		temp = temp->next;
	}
	temp->name = ft_strdup(name);
	temp->next = NULL;
}

void		push_tail_str_path(t_str_list *list, t_str_path **head)
{
	t_str_path *temp;

	if (!(*head))
	{
		*head = (t_str_path *)malloc(sizeof(t_str_path));
		temp = *head;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_str_path *)malloc(sizeof(t_str_path));
		temp = temp->next;
	}
	temp->path = list;
	temp->next = NULL;
}

void		free_str_list(t_str_list **head)
{
	t_str_list *temp;

	while (*head)
	{
		temp = (*head)->next;
		ft_strdel(&((*head)->name));
		free(*head);
		*head = NULL;
		*head = temp;
	}
}

void		free_str_paths(t_str_path **paths)
{
	t_str_path *temp;

	while (*paths)
	{
		temp = (*paths)->next;
		free_str_list(&((*paths)->path));
		free(*paths);
		*paths = temp;
	}
}
