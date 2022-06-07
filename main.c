#include "include/libft.h"
#include <unistd.h>

int main(void)
{
	t_dict	*dict;
	t_dict	*new;

	dict = ft_dictnew("oui", "non");
	new =  ft_dictnew("manger", "boire");
	ft_dictadd_front(&dict, new);
	ft_dictprint(dict);
	//ft_dictclear(dict);
}
