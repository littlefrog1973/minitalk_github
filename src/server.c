/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:05:34 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/25 14:02:28 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/*
static void	sig_to_client(int *bits_count, int *pid_digit_count, char *pid_str, unsigned char *chr, int *write_pid)
{
	if (*bits_count == BYTE && *pid_digit_count <= PID_DIGIT)
	{
		pid_str[*pid_digit_count] = *chr;
		if (*pid_digit_count < PID_DIGIT)
		{
			*bits_count = 0;
			*chr = 0;
		}
		if (*pid_digit_count == PID_DIGIT)
		{
			write(1, pid_str, PID_DIGIT);
			write(1, "\n", 1);
			*write_pid = 1;
		}
		*pid_digit_count += 1;
	}

}
*/
static void	bit_to_char(int signum)
{
	static int				bits_count;
	static unsigned char	chr;
	static char				pid_str[PID_DIGIT + 1];
	static int				pid_digit_count;
	static int				write_pid;

	++bits_count;
	if (signum == SIGUSR1 && bits_count != BYTE)
		chr >>= 1;
	if (signum == SIGUSR2)
	{
		chr |= 0b10000000;
		if (bits_count != BYTE)
			chr >>= 1;
	}
//	sig_to_client(&bits_count, &pid_digit_count, pid_str, &chr, &write_pid);
	if (bits_count == BYTE && pid_digit_count <= PID_DIGIT)
	{
		pid_str[pid_digit_count] = chr;
		if (pid_digit_count < PID_DIGIT)
		{
			bits_count = 0;
			chr = 0;
		}
		if (pid_digit_count == PID_DIGIT)
		{
			write(1, &pid_str, PID_DIGIT);
			write(1, "\n", 1);
//			kill(ft_atoi(pid_str), SIGUSR1);
//			usleep(30);
//			ft_printf("ft_atoi(pid_str) = %d\n", ft_atoi(pid_str));
			write_pid = 1;
		}
		pid_digit_count += 1;
	}
	if (bits_count == 8 && write_pid)
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
