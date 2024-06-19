#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int BOARD_SIZE = 10;
const string SESSION_FILE = "session.txt";


class Board {
private:
    char playerGrid[BOARD_SIZE][BOARD_SIZE];

public:
   
    void initializeGrid() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                playerGrid[i][j] = ' ';
            }
        }
    }

   
    void placeShipsRandomly() {
        int shipSizes[] = {5, 4, 3, 3, 2}; 
        srand(time(nullptr));

        for (int size : shipSizes) {
            bool shipPlaced = false;
            while (!shipPlaced) {
                int x = rand() % BOARD_SIZE;
                int y = rand() % BOARD_SIZE;
                int orientation = rand() % 2; 

                if (canPlaceShip(x, y, size, orientation)) {
                    placeShip(x, y, size, orientation);
                    shipPlaced = true;
                }
            }
        }
    }

  
    bool canPlaceShip(int x, int y, int size, int orientation) {
        if (orientation == 0) { 
            if (x + size > BOARD_SIZE)
                return false;

            for (int i = x; i < x + size; ++i) {
                if (playerGrid[i][y] != ' ')
                    return false;
            }
        } else {
            if (y + size > BOARD_SIZE)
                return false;

            for (int j = y; j < y + size; ++j) {
                if (playerGrid[x][j] != ' ')
                    return false;
            }
        }

        return true;
    }

  
    void placeShip(int x, int y, int size, int orientation) {
        if (orientation == 0) { 
            for (int i = x; i < x + size; ++i) {
                playerGrid[i][y] = 'S';
            }
        } else { 
            for (int j = y; j < y + size; ++j) {
                playerGrid[x][j] = 'S';
            }
        }
    }

  
    void saveSessionToFile() {
        ofstream file(SESSION_FILE);
        if (file.is_open()) {
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    file << playerGrid[i][j] << " ";
                }
                file << endl;
            }
            file.close();
            cout << "Game session saved to file." << endl;
        } else {
            cerr << "Unable to open file for saving session." << endl;
        }
    }
};

int main() {
    Board game;


    game.initializeGrid();
    game.placeShipsRandomly();

    game.saveSessionToFile();

    return 0;
}
