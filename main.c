/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:46:50 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 19:46:20 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/ft/libft.h"

int main(void)
{
	t_dict	*dict;
	t_dict	*new;

	dict = ft_dictnew("oui", "non");
	new =  ft_dictnew("bienn", "boire");
	ft_dictadd_front(&dict, new, 0);
	new =  ft_dictnew("bie", "mourir");
	ft_dictadd_front(&dict, new, 0);
	new =  ft_dictnew("bien", "mal");
	ft_dictadd_front(&dict, new, 0);
	ft_dictprint(dict);
	ft_printf("%u\n\n", ft_dictsize(dict));
	ft_dictchangeval(&dict, "oui", "marre", 0);
	ft_dictprint(dict);
	ft_dictprint_keys(dict);
	ft_dictprint_values(dict);
	ft_dictclear(dict, 0);
}
