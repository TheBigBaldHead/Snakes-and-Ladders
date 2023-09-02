#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>
#include <Windows.h>
#include <cstdio>


using namespace std;

class Player;
class SnakesandLadders;
class Snake;
class Ladder;

class Player {
public:
    string Name;
    string Username;
    string Symbol;
    vector<int> Scores;
    bool LeftTheGame = false;
    int CurrentSlot = -1;
    Player(string name, string username, string symbol) {
        Name = name;
        Username = username;
        Symbol = symbol;
    }
    int TotalScore() {
        int sum = 0;
        for (unsigned int i = 0; i < Scores.size(); i++) {
            if (Scores[i] > 0) {
                sum += Scores[i];
            }
        }
        return sum;
    }
    bool Won() {
        for (unsigned int i = 0; i < Scores.size(); i++) {
            if (Scores[i] == 50) {
                return true;
            }
        }
        return false;
    }
    void show() {
        if (Name != "" && Username != "" && Symbol != "") {
            cout << "Player: " << Name << endl;
            cout << "Username: " << Username << endl;
            cout << "Total score: " << TotalScore() << endl;
            for (int round = 1; round <= Scores.size(); round++) {
                if (Scores[round - 1] == -1) {
                    cout << "Round " << round << ": --- " << endl;
                }
                else {
                    cout << "Round " << round << ": " << Scores[round - 1] << endl;
                }
            }
            cout << "-------------------------" << endl;
        }
    }
};

class Snake {
public:
    int Head;
    int Tail;
    Snake(int head, int tail) {
        Head = head;
        Tail = tail;
    }
};

class Ladder {
public:
    int Top;
    int Bottem;
    Ladder(int top, int bottem) {
        Top = top;
        Bottem = bottem;
    }
};

void generateSnake(int n, vector<Snake>& Snakes, vector<Ladder> Ladders) {
    int Head, Tail;
    srand(time(NULL));
    while (true) {
        Head = rand() % (n*n);
        if (Head == 0 || Head == n*n - 1) { 
            continue;
        }
        bool TakenAlready = false;
        for (unsigned int i = 0; i < Snakes.size(); i++) {
        if (Snakes[i].Head == Head || Snakes[i].Tail == Head) {
                TakenAlready = true;
            }
        }
        for (unsigned int i = 0; i < Ladders.size(); i++) {
            if (Ladders[i].Top == Head || Ladders[i].Bottem == Head) {
                TakenAlready = true;
            }
        }
        if (TakenAlready) {
            continue;
        }
        break;
    }
    while (true) {
        Tail = rand() % (n*n);
        if (Tail == 0 || Tail == n*n - 1) { 
            continue;
        }
        if (Tail >= Head) {
            continue;
        }
        bool TakenAlready = false;
        for (unsigned int i = 0; i < Snakes.size(); i++) {
        if (Snakes[i].Head == Tail || Snakes[i].Tail == Tail) {
                TakenAlready = true;
            }
        }
        for (unsigned int i = 0; i < Ladders.size(); i++) {
            if (Ladders[i].Top == Tail || Ladders[i].Bottem == Tail) {
                TakenAlready = true;
            }
        }
        if (TakenAlready) {
            continue;
        }
        break;
    }
    Snake snake = Snake(Head, Tail);
    Snakes.push_back(snake);
}

void generateLadder(int n, vector<Snake> Snakes, vector<Ladder> &Ladders) {
    int Top, Bottem;
    srand(time(NULL));
    while (true) {
        Top = rand() % (n*n);
        if (Top == 0 || Top == n*n - 1) { 
            continue;
        }
        bool TakenAlready = false;
        for (unsigned int i = 0; i < Snakes.size(); i++) {
        if (Snakes[i].Head == Top || Snakes[i].Tail == Top) {
                TakenAlready = true;
            }
        }
        for (unsigned int i = 0; i < Ladders.size(); i++) {
            if (Ladders[i].Top == Top || Ladders[i].Bottem == Top) {
                TakenAlready = true;
            }
        }
        if (TakenAlready) {
            continue;
        }
        break;
    }
    while (true) {
        Bottem = rand() % (n*n);
        if (Bottem == 0 || Bottem == n*n - 1) { 
            continue;
        }
        if (Bottem >= Top) {
            continue;
        }
        bool TakenAlready = false;
        for (unsigned int i = 0; i < Snakes.size(); i++) {
        if (Snakes[i].Head == Bottem || Snakes[i].Tail == Bottem) {
                TakenAlready = true;
            }
        }
        for (unsigned int i = 0; i < Ladders.size(); i++) {
            if (Ladders[i].Top == Bottem || Ladders[i].Bottem == Bottem) {
                TakenAlready = true;
            }
        }
        if (TakenAlready) {
            continue;
        }
        break;
    }
    Ladder ladder = Ladder(Top, Bottem);
    Ladders.push_back(ladder);
}

