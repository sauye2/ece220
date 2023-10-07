//partners: sauye2, cgwang3
/* The purpose of this program is to print out all of the semiprime numbers within a range specified by user input and return 1 if the range
 * included any semiprime numbers. If the range did not include any semiprime numbers, then the program should return 0. If the inputs were
 * invalid, then return -1 and print error message. For this MP, we were to use GDB to debug any errors found within the provided code. In
 * experimenting with GDB, I found that the code had 5 errors that caused the program to function incorrectly (these errors are numbered in
 * the comments). The first error was on line 35, which was due to the line returning 1 if the remainder were 0. If the remainder were 0,
 * then that indicated that the number was not a prime number and should return 0 instead of 1. The second error was on line 38, which was
 * due to the line returning 0 if the remainder was not 0. If the remainder was not equal to 0, then the number is a prime number and the
 * code should return 1. The third error in the code was found in line 57, which was due to the fact that the value of k was being set to
 * be the remainder when dividing i and j. This would make the second operand equal to zero, which is not a prime number and would thus
 * not print the corret values. Since you are trying to see if the second operand being multiplied to the value in j is prime
 * or not, you should divide i and j in order to get the second operand, k. The fourth error is in line 60 which should set the ret value
 * to 1 if a semiprime number were found. If this line wasn't added, then the the code would not return the correct values after finishing
 * its execution and would always return 0. The fifth error is in line 61 which should include a break command in order to break out of the
 * second for loop once a semiprime number has been found and printed. Without the break command, the code would continue looping until j=i,
 * which could potentially cause the program to print semiprime numbers multiple times. Adding this command limits the printing to just one
 * time.
 */

#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than number
        if (number % i == 0) { //check if the remainder is 0
	  return 0;            // 1) return values were flipped, if remainder is 0 then "number" is not prime and should return 0
	  
        }
    }
    return 1;                // 2) return value should be 1 if "number" is a prime number
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
		  k = i/j;                    // 3) error was it should be k=i/j instead of k=i%j
                    if (is_prime(k)) {
                        printf("%d ", i);
		        ret = 1;             // 4) if both j and k are prime, then program should return 1 instead of 0
			break;               // 5) code should break out of this for loop once a number is shown to be prime and is printed
			
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
