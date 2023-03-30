<h1 align="center">
	📖 Philosophers
</h1>

<p align="center">
	<b><i>Basics of process threading, and how work on the same memory space.</i></b><br>
</p>

---

Philosophers is a 42-school project (https://www.42.fr/42-network/) which serves as an introduction to multithreading's basics.  

## Introduction

The dining philosophers problem is a classic example in computer science that illustrates the challenges of resource allocation and synchronization in a distributed system, using the metaphor of philosophers sharing chopsticks at a circular table. It was originally formulated in *1965 by Edsger Dijkstra*.

[More informations](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

*Tips and good methodology to do the project at the bottom of the readme*

## Installation 🖥

`make` inside a __*philo*__ folder

__usage :__

`./philo {nb_philos} {die_tm} {eat_tm} {sleep_tm} (max_eat)`  
`{.}` inputs are in ms and capped to 60,000 ms  
`max_eat` argument is not required

__example :__

`./philo 4 500 200 200`

> **Warning**: I had to comply to the subject's constraints so the code is not optimized.  
> These constraints were numerous. Here are a few:  
>> • This project had to be coded in C, complying with the 42-school norm.
> • Any leak, crash, undefined behavior or norm error means 0 to the project.  
> • The only authorized mutex-related functions were `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`.  
> • The philosophers must never be starving.  
> • Philosophers don’t speak with each other.  
> • Philosophers don’t know when another philosopher is about to die. 
> • The simulation stops when a philosopher dies.  
> • The status printed should not be scrambled or intertwined with another philosopher’s status.  
> • You can’t have more than 10 ms between the death of a philosopher and when it will print its death.  

> **Warning**: Don't copy/paste code you don't understand: it's bad for you, and for the school.
