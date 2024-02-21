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

Part 1 is correct for the following reasons:
Each guest is assigned a unique identifier (ID) and a specific role based on their ID, with guest 0 being the counter guest. This unique assignment prevents role confusion and ensures the counter guest's actions are distinct from others.

The cup_cake boolean flag represents the state of the cupcake (present or not). It is manipulated correctly according to the rules: the counter guest eats it (sets it to false), and a non-counter guest who hasn't placed a cupcake before will replace it (set it to true), ensuring the cupcake's presence accurately reflects the visiting actions.
Access to shared variables (cup_cake, currentIndex, count, guests) is synchronized using a mutex (mtx), ensuring atomicity in updates and preventing race conditions. This 
The loop while(count != N) in guestAction and the main thread's loop ensure the simulation continues until every guest has visited. The variable count is incremented only by the counter guest, ensuring it accurately reflects the number of unique guest visits. The simulation ends when count equals N, signifying all guests have visited at least once.Although guests are selected randomly to visit the labyrinth (currentIndex = rand() % N), the program's logic ensures that even with random selection, each guest's unique action (eating or placing the cupcake) contributes to the collective goal of informing the Minotaur that all guests have visited. The use of hasBeen and has_placed flags for each guest ensures that actions contributing to this goal are taken exactly once per guest.

Part 2 is correct for the following reasons:
-Mutual Exclusion: Ensured by the mutex (mtx) and the isAvailable flag, makes it so that only one guest can access the showroom at any given time.
-No Deadlock/Livelock: The condition variable (cv) is used with the queue to manage access order, ensuring guests proceed in a FIFO manner without deadlock or livelock conditions.
-Fairness: The FIFO queue ensures that guests access the showroom in the order they decide to queue.
    
  
# Efficiency 
-Part1
The program efficiently simulates the Minotaur's Birthday Party problem by leveraging dedicated threads for each guest, enabling concurrent decision-making and actions with minimal active waiting, thanks to the strategic use of mutexes for critical section protection and minimal overhead. It employs straightforward logic and minimal resource usage ensure fast execution and scalability, suitable for varying party sizes without exponentially increasing computational complexity. 

Runtime estimate 
Total Runtime≈(N×Sleep Duration)+Thread Overhead+Random Selection Overhead

-Part2
The use of condition variables minimizes busy waiting, making the synchronization mechanism efficient.
However, continuously starting threads in a loop without considering whether guests have already visited can be inefficient.However in order
to make the simulation realistic(able to simulate the guests randomly deciding to que) 

*TC = avg time to create and start a thread
*TJ = avg time to join a thread 
*TD = avg time to make tandom descion for each guest
*TS = Avg synchronization overhead per symbol
*TV = the simulated amt of time for each guest to vist

Runtime bestcase = N X (TX + TD) + (N/2) X (TV + TS +TJ)
Since TV is the most significant we can represent the run time as
T = N(TV) + overheads

Note that in both cases the amount of times N is random so that could drastically affect the run time of the program.

# Experimental Evaluation

