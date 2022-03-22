/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:05:20 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/27 15:02:28 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

// standard library
# include <stdlib.h>

// structure for doubly-linked list elements

typedef struct s_dlist_elem
{
	void				*data;
	struct s_dlist_elem	*next;
	struct s_dlist_elem	*prev;
}						t_elem;

// structure for doubly-linked list

typedef struct s_dlist
{
	int		size;
	int		(*match)(const void *key1, const void *key2);
	void	(*destroy)(void *data);
	t_elem	*head;
	t_elem	*tail;
}			t_dlist;

// functions to control the doubly-linked list
void	ft_dlist_init(t_dlist *list, void (*destroy)(void *data));
void	ft_dlist_destroy(t_dlist *list);
int		ft_dlist_ins_next(t_dlist *list, t_elem *element, const void *data);
int		ft_dlist_ins_prev(t_dlist *list, t_elem *element, const void *data);
int		ft_dlist_remove(t_dlist *list, t_elem *element, void **data);

// function of control
int		ft_dlist_size(t_dlist *list);
t_elem	*ft_dlist_head(t_dlist *list);
t_elem	*ft_dlist_tail(t_dlist *list);

int		ft_dlist_is_head(t_elem *element);
int		ft_dlist_is_tail(t_elem *element);

void	*ft_dlist_data(t_elem *element);
t_elem	*ft_dlist_next(t_elem *element);
t_elem	*ft_dlist_prev(t_elem *element);

/* The NORM does NOT ALLOW Define with Arguments...

#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)

#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

*/
#endif
