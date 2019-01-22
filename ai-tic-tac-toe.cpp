#include <vector>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

struct Board
{

  vector<char> vals;
  int minmaxScore;

  Board() : minmaxScore(0) {
    for(int i = 0; i < 9; i++)
    {
      vals.push_back('-');
    }
  };

  int getScore()
  { return minmaxScore; }

  void setScore (int newScore)
  { minmaxScore = newScore; }

  void printBoard()
  {

    for(int i = 0; i < vals.size(); i++)
    {
        if((i+1) % 3 == 0)
        {
          cout << " " << vals[i] << endl;
        } else
        {
          cout << " " <<vals[i] << " ";
        }
    }
  }

  vector<char> getBoard ()
  {
    return vals;
  }

  vector<int> openSpaces()
  {
    vector<int> tempSpaceCol;
    for(int i = 0; i < 9; i++)
    {
      if(vals[i] == '-')
      {
        tempSpaceCol.push_back(i);
      }
    }
    return tempSpaceCol;
  }

  void setBoard (vector<char> tempBoard)
  {
    vals = tempBoard;
  }

  bool isFinished()
  {
     if(vals[0] == vals[1] && vals[1] == vals[2] && vals[0] != '-')
     {
       return true;
     }
     if(vals[3] == vals[4] && vals[4] == vals[5] && vals[3] != '-')
     {
       return true;
     }
     if(vals[6] == vals[7] && vals[7] == vals[8] && vals[6] != '-')
     {
       return true;
     }
     if(vals[0] == vals[3] && vals[3] == vals[6] && vals[0] != '-')
     {
       return true;
     }
     if(vals[1] == vals[4] && vals[4] == vals[7] && vals[1] != '-')
     {
       return true;
     }
     if(vals[2] == vals[5] && vals[5] == vals[8] && vals[2] != '-')
     {
       return true;
     }
     if(vals[0] == vals[4] && vals[4] == vals[8] && vals[0] != '-')
     {
       return true;
     }
     if(vals[2] == vals[4] && vals[4] == vals[6] && vals[2] != '-')
     {
       return true;
     }

     for(int i = 0; i < 9; i++)
     {
       if(vals[i] == '-')
       {
         return false;
       }
     }
     return true;
  }

  bool didAIwin()
  {
    // ai always plays x
    if(vals[0] == vals[1] && vals[1] == vals[2] && vals[0] == 'x')
    {
      return true;
    }
    if(vals[3] == vals[4] && vals[4] == vals[5] && vals[3] == 'x')
    {
      return true;
    }
    if(vals[6] == vals[7] && vals[7] == vals[8] && vals[6] == 'x')
    {
      return true;
    }
    if(vals[0] == vals[3] && vals[3] == vals[6] && vals[0] == 'x')
    {
      return true;
    }
    if(vals[1] == vals[4] && vals[4] == vals[7] && vals[1] == 'x')
    {
      return true;
    }
    if(vals[2] == vals[5] && vals[5] == vals[8] && vals[2] == 'x')
    {
      return true;
    }
    if(vals[0] == vals[4] && vals[4] == vals[8] && vals[0] == 'x')
    {
      return true;
    }
    if(vals[2] == vals[4] && vals[4] == vals[6] && vals[2] == 'x')
    {
      return true;
    }
    return false;
  }

  bool didOPPwin()
  {
    // opp is always o
    if(vals[0] == vals[1] && vals[1] == vals[2] && vals[0] == 'o')
    {
      return true;
    }
    if(vals[3] == vals[4] && vals[4] == vals[5] && vals[3] == 'o')
    {
      return true;
    }
    if(vals[6] == vals[7] && vals[7] == vals[8] && vals[6] == 'o')
    {
      return true;
    }
    if(vals[0] == vals[3] && vals[3] == vals[6] && vals[0] == 'o')
    {
      return true;
    }
    if(vals[1] == vals[4] && vals[4] == vals[7] && vals[1] == 'o')
    {
      return true;
    }
    if(vals[2] == vals[5] && vals[5] == vals[8] && vals[2] == 'o')
    {
      return true;
    }
    if(vals[0] == vals[4] && vals[4] == vals[8] && vals[0] == 'o')
    {
      return true;
    }
    if(vals[2] == vals[4] && vals[4] == vals[6] && vals[2] == 'o')
    {
      return true;
    }
    return false;
  }

  void makeMove(int i, string turn)
  {
    if(turn == "ai")
    {
      vals[i] = 'x';
    } else
    {
      vals[i] = 'o';
    }
  }

};

typedef struct Board Board;


int getMaxPoint(vector<Board> possibleBoards)
{
  int currMax = possibleBoards[0].getScore();
  for(int i = 1; i < possibleBoards.size(); i++)
  {
     currMax = currMax < possibleBoards[i].getScore() ? possibleBoards[i].getScore() : currMax;
  }
  return currMax;
}

