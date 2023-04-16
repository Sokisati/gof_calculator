#include <iostream>

//for using sleep() function
#include <stdio.h>
#include <unistd.h>

//for using color
#include <windows.h>

//for using randomnes
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int binaryCompositionGenerator(int totalDigit, int desiredDigitNumber,int desiredCompositionNumber)
{

    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    int c;
    c = 0;
    int totalCombinations;
    totalCombinations = pow(2,totalDigit);

    int digitArray[totalDigit+1];


    //fill intial composition with zero
    for(int i=totalDigit; i>0; i--)
    {
        digitArray[i]=0;
    }

    c++;


    //action begins
    while(c<=totalCombinations)
    {
        int steps;
        steps = 0;
        //for loop for general checking
        for(int i=totalDigit; i>0; i--)
        {
            //count the steps needed to reach a zero
            if(digitArray[i]!=0)
            {
                steps++;
            }

                //now use it
            else
            {
                int t = totalDigit;

                for(int s=steps ; s>0; s--)
                {
                    digitArray[t]=0;
                    t--;
                }

                //it erased all the past 1's into all zeros. now make the final digit, a one
                digitArray[t]=1;
                break;
            }


        }

        //now we need to operate for next composition
        //check if we reached the desired place
        if(c==desiredCompositionNumber)
        {
            return digitArray[desiredDigitNumber];
        }

/*
        //write to console

        for (int i = 1; i <= totalDigit; i++)
        {
            if(digitArray[i]==1)
            {
                SetConsoleTextAttribute(h,10);
                cout << digitArray[i];
            }
            else
            {
                SetConsoleTextAttribute(h,15);
                cout << digitArray[i];
            }

        }
        SetConsoleTextAttribute(h,4);
        cout<<"  composition number is: "<<c;
        cout << "\n";
*/
        c++;

    }

}


