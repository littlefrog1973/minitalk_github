/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:55:52 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/27 08:29:08 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile char	*g_argv[2];

static void	send_to_server(pid_t pid, unsigned char chr)
{
	int	i;

	i = 0;
	while (i < BYTE)
	{
		if (chr & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		if (i == 7)
			usleep(30);
		else
			usleep(100);
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
	g_argv[0] = argv[1];
	g_argv[1] = argv[2];
	pid_no = ft_atoi(argv[1]);
	if (str_to_bin(pid_no, argv[2]))
		ft_printf("Invalid message\n");
	return (0);
}

/*
int	main(int argc, char *argv[])
{
	pid_t	pid_no;
	static unsigned char	bit_mask[] = {1, 1, 1, 1, 1, 1, 1};

	pid_no = 0;
	if (argc != 3)
	{
		ft_printf("Error\n: Fewer or Larger parameters");
		return (1);
	}
	pid_no = ft_atoi(argv[1]);
	printf("strlen of bit_mask = %lu\n", ft_strlen((char *) bit_mask));
	if (str_to_bin(pid_no, argv[2]))
		ft_printf("Invalid message\n");
	return (0);
}
*/
