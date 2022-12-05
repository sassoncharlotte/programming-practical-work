/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"


/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */

class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {
        std::unique_lock lk(m);
        // Waiting for a consumer to take the data in the FIFO
        while (box_size > 0) {
            cv1.wait(lk);
        }
        // Putting new data in FIFO
        basic_put( message );
        // Adding 1 to FIFO length
        box_size++;
        // Notifying that changes have happened
        cv2.notify_one();
    }
 
    int get() {
        std::unique_lock lk2(m);
        // If box is empty, waiting for a producer
        // to put data in the FIFO
        while (box_size == 0) {
            cv2.wait(lk2);
        }
        // Getting the message from FIFO
        int message{ basic_get() };
        // Setting FIFO length back to 0
        box_size = 0;
        // Notifying changes have been made
        cv1.notify_one();
        // Returning gotten message
        return message;
    }
private:
    std::mutex m;
    std::condition_variable cv1;
    std::condition_variable cv2;
    int box_size = 0;
};
 
