/*
 Andrew J Wood
 FSU ID: ajw14m
 February 20, 2017
 
 Implementation for WordSmith API
 
 This file implements the API described in wordsmith.h
 
 */

#include <wordsmith.h> // included to indicate that this is the implementation file
#include <fstream> // Allows for read access to files
#include <entry.h>
#include <iomanip>

WordSmith::WordSmith() : wordset_(), infiles_()  //default constructor
{}

WordSmith::~WordSmith() // destructor
{} //note - destructors of each element will be called

bool WordSmith::ReadText (const fsu::String& infile, bool showProgress)
{
    const char * fileForOpen = infile.Cstr();
    std::ifstream inClientFile(fileForOpen, std::ios::in); //open file for read
    
    if (!inClientFile)
    {
        return 0; //return 0, indicating file could not be read
    }
    
    const unsigned long tickerVal = 0xFFFF;
    fsu::String wordString;
    size_t wordCounter = 0;
    
    while (inClientFile >> wordString) //read words from file separated by whitespace, continue until EOF
    {
        WordSmith::Cleanup(wordString); //cleans up the string as per rules
        
        if (wordString.Length() == 0) //if cleanup operation resulted in 0-length word
            continue; //skip and restart loop
        
        EntryType wordPair(wordString,1); //declares Pair containing string
        
        //determine if the word is already included
        //bool isThere detrmines what to do
        
        bool isThere = wordset_.Retrieve(wordPair); //determines if pair is already in the set
        
        if (!isThere) //if the pair is not already in the set
        {
            wordset_.Insert(wordPair);
        }
        else //the pair already exists, "wordPair" is now the referenced Pair
        {
            unsigned long numEntries;
            numEntries = ++(wordPair.second_);
            EntryType wordPair(wordString, numEntries); //redeclare wordPair with updated count
            wordset_.Insert(wordPair); //unimodal container does not allow duplicates; will replace
        }
        
        ++wordCounter; //increment the word counter
        
        if (showProgress) //if ticker is enabled
        {
            if (wordCounter % tickerVal == 0) //if the read word count is a multiple of the ticker value
            {
                std::cout << "  ** reading progress : numwords == " << wordCounter << "\n";
            }
        }
        
    } // end reading file
    
    std::cout << "\n\tNumber of words read:    " << wordCounter;
    std::cout << "\n\tCurrent vocabulary size: " << VocabSize() << "\n";
    
    infiles_.PushBack(infile); //pushes the file name to the infiles_ list
    
    return 1; //operation was successful
}

bool WordSmith::WriteReport (const fsu::String& outfile, unsigned short c1, unsigned short c2) const
{
    const char * fileForWrite = outfile.Cstr();
    std::ofstream outClientFile(fileForWrite, std::ios::out); //opens file for output
    
    if (!outClientFile)
    {
        return 0; //error - file could not be written
    }
    
    //check to see if infiles_ is empty
    if (infiles_.Empty())
    {
        std::cout << "\n No files in read list, leaving " << outfile << " unopened\n";
        outClientFile.close();
        return 1;
    }
    
    outClientFile.seekp(0); //ensure the pointer is at the beginning of the file
    
    outClientFile << "Text Analysis for files: ";

    ListType::ConstIterator i; //declare itatator for list
    for (i = infiles_.Begin(); i != infiles_.End(); ++i)
    {
        outClientFile << *i;
        if (i != infiles_.rBegin()) //if the iterator is not on the last file
            outClientFile << ", "; //comma space
    }
    
    outClientFile << "\n\n";
    
    outClientFile << std::setw(c1) << std::left << "word";
    outClientFile << std::setw(c2) << std::right << "frequency";
    outClientFile << "\n";
    outClientFile << std::setw(c1) << std::left << "----";
    outClientFile << std::setw(c2) << std::right << "---------";
    
    outClientFile << "\n";
    
    //loop through all words
    SetType::Iterator setIterator;
    for (setIterator = wordset_.Begin(); setIterator != wordset_.End(); ++setIterator)
    {
        outClientFile << std::setw(c1) << std::left << (*setIterator).first_;
        outClientFile << std::setw(c2) << std::right << (*setIterator).second_;
        outClientFile << "\n";
    }
    
    //create temp vars to avoid multiple calls
    size_t numWords = WordsRead();
    size_t vocabSize = VocabSize();
    
    //once file is finished, output summary
    outClientFile << "\n";
    outClientFile << "Number of words: " << numWords << "\n";
    outClientFile << "Vocabulary size: " << vocabSize << "\n";
    
    outClientFile.close(); //close the file
    
    //output summary information to screen
    std::cout << "\n\tNumber of words:         " << numWords << "\n";
    std::cout << "\tVocabulary size:         " << vocabSize << "\n";
    std::cout << "\tAnalysis written to file ";
    std::cout << outfile;
    std::cout << "\n\n";

    return 1; //file written successfully
}

void WordSmith::ShowSummary () const
{
    std::cout << "\nCurrent files:           ";
    ListType::ConstIterator i; //declare itatator for list
    for (i = infiles_.Begin(); i != infiles_.End(); ++i)
    {
        std::cout << *i;
        if (i != infiles_.rBegin()) //if the iterator is not on the last file
            std::cout << ", "; //comma space
    }
    std::cout << "\nCurrent word count:      ";
    std::cout << WordsRead();
    std::cout << "\nCurrent vocabulary size: ";
    std::cout << VocabSize();
    std::cout << "\n\n";
}

void WordSmith::ClearData ()  //temporarily using as debugger
{
    wordset_.Clear(); //empty the data
    infiles_.Clear(); //empty the list of file names
}

size_t WordSmith::WordsRead() const
{
    size_t accumulator = 0; //create accumulator
    SetType::ConstIterator i; //declare iterator for set
    for (i = wordset_.Begin(); i != wordset_.End(); ++i)
    {
        accumulator += (*i).second_; //add value of second pair item to accumulator
    }
    return accumulator;
}

size_t WordSmith::VocabSize() const
{
    return wordset_.Size(); //returns size of wordset
}
