/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:05:34 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/27 08:27:32 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	bit_to_char(int signum, siginfo_t *info, void *context)
{
	static int				bits_count;
	static unsigned char	chr = 0;
	static unsigned char	bit_shift[] = {1, 1, 1, 1, 1, 1, 1};

	(void) context;
	(void) info;
	bits_count++;
	if (signum == SIGUSR2)
		chr |= 128;
	chr >>= bit_shift[bits_count - 1];
	if (bits_count == 8)
	{
		write(1, &chr, 1);
		bits_count = 0;
		chr = 0;
	}
}
/*
void	bit_to_char(int signum)
{
	static int				bits_count = 0;
	static unsigned char	chr = 0;

	bits_count++;
	if (signum == SIGUSR1 && bits_count != 8)
		chr >>= 1;
	if (signum == SIGUSR2)
	{
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
*/

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;

	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	pid = getpid();
	ft_putstr_fd("Server PID = ", pid);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = bit_to_char;
	s_sigaction.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}

/*
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
*/