int main()
{

    srand(time(0));


/*x for x spectrum, y for y spectrum, delay for sleeping the program for a specific amount of seconds, aliveCells for counting alive cells in
a generation, peakAliveCell for knowing the max amount of alive cells and peakGeneration for knowing which generation peaked in terms of alive cell count
*/
    int x,y,g,delay,aliveCells,stableCounter,peakAliveCell,peakGeneration,totalCombinations;
    int stillAlive = 0;
    int wantYouGone = 0;
    int probabilityArray[15];


    //for using color, nothing really special again
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

    //11 means bright cyan, it looks cool
    SetConsoleTextAttribute(h,11);

    //LOOK OUT
    x = 4;
    y = x;

    totalCombinations = pow(2,pow(x,2));

    g = 0;
    stableCounter = 0;
    aliveCells = 0;
    int aliveCellsArray[420];
    int gridArray[x+2][y+2][420];

    //LOOK OUT
    delay=0;




//mark all as dead

    for(int i=1; x>=i; i++)
    {

        for(int k=1; y>=k; k++)
        {

            gridArray[k][i][g]=0;

        }

    }






//write the first generation
    for(int i=1; x>=i; i++)
    {

        for(int k=1; y>=k; k++)
        {
            if(gridArray[k][i][g]==1)
            {
                SetConsoleTextAttribute(h,10);
                cout<<"  "<<gridArray[k][i][g];
            }
            else
            {
                SetConsoleTextAttribute(h,4);
                cout<<"  "<<gridArray[k][i][g];
            }


        }
        cout<<"\n";
    }
    cout<<"\n"<<endl;

 //this is where the fun begins
 //a quick test

 int t = x*x;
 int d = 1;
 int c = 1;



for(int m=c; m<totalCombinations; m++) {

    cout<<"operating for composition: "<<m<<endl<<endl;
d = 1;

    for (int i = 1; x >= i; i++) {

        for (int k = 1; y >= k; k++) {


            gridArray[k][i][g] = binaryCompositionGenerator(t, d, m);
            d++;

        }

    }

    //write
    for (int i = 1; x >= i; i++) {

        for (int k = 1; y >= k; k++) {
            if (gridArray[k][i][g] == 1) {
                SetConsoleTextAttribute(h, 10);
                cout << "  " << gridArray[k][i][g];
            } else {
                SetConsoleTextAttribute(h, 4);
                cout << "  " << gridArray[k][i][g];
            }


        }
        cout << "\n";
    }
    //we are now operating for the current composition

    while(true){
//scan every array value and decide if they are alive or not in the next generation

//we need to know how many alive neighbours a cell has so we can determine whether it's alive in the next gen or not (note: in all 8 directions)
        int neiCounter =0;


        for(int i=1; i<=x; i++)
        {

            for(int k=1; k<=y; k++)
            {

                //lets count the alive neighbour cell for every cell

                //every if statement has at least one safety precaution (like k!0=0 or i+1<=y) so that program doesn't look for an array value that doesn't exist.
                //one more important thing is that we need to put the safety precaution first inside the statement
                neiCounter=
                        (k!=0 && gridArray[k-1][i][g]==1) +
                        (k+1<=x && gridArray[k+1][i][g]==1) +
                        (i+1<=y && gridArray[k][i+1][g]==1) +
                        (i!=0 && gridArray[k][i-1][g]==1) +
                        (i+1<=y && k!=0 && gridArray[k-1][i+1][g]==1) +
                        (k!=0 && i!=0 && gridArray[k-1][i-1][g]==1) +
                        (k+1<=x && i!=0 && gridArray[k+1][i-1][g]==1) +
                        (k+1<=x && i+1<=y && gridArray[k+1][i+1][g]==1);

                //lets judge if he is alive or not


                if((neiCounter == 2 && gridArray[k][i][g]==1) || (neiCounter == 3 && gridArray[k][i][g] == 1) || (neiCounter == 3 && gridArray[k][i][g] == 0)){
                    gridArray[k][i][g+1] = 1;
                } else{
                    gridArray[k][i][g+1] = 0;
                }

                //we need to reset the counter so that it doesn't add up constantly
                neiCounter = 0;
            }

        }

//we sometimes need to examine generations so there should be some breathing time (also it looks ugly as hell otherwise)
        sleep(delay);

//now we are gonna operate for next generation
        g++;

        if(g>400)
        {
            cout<<"Looks like it reached into a stable or ever-repeating position. No need to calculate for another billion generations, right?"<<endl;
            stillAlive++;
            cout<<"still alive: "<<stillAlive<<endl;
            break;
        }


        SetConsoleTextAttribute(h,11);
        cout<<"\n"<<"\n";
        cout<<"generation: "<<g<<endl;

//count the alive cells
        for(int i=1; x>=i; i++)
        {

            for(int k=1; y>=k; k++)
            {

                if(gridArray[k][i][g]==1)
                {
                    aliveCells++;
                }


            }

        }


        cout<<"alive cells :"<<aliveCells<<endl;
        if(aliveCells==0)
        {

            cout<<"All cells are dead. This place once thrived with life, now it's a wasteland because of your composition."<<endl;
            wantYouGone++;
            cout<<"want you gone:"<<wantYouGone<<endl;
            break;
        }


//lets write down the next generation
        for(int i=1; x>=i; i++)
        {

            for(int k=1; y>=k; k++)
            {
                if(gridArray[k][i][g]==1)
                {
                    SetConsoleTextAttribute(h,10);
                    cout<<"  "<<gridArray[k][i][g];
                }
                else
                {
                    SetConsoleTextAttribute(h,4);
                    cout<<"  "<<gridArray[k][i][g];
                }


            }
            cout<<"\n";
        }

        aliveCellsArray[g]=aliveCells;

        if(g>2 && aliveCellsArray[g]==aliveCellsArray[g-1])
        {
            stableCounter++;
        }
        else
        {
            stableCounter=0;
        }

        SetConsoleTextAttribute(h,11);

        if(stableCounter==20)
        {
            cout<<"Looks like it reached into a stable or ever-repeating position. No need to calculate for another billion generations, right?"<<endl;
            stillAlive++;
            cout<<"still alive: "<<stillAlive<<endl;
            break;
        }

        aliveCells=0;

    }
    //end of while loop
  g = 0;


    cout<<"\n"<<endl<<endl;

}

cout<<"w"<<wantYouGone<<endl;
cout<<"s"<<stillAlive<<endl;



/*

*/

return 0;
}
