/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:33:17 by zbentale          #+#    #+#             */
/*   Updated: 2023/03/21 11:35:18 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void envv(envp *str)
{
    envp *st;
    st = str;
    while(st)
    {
        if(st->option == 1)
        printf("%s\n",st->str);
        st = st->next;
    }  
    //print the last lint in the original env
    printf("_=/usr/bin/env\n");
}