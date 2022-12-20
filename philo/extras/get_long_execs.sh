# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    get_long_execs.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 15:19:42 by lkrief            #+#    #+#              #
#    Updated: 2022/12/20 15:26:47 by lkrief           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARG=$"gcc -Wall -Wextra -Werror -Iinclude srcs/test.c && ./a.out"; 
echo $ARG | while[read line]
do

done