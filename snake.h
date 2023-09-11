#include <vector>
#include <utility>

class Snake {
public:
    Snake() : score(0) {}

    // Lisää uuden kerättävän pisteen
    void addPoint(int x, int y) {
        int x, y;
        do {
            x = generateRandomCoordinate();
            y = generateRandomCoordinate();
        } while (isCoordinateInSnake(x, y));

        point = std::make_pair(x, y);
    }

    // Aseta pistemäärä
    void setScore(int newScore) {
        score = newScore;
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
    
    // Arpoo satunnaisen kordinaatin kentän sisällä (0 - 25)
    int generateRandomCoordinate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 25);
        return dis(gen);
    };

    // Tarkista, onko annettu kordinaatti jo käärmeen kordinaattien joukossa
    bool isCoordinateInSnake(int x, int y) {
        for (const auto& coord : coordinates) {
            if (coord.first == x && coord.second == y) {
                return true;
            }
        }
        return false;
    }
