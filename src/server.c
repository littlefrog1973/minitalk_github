/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:05:34 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/24 14:26:19 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void bit_to_char(int signum)
{
	static int bits_count;
	static unsigned char chr;

	bits_count++;
	if (signum == SIGUSR1 && bits_count != 8)
	{
//		write(1, "SIGUSR1\n", 8);
		chr >>= 1;
	}
	if (signum == SIGUSR2)
	{
//		write(1, "SIGUSR2\n", 8);
		chr |= 128;
		if (bits_count != 8)
			chr >>= 1;
	}
	if (bits_count == 8)
	{
		write(1, &chr, 1);
		bits_count = 0;
		chr = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID = %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, bit_to_char);
		signal(SIGUSR2, bit_to_char);
		pause();
	}
	return (0);
}


/*
int main()
{
	pid_t	pid;
	struct	sigaction sa;

	sa.sa_handler = bit_to_char;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
//	write(1,"\340\270\201\340\270\202\n",7);
	ft_printf("Server Pid = %d\n", pid);
	while (1)
		pause();
	return 0;
}
*/
