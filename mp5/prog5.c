//partners: sauye2, cgwang3
/*The purpose of this code is to generate a pseudo-random 4-digit code that the user has to crack by
 *guessing four numbers at a time. At the end of each guess, the program will identify how many numbers
 *in your guess are perfect matches and how many are misplaced matches. You have 12 guesses to try to
 *guess the code correctly, otherwise you will lose the game and be presented with the correct code.
 *In order to get the code to function correctly, we had to add a series of code to the set_seed, 
 *start_game, and make_guess functions. Once implemented, we tested the program with the test cases
 *provided.
 */



/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
  int seed;             //declare variable seed to store integer value after sscanf function
  char post[2];
  
  int return_val = sscanf(seed_str, "%d%1s", &seed, post);   //check to see if user input is a single integer with no letters and set return to return_val
    if(return_val == 1){                                     //if return value is 1, call function srand and return 1; else print error and return 0
			srand(seed);
			return 1;
    }
    else{
	 printf("set_seed: invalid seed\n");
	 return 0;
    }
}

		
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    *one = rand() % 8 + 1;  
    *two = rand() % 8 + 1;  
    *three = rand() % 8 + 1;    
    *four = rand() % 8 + 1; //set *one,*two,*three,*four to be a pseudo-random value between 0-7 and add 1 to make range 1-8
    solution1 = *one;
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;      //set the solution values for each digit for the later part of the code.

    guess_number = 1;       //initialize the guess number to be the first guess

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
        char post[2];
        int w,x,y,z;        //declare variables
        int a=0;           //var=1 if solution# is matched
        int b=0;
        int c=0;
        int d=0;
        int e=0;           //var=1 if guess number is matched
        int f=0;
        int g=0;
        int h=0;
        int perfect = 0;
        int misplaced = 0; //initalize perfect and misplaced counter to 0
        
        int return_vall = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
        if (return_vall == 4){
            if (1<=w && w<=8){
                if (1<=x && x<=8){
                    if (1<=y && y<=8){
                        if (1<=z && z<=8){
                                     //test if the guess is 4 digits and if each digit is 1-8. If guess is valid, check for perfect and misplaced matches
                            *one = w;
                            *two = x;
                            *three = y;
                            *four = z;
                            if(*one==solution1){
                                perfect++;
                                a=1;
                                e=1;
                            }
                            if(*two==solution2){
                                perfect++;
                                b=1;
                                f=1;
                            }
                            if (*three==solution3){
                                perfect++;
                                c=1;
                                g=1;
                            }
                            if (*four==solution4){
                                perfect++;
                                d=1;
                                h=1;
                            }                                                        
                            if(*one==solution2 && e!=1 && b!=1){
                                misplaced++;
                                b=1;
                                e=1;   
                                }
                            if(*one==solution3 && e!=1 && c!=1){
                                    misplaced++;
                                    c=1;
                                    e=1;
                                }
                            if(*one==solution4 && e!=1 && d!=1){
                                    misplaced++;
                                    d=1;
                                    e=1;  
                                }                                        
                            ////////////////////////////////////////////////////////////////end of testing *one values with solution values

                            if(*two==solution1 && f!=1 && a!=1){
                                misplaced++;
                                a=1;
                                f=1;   
                                }
                            if(*two==solution3 && f!=1 && c!=1){
                                    misplaced++;
                                    c=1;
                                    f=1;
                                }
                            if(*two==solution4 && f!=1 && d!=1){
                                    misplaced++;
                                    d=1;  
                                    f=1;
                                }
                            ///////////////////////////////////////////////////////////////////end of testing *two values with solution values
                            if(*three==solution1 && g!=1 && a!=1){
                                misplaced++;
                                a=1;   
                                g=1;
                                }
                            if(*three==solution2 && g!=1 && b!=1){
                                    misplaced++;
                                    b=1;
                                    g=1;
                                }
                            if(*three==solution4 && g!=1 && d!=1){
                                    misplaced++;
                                    d=1;  
                                    g=1;
                                } 
                            ////////////////////////////////////////////////////////////////////end of testing *three values with solution values
                            if(*four==solution1 && h!=1 && a!=1){
                                misplaced++;
                                a=1;   
                                h=1;
                                }
                            if(*four==solution2 && h!=1 && b!=1){
                                    misplaced++;
                                    b=1;
                                    h=1;
                                }
                            if(*four==solution3 && h!=1 && c!=1){
                                    misplaced++;
                                    c=1;  
                                    h=1;
                                }   
                            ////////////////////////////////////////////////////////////////////////end of testing *four values with solution values
                            printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number,perfect,misplaced);
                            guess_number++;             //print statement and increment guess_number
                            return 1;

                            }

                        }

                    }

                }

            }
        
printf ("make_guess: invalid guess\n");     //print invalid message if the guess is invalid
return 0;
}

//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed



