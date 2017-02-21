/*
 Andrew J Wood
 FSU ID: ajw14m
 February 20, 2017
 
 Header file for wordsmith.h
 
 A WordSmith object stores words in an underlying set available set in the FSU library.  The set itself uses the fsu::Pair as the key and the fsu::LessThan as the predicate object for the ordered sets.  These can be changed by commenting out the appropriate code in the header file.
 
    The API shoes the ability to Read text from a file, write a report showing each individual word read and the frequency, display a summary of all words and quanties read so far, and to clear the set of all data.
 
    The cleanup method is a helper method used to make it easy for the client to store words; it removes junk characters according to a set of rules for the program.
 
    The copy constructor and assignment operator are marked as private methods and are not implemented so that the compiler does not generate default versions.
 */

#ifndef WORDSMITH_H
#define WORDSMITH_H

#include <cctype> //various std library character methods
#include <xstring.h> //fsu::String
#include <list.h> //fsu::List
#include <pair.h> //fsu::Pair
#include <olist.h> //fsu::MOList, fsu::UOList
#include <ovector.h> //fsu::MOVector, fsu::UOVector

class WordSmith
{
    
public:
         WordSmith();            //default constructor
         ~WordSmith();           //destructor
    bool ReadText       (const fsu::String& infile, bool showProgress = 0); //read file contents
    bool WriteReport    (const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const;
    void ShowSummary    () const;
    void ClearData      () const;
    
private:
    
    //internal class terminology
    typedef fsu::Pair < fsu::String, unsigned long >    EntryType;
    typedef fsu::LessThan < EntryType >                 PredicateType;
    
    //associate container classes for SetType - choose one
    
    //typedef fsu::UOList < EntryType, PredicateType >    SetType;
    //typedef fsu::MOList < EntryType, PredicateType >    SetType;
    typedef fsu::UOVector < EntryType, PredicateType >  SetType;
    //typedef fsu::MOVector < EntryType, PredicateType >  SetType;
    //typedef fsu::RBLLT < EntryType, PredicateType >     SetType;
    
    SetType                     wordset_; //specified set
    fsu::List < fsu::String >   infiles_; //list of file names
    
    static void Cleanup (fsu::String&); //removes invalid characters from string
    
    // copy constructor and assignment operator - not implemented
    WordSmith (const WordSmith &);
    WordSmith& operator = (const WordSmith &);
    
    
}; // end class WordSmith


#endif // wordsmith.h
