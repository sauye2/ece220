//partners: sauye2, cgwang3
//The purpose of this program is to print the coefficients of Pascal's Triangles of a single row when a row
//index is inputted by the user. By implementing the equation given to us for this MP, we were able to correctly
//code through testing and debugging. At first, we tried to use a for loop in order to replicate the function of
//the multiplication summation but we decided to switch for the better by using the while loop instead. The code
//performs the calculations for each number of coefficients and prints it out on the console. We were able to
//implement this by setting conditional situations where the loop continues until k was equal to n.



#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n; // row = n
  printf("Enter a row index: ");
  scanf("%d",&n);

  // Write your code here
  
unsigned long k=2; // declare variable k
unsigned long i=1; // declare variable i
unsigned long formval; // holds the value of the formula
unsigned long product=1; // product of interaction
unsigned long coeff; // declare coeff variable

if (n==0){
    printf ("%d ",1); // in the case the row number is 0, only print 1
    printf ("\n");
}
else
{
  printf ("%d ",1);  //if row number is not 0, print 1 and then calculate following  coefficients to print
  while (k<=n)
{
    while (i<k)
    {
        formval=(n+1)-i; //per numerator of formula n+1-i
        product=product*formval; // multiplication summation: last iteration times current
        coeff = product/i; // per formula (n+1-i)/i
        product = coeff; // load new coeff value back into product
        i++;
    } 
    printf ("%lu ",coeff);  //print coefficients
    k++;
}
if (k==n+1)
{
    printf ("%d",1);  //print 1 for the last coefficient
}
    printf("\n");  //print newline 
    return 0;      //finish code
}
}
