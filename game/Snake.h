#include "linkedList.h"
#include "Pair.h"


class Snake {
public:
    Snake() : score(0) {}

    void start(int x, int y){
        if(!coordinates.isEmpty()){
            coordinates.empty();
        }
        coordinates.insert(Pair<int, int> (x, y));
        addPoint();
        delay = 500;
        score = 0;
        running = true;
    }

    // Lisää uuden kerättävän pisteen
    void addPoint() {
        int x, y;
        do {
            x = random(26);
            y = random(26);
        } while (isCoordinateInSnake(x, y));
        point = Pair<int, int> (x, y);
    }

    Pair<int, int> getPoint(){
        return point;
    }

    // Palauta pistemäärä
    int getScore() const {
        return score;
    }

    int getDelay(){
        return delay;
    }

    bool getState(){
      return running;
    }

    bool chekFails(int x, int y){
      for (const auto& coord : coordinates) {
            if (coord.first == x && coord.second == y) {
                return true;
            }
        }
        return false;
    }

    // Siirrä käärmettä eli poista piste lopusta ja lisää alkuun
    Pair<int, int> moveSnake(int newX, int newY) {
        
        if (!coordinates.isEmpty()) { 
            if (newX == point.first && newY == point.second){// If point is eaten
                coordinates.insert(Pair<int, int>(newX, newY));
                addPoint();
                if (delay > 100){
                  delay = delay -5;
                }
                
                score = score + round(500/delay)*10;
                return Pair<int, int>(-1,-1);
            }else if(chekFails(newX, newY)){
                running = false;
                return Pair<int, int>(-2,-2);
            }else {
                coordinates.insert(Pair<int, int>(newX, newY));
                Pair<int, int> last = coordinates.getLast();
                coordinates.removeLast();
                score = score + round(500/delay);
                if (delay > 100){
                  delay = delay -1;
                }
                return last;
            }
        }
    }

    // Function to get the snake's body as a list of coordinates
    LinkedList<Pair<int, int>> getSnake() {
      return coordinates;
    }

private:
    bool running;
    LinkedList<Pair<int, int>> coordinates; // Kordinaatit
    Pair<int, int> point; // pisteen kordinaatit
    int score; // Pistemäärä
    int delay; //microsedonds between movements 

    // Tarkista, onko annettu kordinaatti jo käärmeen kordinaattien joukossa
    bool isCoordinateInSnake(int x, int y) {
        for (const auto& coord : coordinates) {
            if (coord.first == x && coord.second == y) {
                return true;
            }
        }
        return false;
    }
};
