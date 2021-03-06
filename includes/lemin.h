/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:33:43 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 22:43:41 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# include <limits.h>

typedef struct		s_room
{
	char			*name;
	int				unique_idx;
	int				parent_idx;
}					t_room;

typedef	struct		s_anthill
{
	int				num_ants;
	int				start_idx;
	int				end_idx;
	int				num_rooms;
	t_room			**rooms;
	t_list			**adj_list;
	t_list			**ant_routes;
	int				is_valid;
}					t_anthill;

typedef struct		s_route
{
	int				*path;
	int				cost;
	int				num_ants;
}					t_route;

typedef struct		s_search
{
	int				*pred;
	int				*dist;
}					t_search;

typedef struct		s_ant
{
	t_route			*route;
	int				wait;
	int				turns_taken;
	int				current_turn;
}					t_ant;

typedef struct		s_set
{
	t_route			**routes;
	int				size;
	struct s_set	*next;
}					t_set;

t_list				*read_input(void);

int					is_antcount(char *line);
int					is_roomline(char *line);
int					is_tunnelline(char *line);
int					lookup_room_index(char *name, t_anthill *anthill);

int					validate_input_lines(t_list *input_lines);

int					build_anthill(t_list *input_lines, t_anthill *anthill);
void				build_roomlist(t_list *input_lines, t_anthill *anthill);
void				build_adjlist(t_list *input_lines, t_anthill *anthill);

void				delete_roomlist(t_anthill *anthill);
void				delete_adjlist(t_anthill *anthill);
void				delete_inputlines(t_list **input_lines);

int					bfs(t_anthill *ah, t_search *info, t_route *ignore);
int					discover_routes(t_anthill *anthill, t_list *input_lines);
void				delete_key_from_adjlist(t_anthill *anthill,
											int key_from, int key_to);
t_ant				*choose_routes(t_anthill *anthill, t_route **routes,
									int num_routes);
void				choose_best_route_combo(t_anthill *anthill, t_set *set,
											t_list *input_lines);
void				print_turns(t_anthill *anthill, t_ant *ants);
t_route				*create_route(int path_cost);
void				free_routes(t_route **arr, int size);
void				free_set(t_set *set);
t_set				*create_route_set(t_route **routes, int size);
#endif
