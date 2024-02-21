#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <random>

using namespace std; 
const int N = 5; // Total number of threads (guests)
random_device rd; // Random device for generating random numbers
mt19937 gen(rd()); // Mersenne Twister random number generator
uniform_int_distribution<> distrib(0, 1);
vector<bool> hasBeen(N, false); // Vector to track which guests have visited
bool isAvailible = true; 
mutex mtx; // Mutex for protecting shared resources
condition_variable cv; // Condition variable for synchronization
queue<int> accessQueue; // Queue to manage the access order


void accessResource(int id) {
    unique_lock<mutex> lock(mtx);
    accessQueue.push(id);

    // Wait until it's this thread's turn
    cv.wait(lock, [id] { return !accessQueue.empty() && accessQueue.front() == id && isAvailible; });

    // Simulate accessing the resource
    isAvailible = false;
    cout << "Thread " << id << " is accessing the show room." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate visiting time
    cout << "Thread " << id << " has finished accessing the show room." << endl;
    hasBeen[id-1] = true;

    isAvailible = true;
    accessQueue.pop(); // Remove the thread from the queue

    // Unlock before notifying to avoid waking up a thread that will immediately block again
    lock.unlock();
    cv.notify_one(); // Notify the next thread in line
}

bool allHaveVisited() { // Function to check if all guests have visited
    for (bool visited : hasBeen) {
        if (!visited) return false;
    }
    return true;
}
int main() 
{
    
    // Create and start threads
    while(!allHaveVisited())
    {
        vector<thread> threads;
        for (int i = 0; i < N; ++i) {
            if(distrib(gen) == 1)
            {
                threads.push_back(thread(accessResource, i + 1));
                cout << "Guest " << i << " has decided to que." << endl;
            }
            else
            {
                cout << "Guest " << i << " has decided not to que." << endl;
            }
        }

        // Wait for all threads to finish
        for (auto& t : threads) {
            t.join();
        }
    }

    cout << "All guests have visited the showroom." << endl;
    return 0;
}
