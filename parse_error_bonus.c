/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:36 by snpark            #+#    #+#             */
/*   Updated: 2021/07/24 15:40:42 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_atoi_err(const char *string)
{
	int	i;

	i = 0;
	while (ft_isspace(string[i]))
		i++;
	if (ft_ispm(string[i]))
		i++;
	while (ft_isdigit(string[i]))
		i++;
	if (string[i])
		return (0);
	return (1);
}

float	ft_atof_err(char *string)
{
	while (ft_isspace(*string))
		string++;
	if (ft_ispm(*string))
		string++;
	while (ft_isdigit(*string))
		string++;
	if (*string == '.')
		string++;
	while (ft_isdigit(*string))
		string++;
	if (*string)
		return (0);
	return (1);
}

int	parse_error(int arg_n, char **arg_s)
{
	if (arg_n >= 3 && !ft_atof_err(arg_s[2]))
		return (0);
	if (arg_n >= 4 && !ft_atof_err(arg_s[3]))
		return (0);
	if (arg_n >= 5 && !ft_atoi_err(arg_s[4]))
		return (0);
	if (arg_n >= 6 && !ft_atof_err(arg_s[5]))
		return (0);
	if (arg_n >= 7 && !ft_atof_err(arg_s[7]))
		return (0);
	return (1);
}
