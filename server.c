/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozturk <onur_fb_5959@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:47:34 by oozturk           #+#    #+#             */
/*   Updated: 2022/06/30 14:50:48 by oozturk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	binarytodecimal(char *bits)
{
	int				base;
	unsigned char	num;
	int				i;

	num = 0;
	i = 0;
	base = 128;
	while (bits[i])
	{
		num += base * (bits[i] - '0');
		base /= 2;
		i++;
	}
	write(1, &num, 1);
}

void	ft_signal(int signal)
{
	static int	counter;
	static char	*bits;

	if (bits == NULL)
	{
		bits = ft_strdup("");
		counter = 1;
	}
	if (signal == SIGUSR1)
		bits = ft_strjoin(bits, '0');
	else
		bits = ft_strjoin(bits, '1');
	if (counter == 8)
	{
		binarytodecimal(bits);
		free(bits);
		bits = NULL;
	}
	counter++;
}

int	main(void)
{
	int		pid;
	char	*pidstr;

	pid = getpid();
	ft_putstr("PID: ");
	pidstr = ft_itoa(pid);
	ft_putstr(pidstr);
	write(1, "\n", 1);
	while (1)
	{
		signal(SIGUSR1, ft_signal);
		signal(SIGUSR2, ft_signal);
		pause();
	}
	return (0);
}
