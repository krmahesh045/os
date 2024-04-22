#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

#define NUM_READERS 2
#define NUM_WRITERS 2
mutex mtx;
condition_variable cond_reader, cond_writer;
int readers_count = 0;
int writers_count = 0;
int resource = 0;
bool synchronized_flag = true;

void readerFunction(int reader_id)
{
    if (synchronized_flag)
    {
        unique_lock<mutex> lock(mtx);
        while (writers_count > 0)
        {
            cout << "Reader " << reader_id << " is waiting because a writer is writing" << endl;
            cond_reader.wait(lock);
        }
        readers_count++;
        lock.unlock();
        cout << "Reader " << reader_id << " reading shared resource" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        lock.lock();
        readers_count--;
        if (readers_count == 0)
        {
            cond_writer.notify_one();
        }
        lock.unlock();
    }
    else
    {
        cout << "Reader " << reader_id << " reads resource: " << resource << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Reader " << reader_id << " completed with reading, CS is free" << endl;
}
void writerFunction(int writer_id)
{
    if (synchronized_flag)
    {
        unique_lock<mutex> lock(mtx);
        writers_count++;
        while (readers_count > 0 || writers_count > 1)
        {
            cout << "Writer " << writer_id << " wants to write but not allowed" << endl;
            cond_writer.wait(lock);
        }
        lock.unlock();
        resource = writer_id;
        cout << "Writer " << writer_id << " writing shared resource" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        lock.lock();
        writers_count--;
        cond_writer.notify_one();
        cond_reader.notify_all();
        lock.unlock();
    }
    else
    {
        resource = writer_id;
        cout << "Writer " << writer_id << " writes resource: " << resource << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Writer " << writer_id << " completed with writing, CS is free" << endl;
}
int main()
{
    thread readers[NUM_READERS];
    thread writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize reader and writer IDs
    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        writer_ids[i] = i + 1;
    }

    // Set the random seed based on current time
    srand(time(nullptr));

    // Case 1: Reader-Reader (RR) case with synchronization
    synchronized_flag = true;
    cout << "Reader-Reader (RR) case with synchronization:" << endl;
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i] = thread(readerFunction, reader_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i].join();
    }

    // Case 2: Reader-Writer (RW) case with synchronization
    synchronized_flag = true;
    cout << "\nReader-Writer (RW) case with synchronization:" << endl;
    readers[0] = thread(readerFunction, reader_ids[0]);
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0].join();
    writers[0].join();

    // Case 3: Writer-Writer (WW) case with synchronization
    synchronized_flag = true;
    cout << "\nWriter-Writer (WW) case with synchronization:" << endl;
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i] = thread(writerFunction, writer_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i].join();
    }

    // Case 4: Writer-Reader (WR) case with synchronization
    synchronized_flag = true;
    cout << "\nWriter-Reader (WR) case with synchronization:" << endl;
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0] = thread(readerFunction, reader_ids[0]);
    readers[0].join();
    writers[0].join();

    // Case 5: Reader-Reader (RR) case without synchronization
    synchronized_flag = false;
    cout << "\nReader-Reader (RR) case without synchronization:" << endl;
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i] = thread(readerFunction, reader_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i].join();
    }

    // Case 6: Reader-Writer (RW) case without synchronization
    synchronized_flag = false;
    cout << "\nReader-Writer (RW) case without synchronization:" << endl;
    readers[0] = thread(readerFunction, reader_ids[0]);
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0].join();
    writers[0].join();

    // Case 7: Writer-Writer (WW) case without synchronization
    synchronized_flag = false;
    cout << "\nWriter-Writer (WW) case without synchronization:" << endl;
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i] = thread(writerFunction, writer_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i].join();
    }

    // Case 8: Writer-Reader (WR) case without synchronization
    synchronized_flag = false;
    cout << "\nWriter-Reader (WR) case without synchronization:" << endl;
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0] = thread(readerFunction, reader_ids[0]);
    readers[0].join();
    writers[0].join();

    return 0;
}

