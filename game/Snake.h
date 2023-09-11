#include <ArduinoSTL.h>
#include <utility>


class Snake {
public:
    Snake() : score(0) {}

    void start(int x, int y){
        // TODO: Make sure that coordinates are empty
        coordinates.insert(coordinates.begin(), std::make_pair(x, y));
        addPoint();
    }

    // Lisää uuden kerättävän pisteen
    void addPoint(int x, int y) {
        int x, y;
        do {
            x = random(26);
            y = random(26);
        } while (isCoordinateInSnake(x, y));

        point = std::make_pair(x, y);
    }

    // Aseta pistemäärä
    void setScore(int newScore) {
        score =+ newScore;
    }

    pair<int, int> getPoint(){
        return point;
    }

    // Palauta pistemäärä
    int getScore() const {
        return score;
    }

    // Siirrä käärmettä eli poista piste lopusta ja lisää alkuun
    void moveSnake(int newX, int newY) {
        if (!coordinates.empty()) {
            coordinates.insert(coordinates.begin(), std::make_pair(newX, newY));
            coordinates.pop_back();
        }
    }

private:
    std::vector<std::pair<int, int>> coordinates; // Kordinaatit
    std::pair<int, int> point; // pisteen kordinaatit
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