class SnakesandLadders {
public:
    vector<string> Board;
    vector<Snake> Snakes;
    vector<Ladder> Ladders;
    SnakesandLadders(int n) {
        for (int i = 1; i <= n*n; i++) {
            Board.push_back(to_string(i));
        }
        srand(time(NULL));
        if (n <= 6) {
            return;
        }
        int SnakesCount = (rand() % (n - 4)) + 4;
        int LaddersCount = (rand() % ((n - 2) - 4)) + 4;
        for (int i = 0; i < SnakesCount; i++) {
            generateSnake(n, Snakes, Ladders);
        }
        for (int i = 0; i < LaddersCount; i++) {
            generateLadder(n, Snakes, Ladders);
        }
    }
    void show(vector<Player> Players) {
        int n = (int) sqrt(Board.size());
        for (int i = 0; i < n; i++) {
            cout << "+-----";
        }
        cout << "+" << endl;
        for (int i = n - 1; i >= 0; i--) {
            if (i % 2 == 1) {
                for (int j = n - 1; j >= 0; j--) {
                    int index = i * n + j;
                    if (index == 0) {
                        cout << "|  GO ";
                        continue;
                    }
                    else if (index == n * n - 1) {
                        cout << "| END ";
                        continue;
                    }
                    bool SnakeOrLadderOrPlayer = false;
                    for (int k = 0; k < Players.size(); k++) {
                        if (index == Players[k].CurrentSlot) {
                            if (Players[k].Symbol.length() == 1) {
                                cout << "|  " << Players[k].Symbol << "  ";
                            }
                            else if (Players[k].Symbol.length() == 2) {
                                cout << "|  " << Players[k].Symbol << " ";
                            }
                            else if (Players[k].Symbol.length() == 3) {
                                cout << "| " << Players[k].Symbol << " ";
                            }
                            SnakeOrLadderOrPlayer = true;
                        }
                    }
                    for (int k = 0; k < Snakes.size(); k++) {
                        if (index == Snakes[k].Head) {
                            cout << "|  S  ";
                            SnakeOrLadderOrPlayer = true;
                        }
                    }
                    for (int k = 0; k < Ladders.size(); k++) {
                        if (index == Ladders[k].Bottem) {
                            cout << "|  L  ";
                            SnakeOrLadderOrPlayer = true;
                        }
                    }
                    if (SnakeOrLadderOrPlayer) {
                        continue;
                    }
                    else if (Board[index].length() == 1) {
                        cout << "|  " << Board[index] << "  ";
                    }
                    else if (Board[index].length() == 2) {
                        cout << "|  " << Board[index] << " ";
                    }
                    else if (Board[index].length() == 3) {
                        cout << "| " << Board[index] << " ";
                    }
                }
            }
            else {
                for (int j = 0; j < n; j++) {
                    int index = i * n + j;
                    if (index == 0) {
                        cout << "|  GO ";
                        continue;
                    }
                    else if (index == n * n - 1) {
                        cout << "| END ";
                        continue;
                    }
                    bool SnakeOrLadderOrPlayer = false;
                    for (int k = 0; k < Players.size(); k++) {
                        if (index == Players[k].CurrentSlot) {
                            if (Players[k].Symbol.length() == 1) {
                                cout << "|  " << Players[k].Symbol << "  ";
                            }
                            else if (Players[k].Symbol.length() == 2) {
                                cout << "|  " << Players[k].Symbol << " ";
                            }
                            else if (Players[k].Symbol.length() == 3) {
                                cout << "| " << Players[k].Symbol << " ";
                            }
                            SnakeOrLadderOrPlayer = true;
                        }
                    }
                    for (int k = 0; k < Snakes.size(); k++) {
                        if (index == Snakes[k].Head) {
                            cout << "|  S  ";
                            SnakeOrLadderOrPlayer = true;
                        }
                    }
                    for (int k = 0; k < Ladders.size(); k++) {
                        if (index == Ladders[k].Bottem) {
                            cout << "|  L  ";
                            SnakeOrLadderOrPlayer = true;
                        }
                    }
                    if (SnakeOrLadderOrPlayer) {
                        continue;
                    }
                    
                    else if (Board[index].length() == 1) {
                        cout << "|  " << Board[index] << "  ";
                    }
                    else if (Board[index].length() == 2) {
                        cout << "|  " << Board[index] << " ";
                    }
                    else if (Board[index].length() == 3) {
                        cout << "| " << Board[index] << " ";
                    }
                }
            }
            cout << "|" << endl;
            for (int i = 0; i < n; i++) {
                cout << "+-----";
            }
            cout << "+" << endl;
        }
        // cout << "Snakes: " << endl;
        // for (unsigned int i = 0; i < Snakes.size(); i++) {
        //     cout << "(" << Snakes[i].Head + 1 << "," << Snakes[i].Tail + 1 << ") / ";
        // }
        // cout <<  endl << "Ladders: " << endl;
        // for (unsigned int i = 0; i < Ladders.size(); i++) {
        //     cout << "(" << Ladders[i].Top + 1 << "," << Ladders[i].Bottem + 1 << ") / ";
        // }
        // cout << endl;
    }
    void update(vector<Player> Players) {
        for (unsigned int i = 0; i < Board.size(); i++) {
            Board[i] = to_string(i + 1);
        }
        for (unsigned int i = 0; i < Ladders.size(); i++) {
            Board[Ladders[i].Bottem] = "L";
        }
        for (unsigned int i = 0; i < Snakes.size(); i++) {
            Board[Snakes[i].Head] = "S";
        }
        for (unsigned int i = 0; i < Players.size(); i++) {
            if (Players[i].CurrentSlot != -1) {
                Board[Players[i].CurrentSlot] = Players[i].Symbol;
            }
        }
    }
};

