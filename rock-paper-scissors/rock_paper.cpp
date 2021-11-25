#include <iostream>
#include <ctime>

using namespace std;

int main ()
{
    string userTurn;
    string cpuTurn;
    string Rock;
    string Paper;
    string Scissor;

    char 'r', 's', 'p', 'q', 'R', 'S', 'P', 'Q';
    int quit;
    while(quit==-1)
    {
        srand (time(NULL));
        cout<<"Rock-Paper-Scissor shoo:";

        cin >> userTurn;
        cout << endl;

        if(userTurn== "r")
        {

            userTurn = "Rock";

        }

        if(userTurn== "p")
        {

            userTurn = "Paper";

        }

        if(userTurn== "s")
        {

            userTurn = "Scissors";

        }

        int cpuTurn=(rand () % 3) + 1;
        if(cpuTurn== "r")
        {

            cpuTurn = "Rock";

        }

        if(cpuTurn== "p")
        {

            cpuTurn = "Paper";

        }

        if(cpuTurn== "s")
        {

            cpuTurn = "Scissors";

        }

        // need to change from here especially the str [i] p1_count
        if (cpuTurn== 1 && userTurn == 2)
        {
            cout<<"I am "<<str[i]<<", You won..."<<endl;
        }
        else if (cpuTurn== 2 && userTurn == 3)
        {
            cout<<"I am "<<str[i]<<", I won..."<<endl;
        }
        else if (cpuTurn== 3 && userTurn == 1)
        {
            cout<<"I am "<<str[i]<<", tied..."<<endl;
        }
        else
        {
            cout<<"Move not found. Please re-enter: "<<endl;
        }
        if( userChoice!= 'R' && userChoice != 'P' && userChoice != 'S')
        {
            cout<<"OOPS....Enter Again.."<<endl;
            continue;
        }
        cout<<"You won "<<p1_count<<", lost "<<p2_count<<", tied "<<tied;
        if(c1 == 'Q') break;


    }

}


