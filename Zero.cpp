#include<bits/stdc++.h>
using namespace std;
bool flag = true;
class Player {
public:
    virtual char getSymbol() = 0;
    virtual int makeMove(const vector<char>& board) = 0;
    virtual int makeBestMove(const vector<char>& board) = 0;
};
class Board {
    vector<char> board;
public:
    Board() : board(9, ' ') {}

    const vector<char>& getBoard() const {
        return board;
    }

    void print() const {
        for (int i = 1; i <= 9; i++) {
            if (i % 3 == 0) {
                if(board[i - 1] == ' '){
                    cout <<" "<< i << endl;
                }else{
                    cout<<" "<< board[i - 1]<<endl;
                }
                
                if (i != 9) {
                    cout << "---+---+---" << endl;
                }
            } else {
                if(board[i - 1] == ' '){
                    cout << " " << i << " |";
                }else{
                    cout<<" "<<board[i - 1]<<" |";
                }
                
            }
        }
    }



    void makeMove(int position, char symbol) {
        board[position - 1] = symbol;
    }
};
class HumanPlayer : public Player {
    char symbol;
public:
    HumanPlayer(char symbol) : symbol(symbol) {} 
    char getSymbol() override { return symbol; }
    int makeMove(const vector<char>& board) override {
        int position;
        cout << "Player"<<symbol<<"'s turn"<<" ";
        while(true){
            cin>>position;
            if (position < 1 || position > 9 || board[position - 1] != ' ') {
                cout << "Invalid move! Try again." << endl;
            }else{
                break;
            }
        }
        return position;
    }
    int makeBestMove(const vector<char>& board) override{
        int position;
        cout << "Player"<<symbol<<"'s turn"<<" ";
        while(true){
            cin>>position;
            if (position < 1 || position > 9 || board[position - 1] != ' ') {
                cout << "Invalid move! Try again." << endl;
            }else{
                break;
            }
        }
        return position;
    }
  
};

class ComputerPlayer : public Player {
    char symbol;
public:
    int minimax(vector<char>& board, bool maximizingPlayer) {
        if (checkWin(board, symbol) ) {
            return -10;
        } else if (checkWin(board, (symbol == 'X' ? 'O' : 'X')) ) {
            return 10;
        } else if (checkDraw(board)) {
            return 0;
        }

        if (maximizingPlayer) {
            int maxScore = INT_MIN;
            for (int i = 0; i < 9; ++i) {
                if (board[i] == ' ') {
                    board[i] = (symbol == 'X' ? 'O' : 'X');
                    int score = minimax(board, false);
                    board[i] = ' ';
                    maxScore = max(maxScore, score);
                }
            }
            return maxScore;
        } else {
            int minScore = INT_MAX;
            for (int i = 0; i < 9; ++i) {
                if (board[i] == ' ') {
                    board[i] = symbol;
                    int score = minimax(board, true);
                    board[i] = ' ';
                    minScore = min(minScore, score);
                }
            }
            return minScore;
        }
    }
    ComputerPlayer(char symbol) : symbol(symbol) { srand(static_cast<unsigned int>(time(nullptr))); } 
    char getSymbol() override { return symbol; }
    int makeMove(const vector<char>& board) override {
        int position;
        do {
            position = rand() % 9 + 1;
        } while (board[position - 1] != ' ');
        cout << "Player"<<symbol<<"'s turn"<<endl;
        return position;
    }
    int makeBestMove(const vector<char>& board) override{
       
       int bestMove = -1;
       int bestScore = INT_MAX;
        for(int i = 0; i < 9; i++){
            if(board[i] == ' '){
                vector<char> newBoard = board;
                newBoard[i] = symbol; 
                int score = minimax(newBoard, true);
                if(score < bestScore){
                    bestScore = score;
                    bestMove = i + 1;
                }
            }
        }
        cout << "Player" << symbol << "'s turn" << endl;
        return bestMove;
    }

  
        


    bool checkWin(const vector<char>& board, char symbol) const {
        const auto& b = board;
        for (int i = 0; i < 3; ++i) {
            if (b[i * 3] == symbol && b[i * 3] == b[i * 3 + 1] && b[i * 3 + 1] == b[i * 3 + 2]) {
                return true;
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (b[i] == symbol && b[i] == b[i + 3] && b[i + 3] == b[i + 6]) {
                return true;
            }
        }
        if ((b[0] == symbol && b[0] == b[4] && b[4] == b[8]) || (b[2] == symbol && b[2] == b[4] && b[4] == b[6])) {
            return true;
        }
        return false;
    }

    bool checkDraw(const vector<char>& board) const {
        for(int i = 0; i < 9; i++){
            if(board[i] == ' '){
                return false;
            }
        }
        return true;
    }
};



class Game {
public:
    bool checkWin(Board &board)  {
        const auto& b = board.getBoard();
        for (int i = 0; i < 3; ++i) {
            if (b[i * 3] != ' ' && b[i * 3] == b[i * 3 + 1] && b[i * 3 + 1] == b[i * 3 + 2]) {
                return true;
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (b[i] != ' ' && b[i] == b[i + 3] && b[i + 3] == b[i + 6]) {
                return true;
            }
        }
        if ((b[0] != ' ' && b[0] == b[4] && b[4] == b[8]) || (b[2] != ' ' && b[2] == b[4] && b[4] == b[6])) {
            return true;
        }
        return false;
    }

    bool checkDraw(Board &board) const {
        for(int i = 0; i < 9; i++){
            if(board.getBoard()[i] == ' '){
                return false;
            }
        }
        return true;
    }
    void start() {
        Board board;
        string mode;
        string difficulty = "";
        Player* player1 = nullptr;
        Player* player2 = nullptr;
        while(true){
            cout << "Select game mode: PVP / PVC / CVC: ";
            cin >> mode;
            if (mode == "PVP") {
                player1 = new HumanPlayer('X');
                player2 = new HumanPlayer('O');
                break;
            } else if (mode == "PVC") {
                player1 = new HumanPlayer('X');
                player2 = new ComputerPlayer('O');
                
                while(true){
                    cout<<"Select difficulty: Easy / Hard: ";
                    cin>>difficulty;
                    if(difficulty == "Easy" || difficulty == "Hard"){
                        break;
                    }else{
                        cout<<"Invalid difficulty Try again."<<endl;
                    }
                }
                break;
            } else if(mode == "CVC") {
                player1 = new ComputerPlayer('X');
                player2 = new ComputerPlayer('O');
                break;
            }else{
                cout << "Invalid game mode! Try again." << endl;
            }
        }

        bool isPlayer1Turn = true;
        while (true) {
                board.print();

                Player* currentPlayer = isPlayer1Turn ? player1 : player2;
                int move;
                if(difficulty == "Hard"){
                    move = currentPlayer->makeBestMove(board.getBoard());
                }else{
                    move = currentPlayer->makeMove(board.getBoard());
                }
               
                board.makeMove(move, currentPlayer->getSymbol());

                if (checkWin(board)) {
                    board.print();
                    cout << "Player"<<(isPlayer1Turn ? player1->getSymbol() : player2->getSymbol())<<": ggez"<<endl;
                    break;
                }

                if (checkDraw(board)) {
                    board.print();
                    cout << "It's a draw!" << endl;
                    break;
                }

                isPlayer1Turn = !isPlayer1Turn;
                flag = true;
            }
        

        delete player1;
        delete player2;
    }
};

int main() {
    Game game;
    game.start();
}