int rollDice() {
    srand(time(NULL));
    return (rand() % 6) + 1;
}

char randomCharacter() {
    int c = rand() % 26;
    int Upper = rand() % 2;
    if (Upper == 1) {
        return 'A' + c;
    }
    else {
        return 'a' + c;
    }
}

int ReadyPlayers(vector<Player> Players) {
    int count = 0;
    for (int i = 0; i < Players.size(); i++) {
        if (!Players[i].LeftTheGame) {
            count++;
        }
    }
    return count;
}

bool Exists(string Username, vector<Player> Players) {
    for (unsigned int i = 0; i < Players.size(); i++) {
        if (Players[i].Username == Username) {
            return true;
        }
    }
    return false;
}

void suggestUsername(string username, vector<Player> Players) {
    while (username.length() < 8) {
        username += randomCharacter();
    }
    while (Exists(username, Players)) {
        username += randomCharacter();
    }
    cout << "Suggested username: " << username << endl;
}

// Validations

bool isNameValid(string name, vector<Player> Players) {
    for (unsigned int i = 0; i < Players.size(); i++) {
        if (Players[i].Name == name) {
            cout << "Someone else has picked this name!" << endl;
            return false;
        }
    }
    for (unsigned int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i])) {
            cout << "Invalid name" << endl;
            return false;
        }
    }
    return true;
}

bool isSymbolValid(string Symbol, vector<Player> Players) {
    if (Symbol.length() > 3) {
        cout << "Symbol can't be more that 3 characters!" << endl;;
        return false;
    }
    for (unsigned int i = 0; i < Players.size(); i++) {
        if (Players[i].Symbol == Symbol) {
            cout << "Someone else has already chosen this symbol!" << endl;
            return false;
        }
    }
    return true;
}

