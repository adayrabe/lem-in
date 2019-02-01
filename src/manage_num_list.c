/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_num_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:46:39 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/24 20:46:40 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	pop_num_list(t_num_list **head)
{
	t_num_list *temp;

	if (*head)
	{
		temp = (*head)->next;
		free(*head);
		*head = NULL;
		*head = temp;
	}
}

void	push_tail_num_list(size_t num, t_num_list **head)
{
	t_num_list *temp;

	if (!(*head))
	{
		*head = (t_num_list *)malloc(sizeof(t_num_list));
		temp = *head;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_num_list *)malloc(sizeof(t_num_list));
		temp = temp->next;
	}
	temp->i = num;
	temp->next = NULL;
}

void	push_head_num_list(size_t num, t_num_list **head)
{
	t_num_list *temp;

	if (!(*head))
	{
		*head = (t_num_list *)malloc(sizeof(t_num_list));
		(*head)->next = NULL;
		(*head)->i = num;
	}
	else
	{
		temp = (t_num_list *)malloc(sizeof(t_num_list));
		temp->i = num;
		temp->next = *head;
		*head = temp;
	}
}

void	free_num_list(t_num_list **head)
{
	t_num_list *temp;

	while (*head)
	{
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
}
