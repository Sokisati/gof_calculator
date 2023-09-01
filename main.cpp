#include <iostream>

//for using vector
#include<vector>

//for using color
#include <windows.h>

//for pow function
#include <cmath>

using namespace std;

vector<int> patternFinderFunction(vector<int> aliveCellsVector)
{

    int i,c,p,checkAgain,t,tempI;
    bool searchBool = false;
    vector<int> patternFound;

    i = 1;
    p = 0;
    tempI = i;

    for(i; i<aliveCellsVector.size(); i++)
    {
        searchBool = false;
        checkAgain = 1;
        tempI = i;

        for(c=i-1; c>=1; c--)
        {
            if(searchBool)
            {
                i = tempI;
                break;
            }

            while(aliveCellsVector[c]==aliveCellsVector[i])
            {
                p++;
                searchBool = true;

                if(i-c-p<=0)
                {
                    if(checkAgain<2)
                    {
                        checkAgain++;
                        t = c;
                        c = i;
                        tempI = i;
                        i = 2*i - t;
                        p = 0;
                    }
                    else
                    {
                        p = 0;
                        for (p; i - c - p > 0; p++)
                        {
                            patternFound.push_back(aliveCellsVector[i + p]);
                        }
                        return patternFound;
                    }
                }

                //pattern with period of above 8 are not possible within a 30x30 grid, hence the i-c>8
                if(aliveCellsVector[c+p]!=aliveCellsVector[i+p] || i-c>8)
                {
                    p = 0;
                    i = tempI;
                    break;
                }
            }
        }
    }

    return patternFound;
}
int binaryCompositionGenerator(int totalDigit, int desiredDigitNumber,int desiredCompositionNumber) {

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    int c = 0;
    int steps = 0;
    int totalCombinations = pow(2, totalDigit);

    if(desiredDigitNumber>totalDigit || desiredCompositionNumber>totalCombinations)
    {
        return 404;
    }
    if (desiredCompositionNumber==0)
    {
        return 0;
    }

    int digitArray[totalDigit + 1];


    //fill intial composition with zero
    for (int i = 0; i < totalDigit; i++)
    {
        digitArray[i] = 0;
    }


    while(c<=totalCombinations)
    {

        if(digitArray[steps]==0)
        {
            for(int i=0; steps-i>0; i++)
            {
                digitArray[i]=0;
            }
            digitArray[steps]=1;

            //we just created a new composition
            c++;

            if(desiredCompositionNumber==c)
            {
                return digitArray[desiredDigitNumber];
            }
            else
            {
                steps = 0;
            }

        }

            //count the steps needed to reach a zero
        else
        {
            steps++;
        }
    }

}


int main()
{


/*x for x spectrum, y for y spectrum,aliveCells for counting alive cells in each generation
*/
    int x,y,g,swap,aliveCells,peakAliveCell,peakGeneration,neiCounter;


    //for using color, nothing really special again
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    //11 means bright cyan, it looks cool
    SetConsoleTextAttribute(h,11);

    //LOOK OUT
    x = 2;

    y = x;
    int totalDigit = pow(x+1,2);
    int totalCombinations = pow(2,totalDigit) - 1;
    swap = 0;
    g = 0;
    neiCounter = 0;
    aliveCells = 0;
    peakAliveCell = 0;
    peakGeneration = 0;
    vector<int> aliveCellsVector;
    vector<int> pattern;
    int gridArray[x+1][y+1][2];
    int deadComposition = 0;
    int aliveComposition = 0;
    bool deadCompositionBool = false;

    int compositionNumber = 0;
    int desiredDigitNumber = 0;


    while(compositionNumber<=totalCombinations)
    {
        //first we must create the initial composition,starting from zero
        for(int i=0; x>=i; i++)
        {
            for(int k=0; y>=k; k++)
            {
               gridArray[k][i][swap] = binaryCompositionGenerator(totalDigit,desiredDigitNumber,compositionNumber);
               desiredDigitNumber++;
            }
        }

        g = 0;

        while(true)
        {

            aliveCells = 0;

            for(int i=0; i<=x; i++)
            {
                for(int k=0; k<=y; k++)
                {
                    neiCounter=
                            (k!=0 && gridArray[k-1][i][swap]==1) +
                            (k+1<=x && gridArray[k+1][i][swap]==1) +
                            (i+1<=y && gridArray[k][i+1][swap]==1) +
                            (i!=0 && gridArray[k][i-1][swap]==1) +
                            (i+1<=y && k!=0 && gridArray[k-1][i+1][swap]==1) +
                            (k!=0 && i!=0 && gridArray[k-1][i-1][swap]==1) +
                            (k+1<=x && i!=0 && gridArray[k+1][i-1][swap]==1) +
                            (k+1<=x && i+1<=y && gridArray[k+1][i+1][swap]==1);

                    if((neiCounter == 2 && gridArray[k][i][swap]==1) || (neiCounter == 3 && gridArray[k][i][swap] == 1) || (neiCounter == 3 && gridArray[k][i][swap] == 0)){

                        gridArray[k][i][!swap] = 1;
                    } else{
                        gridArray[k][i][!swap] = 0;
                    }
                    neiCounter = 0;
                }

            }

//now we are gonna operate for next generation
            swap = !swap;
            g++;


//count the alive cells
            for(int i=0; x>=i; i++)
            {
                for(int k=0; y>=k; k++)
                {
                    if(gridArray[k][i][swap]==1)
                    {
                        aliveCells++;
                    }
                }
            }

            aliveCellsVector.push_back(aliveCells);

            if(aliveCells==0)
            {
                SetConsoleTextAttribute(h,6);
                //it's a dead number/composition
                cout<<"composition: "<<compositionNumber<<" is dead"<<endl;
                deadComposition++;
                aliveCellsVector.clear();
                break;
            }


            pattern = patternFinderFunction(aliveCellsVector);
            if(!pattern.empty())
            {
                SetConsoleTextAttribute(h,8);
                cout<<"composition: "<<compositionNumber<<" is alive forever"<<endl;
                //it's an alive number/composition
                aliveComposition++;
                aliveCellsVector.clear();
                break;
            }

        }


        desiredDigitNumber = 0;
        compositionNumber++;
        SetConsoleTextAttribute(h,9);
    }

    cout<<"dead: "<<deadComposition<<endl;
    cout<<"alive: "<<aliveComposition<<endl;


    return 0;
}