/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:42:13 by seronen           #+#    #+#             */
/*   Updated: 2020/10/20 00:53:07 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H
# include "libft.h"

# define TABLE_SIZE 2048

# define MAX_LEN 20

typedef struct  s_hash
{
    char    **hashtable[TABLE_SIZE];
}               t_hash;

#endif