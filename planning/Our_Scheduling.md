# Our Multi-Level Feedback Queue Scheduling Plan:
Our scheduler implements a Multi-Level Feedback Queue that uses a maintenance cycle to prevent starvation.
### Our queues - A Visual Guide
![alt text](MLPQ Graph.png?raw=true)

## Guide to a Scheduling Cycle

#### Thread Statuses:
  * **P_RUN** - The thread ran for the full allocated time
    * *Upon Choosing:*
      * N/A
    * *Upon Putting Away:*
      * Place into one *Q#* lower than from where it was picked. (If from *Q3*, place back into *Q3*)<br><br>

  * **P_YIELD** - The thread stopped early due to a yield()
    * *Upon Choosing:*
      * **SHOULD NEVER HAPPEN.**
    * *Upon Putting Away:*
      * Change status to **P_RUN**
      * Place into the *same* *Q#* from where it was picked.<br><br>

  * **P_WAIT_M** - The thread is waiting on a mutex
    * *Upon Choosing:*
      * Check to see if the **mutex** it is waiting on is unlocked
      * If it is unlocked, run this thread. Otherwise, remove it from this *Q#* and place into one *Q#* lower. (If from *Q3*, place back into *Q3*)
      * Proceed to check the next thing in the current *Q#*.
    * *Upon Putting Away:*
      * Place into the **same** *Q#* from where it was picked.<br><br>

  * **P_WAIT_T** - The thread is waiting on another thread

    * *Upon Choosing:*
      * Check to see if the **thread** it is waiting on is in the *completed* linked list
      * If it is, run this thread. Otherwise, remove it from this *Q#* and place into one *Q#* lower. (If from *Q3*, place back into *Q3*)
      * Proceed to check the next thing in the current *Q#*.
    * *Upon Putting Away:*
      * Place into the **same** *Q#* from where it was picked.<br><br>

  * **P_EXIT** - The thread has finished and run exit()
    * *Upon Choosing:*
      * **SHOULD NEVER HAPPEN.**
    * *Upon Putting Away:*
     * Instead of placing back into the MLFQ, place into a separate linked list "*completed*" where the thread wait()ing on it can find it, take its return value, and delete it.

#### Dealing with the Previously Running Process:

  1. Check the *Q#* and *status* associated with the process.

  2. Following the guide above, decide where the process will go and what you need to do to it.

#### Choosing a new Process:

  1. Check the top of *Q1* for a process. If none exist, then check *Q2*, then *Q3*. When a process is found, pop it, store the *Q#* it was found in and we can call it **nextProc**.

  2. If **nextProc** was popped from *Q1*, then we will run it for **??** ms. If **nextProc** was popped from *Q2*, then we will run it for **??** ms. If **nextProc** was popped from *Q3*, then we will run it for **??** ms.

*Note:* The process will be swapped in after Maintenance has been run.

#### Performing Maintenance:

Once the scheduler has decided on a process to run:

  1. Pop the top process of *Q3*. If *Q3* has none, then pop the top process of *Q2*. If *Q2* has none then skip the remaining steps.
  2. Call this popped process **mProc**.
  2. Take **mProc** and place it into *Q1*.

This will ensure that the big processes stuck in the lowest queue do not get starved by many smaller ones in the higher *Q#*s.
