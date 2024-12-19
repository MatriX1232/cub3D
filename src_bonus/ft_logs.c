/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:16:38 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/22 18:04:27 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_cprint(char *color, char *str)
{
	(void)!write(1, color, ft_strlen(color));
	(void)!write(1, str, ft_strlen(str));
	(void)!write(1, END, ft_strlen(END));
}

void	ft_log(char *str, char *str_optional, int level)
{
	if (level == 0)
		printf("[ %sSUCCESS%s ] %s", GREEN, END, str);
	else if (level == 1)
		printf("[ %sINFO%s ]    %s", CYAN, END, str);
	else if (level == 2)
		printf("[ %sWARNING%s ] %s", YELLOW, END, str);
	else if (level == 3)
		printf("[ %sERROR%s ]   %s", RED, END, str);
	if (str_optional != NULL)
		printf(" | %s\n", str_optional);
	else
		printf("\n");
}

void	ft_log_sub(char *str, char *str_optional, int level, int sub_level)
{
	if (sub_level == 1)
		printf("  |--->  ");
	else if (sub_level == 2)
		printf("    |--->  ");
	if (level == 0)
		printf("[ %sSUCCESS%s ] %s", GREEN, END, str);
	else if (level == 1)
		printf("[ %sINFO%s ]    %s", CYAN, END, str);
	else if (level == 2)
		printf("[ %sWARNING%s ] %s", YELLOW, END, str);
	else if (level == 3)
		printf("[ %sERROR%s ]   %s", RED, END, str);
	if (str_optional != NULL)
		printf(" | %s\n", str_optional);
	else
		printf("\n");
}
