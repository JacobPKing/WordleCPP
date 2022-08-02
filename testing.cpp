#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readAnswers()
{
    string line;
    vector<string> answers;
    ifstream myfile ("answers.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            answers.push_back(line);
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";    
    }
    return answers;
}

bool validword(string potanswer, string guess, string colors)
{
    //Options are green, yellow, black. Returns true if word is consistent with possible letters
    for (int i = 0; i < 5; i++)
    {
        if (colors[i] == 'o')
        {
            //remove words that do not have the letter, or it is not in the spot
            if (potanswer.find(guess[i]) == string::npos || potanswer[i] != guess[i])
            {
                //cout << "failed on o" << endl;
                return false;
            }
        }
        else if (colors[i] == 'v')
        {
            if (potanswer.find(guess[i]) == string::npos)
            {
                //cout << "failed on v" << endl;
                return false;
            }   
        }
        else if (colors[i] == '-')
        {
            if (potanswer.find(guess[i]) != string::npos)
            {
                //cout << "failed on -";
                return false;
            } 
        }
    }
    return true;
}

vector<string> narrowAnswers(vector<string> wordlist, string guess, string colors)
{

}

int main()
{
    vector<string> answers = readAnswers();
    string colors = "o-v--";
    string guess = "crown";
    for(int i = 0; i < answers.size(); i++) {
        bool possible = validword(answers[i],guess,colors);
        if (possible)
        {
            cout << answers[i] << endl;
        }
        else
        {
            answers[i] = "ppppp";
        }
    }
    for(int i = 0; i < answers.size(); i++) {
        cout << answers[i] << endl;
    }
   //validword("brain","groan","-o-vo");
}