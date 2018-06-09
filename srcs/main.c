/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:42:46 by enennige          #+#    #+#             */
/*   Updated: 2018/06/08 16:17:41 by jpollore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_roomlist(t_anthill anthill)
{
	int i;
	i = 0;
	while (i < anthill.num_rooms)
	{
		printf("[%d] room: %s\n", i, anthill.rooms[i]->name);
		i++;
	}
}

void	print_nodelist(t_anthill anthill)
{
	int i;
	t_list *node;
	i = 0;
	while (i < anthill.num_rooms)
	{
		node = anthill.adj_list[i];
		printf("parent: [%d]\n", *(int *)(node->content));
		while (node->next)
		{
			node = node->next;
			printf("	child: [%d]\n", *(int *)(node->content));
		}
		i++;
	}
}

int main(void)
{
	t_list		*input_lines;
	t_anthill	anthill;

	input_lines = read_input();
	if (validate_input_lines(input_lines) != -1)
	{
		if (build_anthill(input_lines, &anthill) != -1)
		{
			print_roomlist(anthill);
			print_nodelist(anthill);
			ft_putstr("FINDING PATH\n");
			if (!(solve(&anthill)))
				ft_putstr("ERROR\n");
			delete_inputlines(&input_lines);
			delete_roomlist(&anthill);
			delete_adjlist(&anthill);
			return (0);
		}
	}
	ft_putstr("ERROR\n");
	return (-1);
}
