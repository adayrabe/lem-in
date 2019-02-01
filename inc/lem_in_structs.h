/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:14:16 by adayrabe          #+#    #+#             */
/*   Updated: 2018/10/26 17:14:17 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCTS_H
# define LEM_IN_STRUCTS_H
# include <stdbool.h>
# define UBLK "\x1B[4;30m"
# define URED "\x1B[4;31m"
# define UGRN "\x1B[4;32m"
# define UYEL "\x1B[4;33m"
# define UBLU "\x1B[4;34m"
# define UMAG "\x1B[4;35m"
# define UCYN "\x1B[4;36m"
# define UWHT "\x1B[4;37m"
# define RESET "\x1B[0m"

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	char			**connections;
	bool			start;
	bool			end;
	struct s_room	*next;

}					t_room;

typedef struct		s_num_list
{
	size_t				i;
	struct s_num_list	*next;
}					t_num_list;

typedef struct		s_num_path
{
	struct s_num_path	*next;
	t_num_list			*path;
}					t_num_path;

typedef struct		s_str_list
{
	char				*name;
	struct s_str_list	*next;
}					t_str_list;

typedef struct		s_str_path
{
	struct s_str_path	*next;
	t_str_list			*path;
}					t_str_path;

typedef struct		s_leaves_stack
{
	struct s_leaf			*leaf;
	struct s_leaves_stack	*next;
}					t_leaves_stack;

typedef struct		s_leaf
{
	size_t			room_num;
	t_leaves_stack	*children;
	struct s_leaf	*parent;
}					t_leaf;

typedef struct		s_graph
{
	int				x;
	int				y;
	char			*name;
	t_num_list		*connections;
	bool			temp_visited;
	bool			visited;
}					t_graph;

typedef struct		s_ant
{
	int				num;
	t_str_list		*path;
	struct s_ant	*next;
}					t_ant;

#endif
