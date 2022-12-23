# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 15:19:42 by lkrief            #+#    #+#              #
#    Updated: 2022/12/23 13:15:31 by lkrief           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

./philo $1 $2 $3 $4 $5 | tee file;
> log_file;
x=1;
while [[ "$x" -le $1 ]]
do
echo "________($x)________" >> log_file;
echo -n "showed     " >> log_file;
grep "] $x " file | wc -l >> log_file;
echo -n "took a fork" >> log_file;
grep "] $x has taken a fork" file | wc -l >> log_file;
echo -n "eating     " >> log_file;
grep "] $x is eating" file | wc -l >> log_file;
echo -n "sleeping   " >> log_file;
grep "] $x is sleeping" file | wc -l >> log_file;
echo -n "thinking   " >> log_file;
grep "] $x is thinking" file | wc -l >> log_file;
echo -n "died       " >> log_file;
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
printf "\nPhilos:      $1\nDie_timer:   $2ms\nEat_timer:   $3ms\nSleep_timer: $4ms\nMax_meals:   $5\n" >> log_file;
cat log_file;

# alias :
# tester_philos() {bash extras/tester/tester.sh $1 $2 $3 $4 $5}