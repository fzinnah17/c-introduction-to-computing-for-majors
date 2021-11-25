#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> animals;
string animals_str;

vector<string> animals_options;
string options_str;

vector<string> animals_answer;
string answer_str;

int options_no;

int success = 0;
int failure = 0;

int level = 1;

void takeAnswer();
void makeQuestion();

int main()
{
    srand(time(NULL));

    int success = 0;
    int level = 1;

    // Take input

    cout << "Enter at least five animals names, e.g., cat, dog, etc..." << endl;

    while(true)
    {
        getline(cin, animals_str);

        if(animals_str.length() <= 0)
        {
            break;
        }

        stringstream check(animals_str);

        string temp;

        while(getline(check, temp, ' '))
        {
            animals.push_back(temp);
        }
    }

    int i = 1;

    for(auto animal:animals)
    {
        cout << i++ << ": " << animal << endl;
    }

    cout << endl;

    // Make question

    makeQuestion();

    return 0;
}

void takeAnswer()
{
    animals_answer.clear();
    answer_str = "";

    getline(cin, answer_str);

    cout << endl;

    if(answer_str.compare("?") == 0)
    {
        int i = 1;

        for(auto animal:animals_options)
        {
            cout << i++ << ": " << animal << endl;
        }

        cout << "\nYour number of input is incorrect. Enter again: ";
        takeAnswer();
    }
    else if (answer_str.compare("quit") == 0)
    {
        cout << "Bye..." << endl;
        exit(0);
    }

    stringstream check(answer_str);

    string temp;

    while(getline(check, temp, ' '))
    {
        animals_answer.push_back(temp);
    }

    if(animals_answer.size() == options_no)
    {
        bool is_correct = is_permutation(animals_options.begin(), animals_options.end(), animals_answer.begin());

        if(is_correct)
        {
            success += 1;
            failure = 0;

            cout << "Yes!" << endl;
        }
        else
        {
            success = 0;
            failure += 1;

            cout << "No!" << endl;
        }

        cout << endl;

        if(success >= 2)
        {
            level += 1;
            success = 0;

            cout << "Succeeded two consecutive times, challenge goes up!\n" << endl;
        }
        else if (failure >= 2)
        {
            if(level > 1)
            {
                level -= 1;
                failure = 0;

                cout << "Missed two consecutive times, challenge goes down!\n" << endl;
            }
        }
    }
    else
    {
        cout << "Your number of input is incorrect. Enter again: ";
        takeAnswer();
    }
}

void makeQuestion()
{
    while(true)
    {
        animals_options.clear();
        options_str = "";

        animals_options = animals;

        random_shuffle(begin(animals_options), end(animals_options));

        options_no = 1 + (rand() % 3);

        animals_options.resize(options_no);

        for(auto animal:animals_options)
        {
            options_str += animal;
        }

        random_shuffle(begin(options_str), end(options_str));

        if(level > 1)
        {
            int i = level;

            while(i > 1)
            {
                int index = rand() % options_str.length();

                if(options_str.at(index) != '_')
                {
                    options_str.replace(index, 1, "_");
                    i--;
                }
            }
        }

        cout << "What are " << options_no;

        if(options_no > 1)
        {
            cout << " animals ";
        }
        else
        {
            cout << " animal ";
        }

        cout << "in " << "\"" << options_str << "\"" << " ? ";

        // Take answer

        takeAnswer();
    }
}
