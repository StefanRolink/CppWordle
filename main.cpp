#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

const int WORD_SIZE = 5;
const int WORD_SIZE_PLUS_NL = WORD_SIZE + 1;
const int NUM_OF_TRIES = 10;

random_device rd;  // Obtain random number from hardware.
mt19937 gen(rd()); // Seed generator.

int generate_random_number(int min, int max)
{
  uniform_int_distribution<>distr(min, max); // define range.
  return distr(gen);
}

string get_word()
{
  // Open wordle list:
  ifstream words_file("wordle-list/words");

  if(words_file.is_open())
  {
    // Count number of lines/words:
    const int max_words = count(istreambuf_iterator<char>(words_file), istreambuf_iterator<char>(), '\n');
   
    // clog << "Words found: " << max_words << endl;
    //
    // for(int i = 0; i < 100; i++)
    // {
    //   clog << "rand i: " << generate_random_number(0, max_words) << endl;
    // }
    
    // Retrieve and return a random word from list:
    int ran = generate_random_number(0, max_words);
    words_file.seekg((ran-1) * WORD_SIZE_PLUS_NL, ios::beg);

    string word_buffer;
    getline(words_file, word_buffer);

    // cout << "Found word " << word_buffer << " at pos " << ran << endl;

    return word_buffer;      
  }
  else 
  {
    cerr << "Words file could not be openened, exiting.." << endl;
  }
  
  return "";
}

bool input_valid(string input)
{
  bool success = true;
  success &= !input.empty();
  success &= input.length() == WORD_SIZE;
 
  if(success)
  {
    for(char & c : input)
    {
      success &= isalpha(c);
    }
  }

  return success;
}

string get_hint_string(string input, string answer)
{
  // Construct hint string, for each element:
  const char NOT_FOUND = 'x'; // x -> letter not in answer.
  const char FOUND     = '?'; // ? -> letter in answer (somehwere).
  const char CORRECT   = '!'; // ! -> letter on this place in answer.
  string hint = string(WORD_SIZE, NOT_FOUND);

  for(int i = 0; i < WORD_SIZE; ++i)
  {
    if(input[i] == answer[i])
    {
      hint[i] = CORRECT;
    }
    else if(answer.find(input[i]) != string::npos)
    {
      hint[i] = FOUND; 
    }
  }

  return hint;
}

int main(int argc, char * argv[])
{
  string answer = get_word();
  
  if(input_valid(answer))
  {
    int tries_left = NUM_OF_TRIES;
    // Let's play!
    while(tries_left >= 0)
    {
      string input;
      cout << "Please guess the word" << setw(25) << "Tries left: " << tries_left << endl;
      cin >> input;
      if(input_valid(input))
      {
        if(answer.compare(input) == 0)
        {
          cout << "Correct! You've won!" << endl;
          break;
        }

        cout << "input valid!" << endl;
        cout << get_hint_string(input, answer) << endl << endl; 
        if(tries_left > 0)
        {
          tries_left--;
        }
        else
        {
          cout << "Out of tries. Too bad, better luck next time.." << endl;
          break;
        }
      }
      else
      {
        cout << "Word should be 5 letters, please tries_left again" << endl;
      }
    } 
    // game end..
  }

  return 0;
}
