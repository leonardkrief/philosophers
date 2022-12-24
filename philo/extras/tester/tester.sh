# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 15:19:42 by lkrief            #+#    #+#              #
#    Updated: 2022/12/23 22:56:24 by lkrief           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# if [[ $1 -eq "log" ]]
# then
# 	cat file | grep "] $2 ";
# 	exit;
# else
	./philo $1 $2 $3 $4 $5 | tee file;
	> log_file;
# fi

s="";
# if [[ $(uname | grep Linux) ]]
# then
# 	s="   ";
# fi

x=1;
while [[ "$x" -le $1 ]]
do
echo "________($x)________" >> log_file;
printf "showed     $s" >> log_file;
grep "] $x " file | wc -l >> log_file;
printf "took a fork$s" >> log_file;
grep "] $x has taken a fork" file | wc -l >> log_file;
printf "eating     $s" >> log_file;
grep "] $x is eating" file | wc -l >> log_file;
printf "sleeping   $s" >> log_file;
grep "] $x is sleeping" file | wc -l >> log_file;
printf "thinking   $s" >> log_file;
grep "] $x is thinking" file | wc -l >> log_file;
printf "died       $s" >> log_file;
grep "] $x died" file | wc -l >> log_file;
x=$((x+1))
done
printf "\n" >> log_file;
if [[ $(grep "died" file | wc -l) -eq "0" ]]
then
	echo "No one died" >> log_file;
else
	grep "died" file | awk '{printf $2 " died\n"}' >> log_file;
fi
printf "\nPhilos:       $1\nDie_timer:    $2ms\nEat_timer:    $3ms\nSleep_timer:  $4ms\nMax_meals:    $5\n" >> log_file;
cat log_file;

# alias :
# tester_philos() {bash extras/tester/tester.sh $1 $2 $3 $4 $5}