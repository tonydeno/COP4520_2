# COP4520_Assignment_2
# To Compile
* To compile part1 do: g++ part1.cpp
* To run part1 do ./a.out
* To compile part2 do: g++ part2.cpp
* To run part2 do ./a.out
# Statements/Proof of Correctness 
*My approach for part 1 is as follows: 
  -Designate 1 guest as the counter and the rest as non-counters
    - Counter Role
      -If there is a cupcake eat it and iterate the count up by 1 otherwise do nothing
    -Non-Counter
      -Can only place a cupcake once
      -If they have not placed a cupcake before and there is no cupcake present then place one otherwise do nothing. 
      This ensures that the counter only eats N cupcakes for N guests and will properly iterate the count.
    This approach also means the order of which guests are selected does not matter since they will only place a cupcake once. Therefore
    it is plausible for the minotaur to re-select as many guests as it wants. 
    I implemented this in my program by first running N threads and declaring N structs to keep track of whether or not a counter has been.
    Each thread is constantly checking whether it is the currentIndex(which is randomly selected to simulate the minotaur picking a guest)
    If it is it implements its designated function based on its role as a counter or non-counter.
    To confirm if the program is only stopping after all non-counters have placed a cupcake once I printed out all of the has_placed booleans during
    the debugging process to see if they where marked true and they where. This can easily be replicated by appending the following code to the end of
    part1.cpp: 
    for(int i = 0; i < guests.length; i++)
    {
      cout << guests[i].has_placed << " ";
    }
    for 5 guests the output should be: 1 1 1 1 1 
    Note that the counter autmatically markes has_placed to true. 

*My approach for part 2 is as follows:
-Variables and structures are initialized, including a mutex (mtx), a condition variable (cv), a boolean flag (isAvailable), and a queue (accessQueue) to manage access order.
-For each round (while not all guests have visited), each guest (thread) decides randomly whether to queue for the showroom visit.
-Guests that decide to queue are added to accessQueue, ensuring their visit follows a first-come, first-served order.
-Each thread waits for its turn based on its position in the queue and the availability of the showroom (isAvailable). When a thread gains access, isAvailable is set to false, simulating the showroom being occupied.
Each thread (guest) simulates a visit to the showroom, marked by a sleep duration, then marks itself as having visited (hasBeen) and sets isAvailable back to true.
-After completing the visit, the thread notifies the next thread in line that it may now attempt to access the showroom.
-The process repeats until all guests have visited the showroom.

Part 2 is correct for the following reasons:
-Mutual Exclusion: Ensured by the mutex (mtx) and the isAvailable flag, makes it so that only one guest can access the showroom at any given time.
-No Deadlock/Livelock: The condition variable (cv) is used with the queue to manage access order, ensuring guests proceed in a FIFO manner without deadlock or livelock conditions.
-Fairness: The FIFO queue ensures that guests access the showroom in the order they decide to queue.
    
  
# Efficiency 

-Part2
The use of condition variables minimizes busy waiting, making the synchronization mechanism efficient.
However, continuously starting threads in a loop without considering whether guests have already visited can be inefficient.However in order
to make the simulation realistic(able to simulate the guests randomly deciding to que) 
# Experimental Evaluation