bool isUsernameValid(string username, vector<Player> players) {
    if (username.length() < 8 || username.length() > 20) {
        cout << "Invalid username" << endl;
        return false;
    }
    int numbers = 0;
    for (unsigned int i = 0; i < username.length(); i++) {
        if (!isalpha(username[i])) {
            if (!isdigit(username[i])) {
                cout << "Invalid username" << endl;
                return false;
            }
            numbers++;
        }
    }
    if (numbers > 3) {
        cout << "Invalid username" << endl;
        return false;
    }
    if (Exists(username, players)) {
        cout << "A user already exists with this username" << endl;
        return false;
    }
    return true;
}

// Menu functions
void addPlayer(vector<Player>& Players) {
    int chances = 5;
    string Name;
    cout << "Name: ";
    cin >> Name;
    while (chances > 0 && !isNameValid(Name, Players)) {
        chances--;
        cout << "Chances left: " << chances << endl;
        cout << "Name: ";
        cin >> Name;
    }
    if (chances > 0) {
        string Symbol;
        cout << "Symbol: ";
        cin >> Symbol; 
        while (chances > 0 && !isSymbolValid(Symbol, Players)) {
            cout << "Symbol: ";
            cin >> Symbol;
        }
        string Username;
        cout << "Username: ";
        cin >> Username;
        while (chances > 0 && !isUsernameValid(Username, Players)) {
            chances--;
            cout << "Chances left: " << chances << endl;
            suggestUsername(Username, Players);
            cout << "Username: ";
            cin >> Username;
        }
        if (chances > 0) {
            Player player = Player(Name, Username, Symbol);
            Players.push_back(player);
            cout << "Player added successfully!" << endl;   
        }
    }
    else {
        cout << "You ran out of chances!" << endl;
    }
}

void StartGame(vector<Player>& Players) {
    int n = 10;
    SnakesandLadders game = SnakesandLadders(n);
    bool isGameOver = false;
    while (true) {
        int times = rand() % 4 + 2;
        for (int i = 0; i < Players.size(); i++) {
            if (!Players[i].LeftTheGame) {
                for (int q = 0; q < times; q++) {
                    system("CLS");
                    game.show(Players);
                    cout << endl << "it is " << Players[i].Name << "'s turn! Press ENTER to roll the dice!" << endl;
                    cin.get();
                    int dice = rollDice();
                    cout << Players[i].Name << " rolled " << dice << endl;
                    
                    if (Players[i].CurrentSlot == -1) {
                        if (dice == 6) {
                            Players[i].CurrentSlot = 0;
                            cout << Players[i].Name << " entered the game!" << endl;
                        }
                        else {
                            Sleep(1000);
                            continue;
                        }
                    }
                    else if (Players[i].CurrentSlot + dice == n * n - 1) {
                        cout << "Player " << Players[i].Name << " reached the end of the game and won!" << endl;
                        isGameOver = true;
                        break;
                    }
                    else if (Players[i].CurrentSlot + dice >= n * n) {
                        cout << "You can't move now! your dice must be a smaller number." << endl;
                        Sleep(2000);
                        continue;
                    } 
                    else if (game.Board[Players[i].CurrentSlot + dice] == "S") {
                        cout << "You have gone into a snake's mouth!" << endl;
                        for (int s = 0; s < game.Snakes.size(); s++) {
                            if (game.Snakes[s].Head == Players[i].CurrentSlot + dice) {
                                Players[i].CurrentSlot = game.Snakes[s].Tail;
                            }
                        }
                    }
                    else if (game.Board[Players[i].CurrentSlot + dice] == "L") {
                        cout << "You reached the bottom of a ladder, you go up!" << endl;
                        for (int l = 0; l < game.Ladders.size(); l++) {
                            if (game.Ladders[l].Bottem == Players[i].CurrentSlot + dice) {
                                Players[i].CurrentSlot = game.Ladders[l].Top;
                            }
                        }
                    }
                    else {
                        for (int j = 0; j < Players.size(); j++) {
                            if (game.Board[Players[i].CurrentSlot + dice] == Players[j].Symbol) {
                                Players[j].CurrentSlot = -1;
                                cout << Players[i].Name << " hit the " << Players[j].Name << endl;
                            }
                        }
                        cout << Players[i].Name << " moved from " << Players[i].CurrentSlot + 1 << " to " << Players[i].CurrentSlot + dice + 1 << endl;
                        Players[i].CurrentSlot += dice;
                    }
                    game.update(Players);
                    Sleep(2000);
                }
                if (isGameOver) {
                    break;
                }
            }
        }
        if (isGameOver) {
            break;
        }
    }
    
    for (int i = 0; i < Players.size(); i++) {
        for (int j = i + 1; j < Players.size(); j++) {
            if (Players[i].CurrentSlot < Players[j].CurrentSlot) {
                Player temp = Players[i];
                Players[i] = Players[j];
                Players[j] = temp;
            }
        }
    }
    int rank = 1;
    for (int i = 0; i < Players.size(); i++) {
        if (!Players[i].LeftTheGame) {
            if (rank == 1) {
                    Players[i].Scores.push_back(50);
                }
                else if (rank == 2) {
                    Players[i].Scores.push_back(25);
                }
                else if (rank == 3) {
                    Players[i].Scores.push_back(5);
                }
                else {
                    Players[i].Scores.push_back(0);
                }
                rank++; 
        }
        else {
            Players[i].Scores.push_back(-1);
        }
    }
        
    
    
    
}

