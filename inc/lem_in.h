/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:39:15 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/24 20:40:51 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <libft.h>
# include "lem_in_structs.h"

t_graph				**parse_rooms(char **res);
void				parse_links(t_graph **graph, char *line, char **res);
t_graph				**make_graph(t_room **head, char **res);
void				print_rooms_error(int index, char **line,
	t_room **head, char **res);
char				parse_hashtag(char *line);
void				pop_num_list(t_num_list **head);
void				push_tail_num_list(size_t num, t_num_list **head);
void				push_head_num_list(size_t num, t_num_list **head);
void				free_num_list(t_num_list **head);
t_num_path			*find_paths(t_graph **graph);
void				free_graph(t_graph ***graph);
void				move_ants(t_str_path *paths, int ants);
int					add_room(char *line, t_room **head, int next, char **res);
void				free_graph(t_graph ***graph);
void				free_rooms(char ***rooms, int length);
void				free_leaves_stack(t_leaves_stack **head);
void				free_tree(t_leaf **tree);
void				add_leaf(size_t num, t_leaf **parent);
t_leaf				*find_leaf(t_leaf *tree, size_t num);
void				push_tail_str_list(char *name, t_str_list **head);
void				push_tail_str_path(t_str_list *list, t_str_path **head);
void				free_str_paths(t_str_path **paths);

#endif
