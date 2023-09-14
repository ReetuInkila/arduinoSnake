#include "linkedList.h"
#include "Pair.h"


class Snake {
public:
    Snake() : score(0) {}

    void start(int x, int y){
        // TODO: Make sure that coordinates are empty
        coordinates.insert(Pair<int, int> (x, y));
        addPoint();
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

    // Aseta pistemäärä
    void setScore(int newScore) {
        score =+ newScore;
    }

    Pair<int, int> getPoint(){
        return point;
    }

    // Palauta pistemäärä
    int getScore() const {
        return score;
    }

    // Siirrä käärmettä eli poista piste lopusta ja lisää alkuun
    Pair<int, int> moveSnake(int newX, int newY) {
      //if (!coordinates.empty()) { 
      //TODO: implement is empty method and check
      if (newX == point.first && newY == point.second){
        coordinates.insert(Pair<int, int>(newX, newY));
        addPoint();
        return Pair<int, int>(-1,-1);
      }else {
        coordinates.insert(Pair<int, int>(newX, newY));
        Pair<int, int> last = coordinates.getLast();
        coordinates.removeLast();
        return last;
      }
    }

    // Function to get the snake's body as a list of coordinates
    LinkedList<Pair<int, int>> getSnake() {
      return coordinates;
    }

private:
    LinkedList<Pair<int, int>> coordinates; // Kordinaatit
    Pair<int, int> point; // pisteen kordinaatit
    int score; // Pistemäärä

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
