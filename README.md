
<h1>The Dining Philosophers problem </h1>
Philosophers is a 42 school project that illustrates synchronization issues and techniques for resolving them in concurrent algorithm design. Similar to the one that was formulated by Edsger Dijkstra in 1965 as a student exam exercise.
<br><br>


![alt text](https://github.com/cyanidev/Philosophers/blob/main/Philo%20img/Philos.webp)


<h2>General instructions</h2>
<ul>
<li>Global variables are forbidden!<br></li>
<li>Your program(s) must accept the following arguments:</li>
  </ul>
   number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]<br><br>
  ◦ <b><code>number_of_philosophers (int between 1 and 200): </code></b> is the number of philosophers, but also the number of forks.<br>
  ◦ <b><code>time_to_die (in milliseconds):</b></code> if a philosopher doesn't start eating within time_to_die milliseconds from the start of their last meal or from the beginning of the simulation, they will die.<br>
  ◦ <b><code>time_to_eat (in milliseconds):</b></code> is the time a philosopher has to eat. During this time, they will have the forks occupied.<br>
  ◦ <b><code>time_to_sleep (in milliseconds):</b></code> is the time a philosopher has to sleep.<br>
  ◦ <b><code>number_of_times_each_philosopher_must_eat (optional argument):</b></code> if all philosophers eat at least number_of_times_each_philosopher_must_eat times, the simulation will stop. If not specified, the simulation will stop with the death of a philosopher.<br>
  </ol>
<ul><br>
<li>Each philosopher will be assigned a number from 1 to number_of_philosophers.<br></li>
<li>Philosopher number 1 will sit next to philosopher number number_of_philosophers. Any other philosopher number N will sit between philosopher number N - 1 and philosopher number N + 1.<br></li>
</ul><br>

<h2>The logs of the program:</h2>

Any change in the state of a philosopher follow this format:

◦ timestamp_in_ms X has taken a fork<br>
◦ timestamp_in_ms X is eating<br>
◦ timestamp_in_ms X is sleeping<br>
◦ timestamp_in_ms X is thinking<br>
◦ timestamp_in_ms X died<br>

<h2>To run the program:</h2>
Compile the program with: 

```
make
```

Run the program with the following arguments:<br>

```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```
example(no philo dies):
```
./philo 4 410 200 200
```
example(one philo dies):
```
./philo 4 310 200 100
```
example(with opcional parameter):
```
./philo 5 800 200 200 7
```

If the inputs are correct, the software will document each philosopher's actions until one passes away or until they've all reached the specified number_of_times_each_philo_must_eat, if that parameter is given.


