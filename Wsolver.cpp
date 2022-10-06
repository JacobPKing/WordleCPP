#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> guesses;

vector<string> readFile(string fname)
{
    string line;
    vector<string> answers;
    ifstream myfile (fname);
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
        cout << "Unable to open file" << endl;    
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
            if (potanswer.find(guess[i]) == string::npos || potanswer[i] == guess[i])
            {
                //cout << "failed on v" << endl;
                return false;
            }   
        }
        else if (colors[i] == '-')
        {
            if (potanswer.find(guess[i]) != string::npos)
            {
                //cout << "failed on -" << endl;
                return false;
            } 
        }
    }
    return true;
}

vector<string> narrowAnswers(vector<string> answers, string guess, string colors)
{
    for(int i = 0; i < answers.size(); i++) {
        bool possible = validword(answers[i],guess,colors);
        if (possible)
        {
            //cout << answers[i] << endl;
        }
        else
        {
            answers[i] = "ppppp";
        }
    }
    vector<string> newAns;
    for(int i = 0; i < answers.size(); i++) {
        if(answers[i] != "ppppp")
        {
            newAns.push_back(answers[i]);
        }
    }
    return newAns;
}

string genColors(string answer, string guess)
{
    string out = "";
    for(int i = 0; i < 5; i++)
    {
        if(answer.find(guess[i]) == string::npos)
        {
            out.append("-");
        }
        else if (answer[i] == guess[i])
        {
            out.append("o");
        }
        else if (answer.find(guess[i]) != string::npos)
        {
            out.append("v");
        }
    }
    return out;
}

string lowestW (map<string,int> words)
{
    string bestW;
    int bestL = 999999;
    for(auto iter = words.begin(); iter != words.end(); ++iter)
    {
        if(iter -> second < bestL && iter->second > 0)
        {
            bestL = iter -> second;
            bestW = iter -> first;
        }
        //cout << iter -> first << iter -> second << endl;
    }
    cout << bestL << bestW << endl;
    return "Hi!";
}

map<string,int> bestWord(vector<string> possAnswers)
{
    map<string, int> outMap;
    for(int i = 0; i < guesses.size(); i++)
    {
        string guess = guesses[i];
        //cout << guess << endl;
        int guessleft = 0;
        for(int e = 0; e < possAnswers.size(); e++)
        {
            string tc = genColors(possAnswers[e],guess);
            guessleft = guessleft + narrowAnswers(possAnswers,guess,tc).size();
        }
        outMap[guess] = guessleft;
    }
    return outMap;
}

int main()
{
    vector<string> answers = readFile("answers.txt");
    guesses = readFile("guesses.txt");
    string colors = "-----";
    string guess = "brain";
    answers = narrowAnswers(answers,guess,colors);
    cout << "Here are all the possible answers now" << endl;
    for(int i = 0; i < answers.size(); i++) {
        cout << answers[i] << endl;
    }
    map<string,int> yes = bestWord(answers);
    lowestW(yes);
    /*
    answers = narrowAnswers(answers,"olein","--v--");
    cout << endl;
    for(int i = 0; i < answers.size(); i++) {
        cout << answers[i] << endl;
    }
    */
    //for(int i = 0; i < guesses.size(); i++)
    //{
        //cout << guesses[i] << ": " << possibles[guesses[i]] << endl;
    //}
    //validword("brain","groan","-o-vo");
    //cout << genColors("coyly","crawl") << endl;
    return 0;
}
