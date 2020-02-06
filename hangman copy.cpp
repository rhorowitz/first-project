/* CISC 1600
   Ryan Horowitz
   Final Part 2 */

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

// Fills the vector with the secret word
// Parameters:
//   list: The secret word
//   chances: the number of chances left for the user
// Postcondition: List contains the secret word
void fill_vector(vector<char> &list, int chances);

// Fills the vector with a specific character
// Parameters:
//   list: The asterisk vector
//   size: the desired size of the list
//   letter: The letter that will be the elements of the list
// Precondition: letter == '*'
// Postcondition: The vector will be a word of size "size" containing the letter
// as all its elements
void fill_vector(vector<char> &list, int size, char letter);

// Replaces asterisks in the asterisk vector with a specific letter using the indices where the
// letter is in the secret word to locate the proper editing location
// Parameters:
//   list: The asterisk vector
//   indices: The indices where the letter will replace the asterisks
//   letter: The guessed letter that will replace asterisks in the list vector
// Postcondition: The vector will have the letter inserted in the correct indices
void edit_vector(vector<char> &list, const vector<int> &indices, char letter);

// Prints out the elements of a vector
// Parameters:
//   list: a vector
// Postcondition: The elements of the vector are printed
void print_vector(const vector<char> &list);

// Checks to see if all elements are asterisks in a vector
// Parameters:
//   list: The asterisk vector 
// Postcondition: Returns true if list does not contain asterisks
bool no_asterisks(const vector<char> &list);

// Check to see if a character is in a vector
// Parameters:
//   list: The secret word
//   guess: The guessed letter
// Postcondition: Returns true if the character is in list and false otherwise
bool is_in_word(const vector<char> &list, char guess);

// Check to see if a character is in a vector and records indices
// Parameters:
//   list: The secret word
//   indices: The indices where the guessed letter is
//   guess: The guessed letter
// Postcondition: Returns true if the guess is in list and records the indices where the guessed
// letter is in list
bool is_in_word(const vector<char> &list, vector<int> &indices, char guess);

// Sorts a list
// Parameters:
//   list: The list of characters
// Postcondition: List will be sorted alphabetically
void sort_vector(vector<char> &list);

// Checks if a list is sorted 
// Parameters:
//   list: The list of characters
// Postcondition: Returns true if list is sorted and false otherwise
bool is_sorted(const vector<char> &list);

int main()
{  
    bool is_valid = true;
    while (is_valid)
    { 
        // Choose difficulty
        char diff;
        int chances = 0;
        cout << "Please enter a difficulty: (e)azy, (m)edium, (h)ard ";
        cin >> diff;
        cout << endl;

        if (diff == 'e' || diff == 'E')
        {
            chances = 6;
        }
        else if (diff == 'm' || diff == 'M')
        {
            chances = 8;
        }
        else if (diff == 'h' || diff == 'H')
        {
            chances = 12;
        }
        else
        {
            cout << "Nonvalid difficulty chosen. Game ending...\n";
            exit(1);
        }
    
        // Create and fill secret word vector and asterisk vector
        vector<char> secret;
        fill_vector(secret, chances);
        vector<char> asterisk;
        fill_vector(asterisk, chances, '*');

        char guess;
        vector<char> guesses;
        vector<int> indices;
    
        while((chances > 0) && !(no_asterisks(asterisk)))
        {
            // Display info and prompt user
            cout << "Previous guesses: ";
            print_vector(guesses);
            cout << endl;
            cout << endl;
            print_vector(asterisk);
            cout << endl;
            cout << endl;
            cout << "You have " << chances << " chances left.\n\n";
            cout << "Please enter your guess(only lowercase letters allowed): ";
            cin >> guess;
            cout << endl;
        
            // Check if guess is in word
            if (is_in_word(secret, indices, guess))
            {
                // Check if guess has already been guessed
                if (is_in_word(guesses, guess))
                {
                    cout << "\nYou already entered that letter and it is in the word.\n\n";
                }
                else
                {
                    // Replace asterisks with letter
                    edit_vector(asterisk, indices, guess);
                    guesses.push_back(guess);
                    chances--;
                }
            }
            else
            {
                cout << "That letter is not in the word.\n\n";
                if (!(is_in_word(guesses, guess)))
                {
                   guesses.push_back(guess);
                   chances--;
                }
            }
            // Check if there are no asterisks in the asterisk vector  
            if (no_asterisks(asterisk))
            {
                cout << "You won!\n\n";
                cout << "The word is ";
                print_vector(asterisk);
                cout << endl;
                cout << endl;
            } 
            // Check if chances == 0
            else if (chances == 0)
            {
                print_vector(asterisk);
                cout << endl;
                cout << endl;
                cout << "You lost :(\n\n";
            }
            // Empty the indices vector
            indices.clear();
            // Sort guesses list
            sort_vector(guesses);
        }
        // Prompt to play again
        char response;
        cout << "Do you want to play again? (y/n) ";
        cin >> response;
        if (response == 'y' || response == 'Y')
        {
            cout << "\nPlaying again...\n\n";
        }
        else
        {
            cout << "\nEnding the game... \n\n";
            is_valid = false;
        }
    }
    return 0;
}



void fill_vector(vector<char> &list, int chances)
{
    if (chances == 6)
    {
        list.push_back('b');
        list.push_back('a');
	list.push_back('l');
	list.push_back('l');
	list.push_back('e');
        list.push_back('t');
    }
    else if (chances == 8)
    {    
        list.push_back('a');
        list.push_back('i');
	list.push_back('r');
	list.push_back('p');
	list.push_back('o');
        list.push_back('r');
        list.push_back('t');
        list.push_back('s');
    }
    else if (chances == 12)
    {    
        list.push_back('m');
        list.push_back('e');
	list.push_back('a');
	list.push_back('n');
	list.push_back('i');
        list.push_back('n');
        list.push_back('g');
        list.push_back('f');
        list.push_back('u');
        list.push_back('l');
        list.push_back('l');
        list.push_back('y');
    }
}

void fill_vector(vector<char> &list, int size, char letter)
{
    for (unsigned int i = 0; i < size; i++)
    {
        list.push_back(letter);
    }
}


void edit_vector(vector<char> &list, const vector<int> &indices, char letter)
{
    for (unsigned int i = 0; i < indices.size(); i++)
    {
        list[indices[i]] = letter;
    }
}

void print_vector(const vector<char> &list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        cout << list[i] << " ";
    }
}

bool no_asterisks(const vector<char> &list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        if (list[i] == '*')
        {
            return false;
        }
    }
    return true;
}

bool is_in_word(const vector<char> &list, char guess)
{
    bool is_there = false;
    for (unsigned int i = 0; i < list.size(); i++)
    {
        if (guess == list[i])
        {
            is_there = true;
        }
    }
    return is_there;
}

bool is_in_word(const vector<char> &list, vector<int> &indices, char guess)
{
    bool is_there = false;
    for (unsigned int i = 0; i < list.size(); i++)
    {
        if (guess == list[i])
        {
            indices.push_back(i);
            is_there = true;
        }
    }
    return is_there;
}

void sort_vector(vector<char> &list)
{
    while (!(is_sorted(list)))
    {
        for (unsigned int i = 0; i < list.size() - 1; i++)
        {
            if (list[i] > list[i+1])
            {
                char temp = list[i+1];
                list[i+1] = list[i];
                list[i] = temp;
            }
        }
    }
}

bool is_sorted(const vector<char> &list)
{
    for (unsigned int i = 0; i < list.size() - 1; i++)
    {
        if (list[i] > list[i+1])
        {
            return false;
        }
    }
    return true;
}
