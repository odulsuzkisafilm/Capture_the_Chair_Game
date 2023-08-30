// Created by Efe Cinar on 17/05/2023.

#include <iostream>
#include <mutex>
#include <thread>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "IntQueue.h"
using namespace std;

mutex myMutex;

void captureChair(IntQueue & que, int playerID, struct tm *ptm){
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));

    myMutex.lock();

    // updating the time that is going to be displayed for each thread/player
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    ptm = localtime(&tt);

    if(!que.isFull()){ // adding the players to chair queue except the last one arrived
        que.enqueue(playerID);
        cout << "Player " << playerID << " captured a chair at " << put_time(ptm,"%X") << "." << endl;
    }else{
        cout << "Player " << playerID << " couldn't captured a chair." << endl;
    }
    myMutex.unlock();
}

int main() {
    int number_of_players;
    cout << "Welcome to Musical Chairs game!" << endl;
    cout << "Enter the number of players in the game:" << endl;
    cin >> number_of_players;
    cout << "Game Start!" << endl << endl;

    // a queue that stores the remaining players id num
    IntQueue remainingPlayers(number_of_players);
    // initialized with nums in the range [0, number_of_players-1]
    // will be updated in the loop with the players in the each new chairQueue
    for (int i = 0; i < number_of_players; i++) {
        remainingPlayers.enqueue(i);
    }

    // in each loop it'll become the las element in the queue (when there is 1 element,
    // it'll become that one)
    int winnerID;

    while(number_of_players != 1) {
        // queue that stores the number of chairs in each rounds (1 less than the player amount in that round)
        IntQueue chairQueue(number_of_players - 1);

        thread players[number_of_players];
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm *ptm = localtime(&tt);
        cout << "Time is now " << put_time(ptm, "%X") << endl;

        ptm->tm_sec += 2; // since this increment is updated and normalized inside the object, no check is needed
        /* if a check was needed, it could be applied like this:
        if (tm_sec >= 58){
            ptm->tm_min++;
            ptm->tm_sec = (ptm->tm_sec + 2) % 60;
        }else{
            ptm->tm_sec += 2;
        }*/

        // starting every player's thread
        for (int i = 0; i < number_of_players; i++) {
            int Id;
            remainingPlayers.dequeue(Id);
            players[i] = (thread(&captureChair, ref(chairQueue), Id, ptm));
        }
        for (int i = 0; i < number_of_players; i++) {
            players[i].join();
        }

        cout << "Remaining players are as follows: ";
        int temp;
        remainingPlayers = chairQueue;

        while (!chairQueue.isEmpty()) {
            chairQueue.dequeue(temp);
            cout << temp << " ";
        }
        cout << endl << endl;

        number_of_players--;

        winnerID=temp; // updating until the last remaining element to be the winner
    }

    cout << "Game over!" << endl << "Winner is Player " << winnerID << "!" << endl;

    return 0;
}
