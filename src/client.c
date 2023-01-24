/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:55:52 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/25 01:09:07 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void send_to_server(pid_t pid, unsigned chr)
{
	int	i;

	i = 0;
	while (i < BYTE)
	{

		if (chr & 1)
		{
			kill(pid, SIGUSR2);
			usleep(50);
		}
		else
		{
			kill(pid, SIGUSR1);
			usleep(50);
		}
		chr >>= 1;
		i++;
	}
}

static int	str_to_bin(pid_t pid, char *str)
{
	unsigned char	chr;

	if (!str)
		return (1);
	while (*str)
	{
		chr = *str;
		send_to_server(pid, chr);
		str++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pid_t	pid_no;

	pid_no = 0;
	if (argc != 3)
	{
		ft_printf("Error\n: Fewer or Larger parameters");
		return (1);
	}
	pid_no = ft_atoi(argv[1]);
	if (str_to_bin(pid_no, argv[2]))
		ft_printf("Invalid message\n");
	return (0);
}
