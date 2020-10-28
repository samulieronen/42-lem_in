/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junkbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:52:28 by seronen           #+#    #+#             */
/*   Updated: 2020/09/06 15:52:37 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	while (node->rooms)
	{
		printf("Found room %s\n", node->rooms->name);
		if (node->rooms->info)
			printf("%s\n", node->rooms->info);
		while (node->rooms->pipes)
		{
			printf("Pipe to '%s'\n", node->rooms->pipes->where);
			node->rooms->pipes = node->rooms->pipes->next;
		}
		printf("\n");
		node->rooms = node->rooms->next;
	}
	ft_printf("\n\n");
    