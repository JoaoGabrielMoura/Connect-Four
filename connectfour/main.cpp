/*  Joao Gabriel Moura De Almeida
    Matricula: A01193400
    11/13/15
    Programa: Un programa donde dos usuarios pueden jugar el juego conecta cuatro, gana el primero que tenga
    cuatro X o O seguidos en vertical, horizontal o diagonal.
 */
#include <iostream>
using namespace std;

const int iSize = 7;

//Display table when the game first starts
void startBoard(char cMatBoard[iSize][iSize])
{
    cout << "Game Start!" << endl;
    
    cout << endl;
    
    //Output top numbers
    for(int i=1; i<=7; i++)
    {
        cout << i << "\t";
    }
    
    cout << endl;
    
    //Output empty spaces
    for(int iR=0; iR<iSize; iR++)
    {
        for (int iC=0; iC<iSize; iC++)
        {
            cMatBoard[iR][iC] = '-';
            cout << cMatBoard[iR][iC] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

//Display player number and where chip is going to be placed
void choosePlace(char cMatBoard[iSize][iSize], int iPlayerNum, int &iColumn)
{
    cout << "Player #" << iPlayerNum << " turn" << endl;
    cout << "Column chosen: ";
    cin >> iColumn;
    
    if(iColumn<1 || iColumn>7)
    {
        cout << "Please select a number between 1 and 7"<< endl;
        cout << "Column chosen: ";
        cin >> iColumn;
    }
}

//Place chip in the lowest place possible in column
int placeChip(char cMatBoard[iSize][iSize], int iPlayerNum, int iColumn)
{
    int i;
    if(cMatBoard[0][iColumn-1]=='-')
    {
        if(iPlayerNum==1)
        {
            for(i=0; cMatBoard[i][iColumn-1]=='-'; i++)
            {
                if(i==6)
                    cMatBoard[i][iColumn-1] = 'X';
            }
            i--;
            cMatBoard[i][iColumn-1] = 'X';
        }
    
        else
        {
            for(i=0; cMatBoard[i][iColumn-1]=='-'; i++)
            {
                if(i==6)
                    cMatBoard[(i)][iColumn-1] = 'O';
            }
            i--;
            cMatBoard[(i)][iColumn-1] = 'O';
        }
    }
    return i;
}

//Displays board after picking place
void displayBoard(char cMatBoard[iSize][iSize])
{
    for(int i=1; i<=7; i++)
    {
        cout << i << "\t";
    }
    
    cout << endl;
    
    for(int iR=0; iR<iSize; iR++)
    {
        for (int iC=0; iC<iSize; iC++)
        {
            cout << cMatBoard[iR][iC] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

//Checks if a player has won
bool checkWin(bool bGamewin, int iRow, int iColumn, char cMatBoard[iSize][iSize], int iPlayerNum)
{
    int iVertical, iHorizontal, iDiagonal1, iDiagonal2, iV, iH;
    
    iVertical = 1;
    iHorizontal = 1;
    iDiagonal1 = 1;
    iDiagonal2 = 1;
    
    //Horizontal
    for(iH = iColumn; cMatBoard[iRow][iH] == cMatBoard[iRow][iColumn-1] && iH <= 6; iH++, iHorizontal++){} //Left
    for(iH = iColumn-2; cMatBoard[iRow][iH] == cMatBoard[iRow][iColumn-1] && iH>=0; iH--, iHorizontal++){} //Right
    if(iHorizontal >= 4)
    {
        cout << "Player #" << iPlayerNum << " Won (-)" << endl;
        return true;
    }
    
    
    //Horizontal
    for(iV = iRow+1; cMatBoard[iV][iColumn-1] == cMatBoard[iRow][iColumn-1] && iV <= 6; iV++, iVertical++){} //Right
    for(iV = iRow-1; cMatBoard[iV][iColumn-1] == cMatBoard[iRow][iColumn-1] && iV >=0; iV++, iVertical++){} //Left
    if(iVertical >= 4)
    {
        cout << "Player #" << iPlayerNum << " Won (|)" << endl;
        return true;
    }
    
    //Diagonal (\)
    for(iH = iRow+1, iV = iColumn; cMatBoard[iH][iV] == cMatBoard[iRow][iColumn-1] && iH <= 6 && iV <=6; iH++, iV++, iDiagonal1++){} //Down and right
    for(iH = iRow-1, iV = iColumn-2; cMatBoard[iH][iV] == cMatBoard[iRow][iColumn-1] && iH >= 0 && iV >= 0; iH--, iV--, iDiagonal1++){} //Up and left
    if(iDiagonal1 >= 4)
    {
        cout << "Player #" << iPlayerNum << " Won(\\)" << endl;
        return true;
    }
    
    //Diagonal (/)
    for(iH = iRow-1, iV = iColumn; cMatBoard[iH][iV] == cMatBoard[iRow][iColumn-1] && iH>=0 && iV<=6; iH--, iV++, iDiagonal2++){} //Down and left
    for(iH = iRow+1, iV = iColumn-2; cMatBoard[iH][iV] == cMatBoard[iRow][iColumn-1] && iH<=6 && iV>=0; iH++, iV--, iDiagonal2++){} //Up and right
    if(iDiagonal2 >= 4)
    {
        cout << "Player #" << iPlayerNum << " Won(/)" << endl;
        return true;
    }
    return false;
}


int main() {

    char cMatBoard[iSize][iSize], cAnswer; //Board Size 7x7
    int iPlayerNum, iColumn, iRow, iRound; //Number of player and Column chosen
    bool bGamewin, bStopgame;
    
    startBoard(cMatBoard);
    bGamewin = false;
    bStopgame = false;
    iPlayerNum = 1;
    iRound = 0;
    
    while(bGamewin == false || bStopgame == true)
    {
        choosePlace(cMatBoard, iPlayerNum, iColumn);
        iRow = placeChip(cMatBoard, iPlayerNum, iColumn);
        iRound++;
        displayBoard(cMatBoard);
        bGamewin = checkWin(bGamewin, iRow, iColumn, cMatBoard, iPlayerNum);
         
        //Change Players
        if(iPlayerNum==1)
            iPlayerNum=2;
        else
            iPlayerNum=1;
        
        //Tie
        if(bGamewin == false)
        {
            if(iRound==49){
                cout << "Tie!" << endl;
            }
        }
        if(iRound==49)
            break;
        
        //Ask if player wants to keep playing(s S = yes || n N = no)
        if(bGamewin == false)
        {
            do{
                cout << "Do you want to keep playing?(S/s or N/n)" << endl;
                cin >> cAnswer;
                if(cAnswer == 'n' || cAnswer == 'N')
                {
                
                }
                else if(cAnswer == 's' || cAnswer == 'S')
                {
                    
                }
            }while(!(cAnswer == 'n' || cAnswer == 'N' || cAnswer == 's' || cAnswer == 'S'));
        }
        
        if(cAnswer == 'n' || cAnswer == 'N')
            break;
    }
    return 0;
}
