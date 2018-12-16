/**
File: main.cpp
Description:This program will find the words' concordances from the attach text file and print the result.
Author: Pei-Yu Kuo
Email: peiyuk9810@student.vvc.edu
Data Created: 12-04-18
**/
#include<iostream>
#include "concordance.h"

 
int main()
{
   Concordance con("alice.txt");  
   con.print();
   return 0;
}
