/*
 Andrew J Wood
 FSU ID: ajw14m
 February 20, 2017
 
 Implementation for WordSmith API
 
 This file implements the API described in wordsmith.h
 
 */

#include <wordsmith.h> // included to indicate that this is the implementation file

WordSmith::WordSmith() : wordset_(), infiles_()  //default constructor
{}

WordSmith::~WordSmith() // destructor
{} //note - destructors of each element will be called

bool WordSmith::ReadText (const fsu::String& infile, bool showProgress)
{
    std::cout << "hi";
    return 1;
}

bool WordSmith::WriteReport (const fsu::String& outfile, unsigned short c1, unsigned short c2) const
{
    std::cout << "hi";
    return 1;
}

void WordSmith::ShowSummary () const
{
    std::cout << "hi";
    std::cout << std::isalpha('5');
}

void WordSmith::ClearData () const
{
    std::cout << "hi";
    fsu::List <int> mylist;
}