void showPlayers(vector<Player> Players) {
    if (Players.size() == 0) {
        cout << "No players added!" << endl;
    }
    for (int i = 0; i < Players.size(); i++) {
        Players[i].show();
    }
}

void findWinner(vector<Player> Players) {
    for (unsigned int i = 0; i < Players.size(); i++) { // bubble sort
        for (unsigned int j = i + 1; j < Players[i].Scores.size(); j++) {
            if (Players[j].TotalScore() > Players[i].TotalScore()) {
                Player temp = Players[j];
                Players[j] = Players[i];
                Players[i] = temp;
            }
        }
    }
    bool FoundWinner = false;
    for (int i = 0; i < Players.size(); i++) {
        if (Players[i].Won()) {
            cout << "The All-Round Champion:" << endl;
            Players[i].show();
            FoundWinner = true;
        }
    }
    if (!FoundWinner) {
        cout << "We don't have a champion yet!" << endl;
    }
}

void LeaveGame(vector<Player>& Players) {
    string Username;
    cout << "Enter your username: ";
    cin >> Username;
    bool UsernameFound = false;
    for (int i = 0; i < Players.size(); i++) {
        if (Players[i].Username == Username) {
            cout << Players[i].Name << " Left the game!" << endl;
            UsernameFound = true;
            Players[i].LeftTheGame = true;
        }
    }
    if (!UsernameFound) {
        cout << "Username not found!" << endl;
    }
}

main() {
    vector<Player> Players;

    while (true) {
        cout << "------------------------------------------" << endl;
        cout << "Welcome to the Snakes and Ladder game." << endl;
        cout << "1) Add a player, Enter 1" << endl;
        cout << "2) Start the Snakes and Ladder game, Enter 2" << endl;
        cout << "3) Show the players scores in all rounds, Enter 3" << endl;
        cout << "4) Show the all-round champion, Enter 4" << endl;
        cout << "5) Quit the game, Enter 5" << endl;
        cout << "6) And finally, if you want to close the program, Enter 6. Have fun!" << endl;
        cout << ReadyPlayers(Players) << " has registered for the game so far." << endl;
        char n;
        cin >> n;
        if (n == '1') {
            addPlayer(Players);
        }
        else if (n == '2') {
            if (Players.size() >= 2 && Players.size() <= 6) {
                StartGame(Players);
            }
            else {
                cout << "Invalid number of players!" << endl;
            }
        }
        else if (n == '3') {
            cout << "Reporting: " << endl;
            showPlayers(Players);
        }
        else if (n == '4') {
            findWinner(Players);
        }
        else if (n == '5') {
            LeaveGame(Players);
        }
        else if (n == '6') {
            cout << "Cloging the program..." << endl;
            break;
        }
        else {
            cout << "invalid input!" << endl;
        }
    }
}