int getMinPoint(vector<Board> possibleBoards)
{
  int currMin = possibleBoards[0].getScore();
  for(int i = 1; i < possibleBoards.size(); i++)
  {
     currMin = currMin > possibleBoards[i].getScore() ? possibleBoards[i].getScore() : currMin;
  }
  return currMin;
}

Board getMaxBoard(vector<Board> possibleBoards)
{
  int maxIndex = 0;
  int maxPoint = possibleBoards[0].getScore();
  for(int i = 1; i < possibleBoards.size(); i++)
  {
    if(possibleBoards[i].getScore() > maxPoint)
    {
      maxPoint = possibleBoards[i].getScore();
      maxIndex = i;
    }
  }
  return possibleBoards[maxIndex];
}


Board MINMAX_HELPER(Board currentBoard, string turn)
{

    if(currentBoard.isFinished())
    {
      if(currentBoard.didAIwin())
      {
        currentBoard.setScore(1);
      } else if(currentBoard.didOPPwin())
      {
        currentBoard.setScore(-1);
      } else
      {
        currentBoard.setScore(0);
      }

      return currentBoard;
    }

    vector<int> getPossibleMoves = currentBoard.openSpaces();

    vector<Board> possibleBoards;

    for(int i = 0; i < getPossibleMoves.size(); i++)
    {
      Board tempBoard;
      tempBoard.setBoard(currentBoard.getBoard());
      tempBoard.makeMove(getPossibleMoves[i],turn);
      string tempTurn = turn;
      if(tempTurn == "ai")
      {
         tempTurn = "human";
      } else
      {
        tempTurn = "ai";
      }
      possibleBoards.push_back(MINMAX_HELPER(tempBoard, tempTurn));
    }

    if(turn == "ai")
    {
      // max my output
      currentBoard.setScore(getMaxPoint(possibleBoards));
      return currentBoard;
    }

    currentBoard.setScore(getMinPoint(possibleBoards));
    return currentBoard;
}

Board MINMAX(Board currentBoard)
{
    vector<int> getPossibleMoves = currentBoard.openSpaces();

    vector<Board> possibleBoards;

    for(int i = 0; i < getPossibleMoves.size(); i++)
    {
      Board tempBoard;
      tempBoard.setBoard(currentBoard.getBoard());
      tempBoard.makeMove(getPossibleMoves[i],"ai");
      possibleBoards.push_back(MINMAX_HELPER(tempBoard, "human"));
    }


    return getMaxBoard(possibleBoards);
}


void startGame()
{
   string welcomeMsg = "\n Hello world, wana play tic-tac-toe with AI. Well here are the instructions \n\n";
   string instruct   = " The board is numbered from 0 - 8 \n boardNumber [ENTER] - perform play \n x [ENTER] - to quite game \n r [ENTER] - to restart game \n Make a play and let us see how good you are :) \n";
   cout << welcomeMsg << instruct << endl;
}

void gamePlay(Board currentBoard, string playing)
{
   currentBoard.printBoard();

   if(currentBoard.isFinished())
   {
     cout << " " << "GAME OVER" << endl;
     if(currentBoard.didAIwin())
     {
       cout << " " << "AI WINS!!!!! YOU CAN NEVER BEAT THE AI DUDE!" << endl;
     } else if(currentBoard.didOPPwin())
     {
       cout << " " << "MATHEMATICALLY, YOU ARE NOT SUPPOSED TO WIN!" << endl;
     } else
     {
       cout << " " << "DRAW? :) YOU ARE BETTER THAN THE AVERAGE PERSON. STILL NO MATCH FOR THE AI THO, SORRY!" << endl;
     }
     Board tempBoardEnd;
     currentBoard.setBoard(tempBoardEnd.getBoard());

   }

   if(playing == "human")
   {
      cout << " " << "ENTER board-number to play OR x to quite OR r to restart" << endl;
      char val = ' ';
      cin >> val;
      if(isdigit(val))
      {
        int number = val - '0';
        if(number < 0 || number > 8)
        {
          cout << " " << "ERROR: board-numbers are from 0-8" << endl;
          gamePlay(currentBoard,"human");
        } else
        {
          currentBoard.makeMove(number, "human");
          gamePlay(currentBoard,"ai");
        }
      } else if (val == 'x')
      {
        return;
      } else if(val == 'r')
      {
        Board newBoard;
        gamePlay(newBoard,"human");
      } else
      {
        cout << " " << "ERROR: wrong input!!" << endl;
        gamePlay(currentBoard,"human");
      }
   } else
   {
     cout << " " << "AI (Thinking...)" << endl;
     gamePlay(MINMAX(currentBoard),"human");
   }

}

int main()
{
    startGame();
    Board gameBoard;
    gamePlay(gameBoard, "human");

}
