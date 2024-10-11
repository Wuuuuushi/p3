#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP

#include <string>
#include <iostream>

namespace shindler::ics46::project3 {

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.

// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// That would give you a 0 for a, etc;  add one to get 'a' = 1, 'b' = 2, etc.

// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
[[nodiscard]] size_t polynomialHashFunction(const std::string &string,
                                            unsigned base, unsigned mod);

// These are value template parameters. You can pass in a value rather than a
// type into the parameter and use its value. This allows them to be set
// dynamically rather than having static constants within the class.
// Think of them as class constants (you can just use them like a variables
// named H1, H2, and EvictThreshold)
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
class BaseWordSet {
   private:
    // You may declare private functions and member variables here.

    size_t HashSize{}; // Keep track of the distinct strings
    size_t ArraySize{}; //Keep track of array size for mod paramter
    void resize();
    bool isPrime(size_t number);
    void nextPrime();

   public:
    explicit BaseWordSet(size_t initialCapacity);
    ~BaseWordSet();

    // You do not need to worry about implementing these. They are only
    // here to ensure that we let the compiler know these functions
    // should not exist.
    BaseWordSet(const BaseWordSet &) = delete;
    BaseWordSet(BaseWordSet &&) = delete;
    BaseWordSet &operator=(const BaseWordSet &) = delete;
    BaseWordSet &operator=(BaseWordSet &&) = delete;

    // adds the given string to the WordSet, so that any
    // future calls to contains(s) will return true, unless that is later
    // removed.
    void insert(const std::string &string);

    std::string * HashTable1{}; //Set two pointer and will point to array when constructed
    std::string * HashTable2{};

    void printInsertStatements() const;

    [[nodiscard]] bool contains(const std::string &string) const;

    // return how many distinct strings are in the set
    [[nodiscard]] size_t size() const noexcept;

    // return how large the underlying array is.
    [[nodiscard]] size_t capacity() const noexcept;

    void erase(const std::string &string);
};

// You Should not use anything within the _impl namespace in your code.
// Instead reference the H1, H2, and EvictThreshold template parameters
namespace _impl {
const static unsigned int BASE_H1 = 37;
const static unsigned int BASE_H2 = 41;
const unsigned int BASE_EVICTION_THRESHOLD = 5;
}  // namespace _impl

// Add a usings statement with the default values for the project.
using WordSet =
    BaseWordSet<_impl::BASE_H1, _impl::BASE_H2, _impl::BASE_EVICTION_THRESHOLD>;

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::BaseWordSet(size_t initialCapacity) {

    HashTable1 = new std::string [initialCapacity]; //Create new arrays for HashTable to point to.
    HashTable2 = new std::string [initialCapacity];
    ArraySize = initialCapacity; //Set ArraySize to intial Capacity
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::~BaseWordSet() {
    delete [] HashTable1;
    delete [] HashTable2;
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
bool BaseWordSet<H1, H2, EvictThreshold>::isPrime(size_t number){

    for(size_t i{2}; i < number; i++) //Start i at 2 because 1 is always a multiple of any number. Go until half of the number since after half it is impossible to find a multiple.
    {
        if(number % i == 0) //If the mod is equal to 0 then it is a multiple.
        {
            return false;
        }
    }
    return true;
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::nextPrime(){
    //Set ArraySize to next integer value and check to see if prime. Continue until ArraySize is a prime.
    ArraySize*= 2;
    while(!isPrime(ArraySize))
    {
        ArraySize++;
    }
}


template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::resize(){
    size_t PreviousArraySize{ArraySize};
    nextPrime(); //Sets ArraySize to next prime
    BaseWordSet resizeWordSet(ArraySize); //Make a temporary BaseWordSet to use the insert features

    for(size_t i{0}; i < PreviousArraySize; i++) //Iterate through all the Hashes and insert them into the new resizeWordSet
    {
        if(HashTable1[i] != "")
        {
            resizeWordSet.insert(HashTable1[i]);
        }
    }
    for(size_t i{0}; i < PreviousArraySize; i++) 
    {
        if(HashTable2[i] != "")
        {
            resizeWordSet.insert(HashTable2[i]);
        }
    }
    //Set the old tables equal to the new tables

    delete [] HashTable1;
    delete [] HashTable2;

    HashTable1 = new std::string [ArraySize];
    HashTable2 = new std::string [ArraySize];

    for (size_t i{0}; i < ArraySize; i++)
    {
        if (resizeWordSet.HashTable1[i] != "")
        {
            HashTable1[i] = resizeWordSet.HashTable1[i];
        }
        if (resizeWordSet.HashTable2[i] != "")
        {
            HashTable2[i] = resizeWordSet.HashTable2[i];
        }
    }
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::insert(const std::string &string) {

    size_t FirstHashValue{polynomialHashFunction(string, H1, ArraySize)}; 

    if (HashTable1[FirstHashValue] == "")
    {
        HashTable1[FirstHashValue] = string;
        HashSize++;
    }
    else
    {
        std::string OldValue{HashTable1[FirstHashValue]};

        HashTable1[FirstHashValue] = string;

        unsigned int numIteration{0}; 
        unsigned int index{0};
        size_t hashValue{0};

        while(OldValue != "")
        {
            if(numIteration == EvictThreshold)
            {
                resize();
                this->insert(OldValue);
                break;
            }
            else
            {
                std::string replacement{};
                if (index % 2 == 0)
                {
                    hashValue = polynomialHashFunction(OldValue, H2, ArraySize);

                    if (HashTable2[hashValue] == "")
                    {
                        HashTable2[hashValue] = OldValue;
                        HashSize++;
                        break;
                    }
                    replacement = OldValue;
                    OldValue = HashTable2[hashValue];
                    HashTable2[hashValue] = replacement;
                }
                else
                {
                    hashValue = polynomialHashFunction(OldValue, H1, ArraySize);

                    if (HashTable1[hashValue] == "")
                    {
                        HashTable1[hashValue] = OldValue;
                        HashSize++;
                        break;
                    }
                    replacement = OldValue;
                    OldValue = HashTable1[hashValue];
                    HashTable1[hashValue] = replacement;
                }
            }
            index++;
            numIteration++;
        }
    }


    // size_t FirstHashValue{polynomialHashFunction(string, H1, ArraySize)}; 
    // if (HashTable1[FirstHashValue] == "")
    // {
    //     HashTable1[FirstHashValue] = string;
    //     HashSize++;
    // }
    // else
    // {
    //     std::string OldValue{HashTable1[FirstHashValue]}; //Store value that is going to be evicted

    //     HashTable1[FirstHashValue] = string; // Evict the value

    //     unsigned int numIteration{0}; 
    //     unsigned int index{0};
    //     size_t hashValue{0};

    //     while(OldValue != "")
    //     {
    //         if(numIteration == EvictThreshold) //If the number of iterations reach the Threshold resize the arrays
    //         {
    //             resize();
    //             this -> insert(string); //Re-insert the string back in after the resize and break once finished.
    //             break;
    //         }
    //         else
    //         {
    //             if (index % 2 == 0)
    //             {
    //                 hashValue = polynomialHashFunction(OldValue, H2, ArraySize);
    //                 if (HashTable2[hashValue] == "")
    //                 {
    //                     HashTable2[hashValue] = OldValue;
    //                     break;
    //                 }
    //                 OldValue = HashTable2[hashValue];
    //             }
    //             else
    //             {
    //                 hashValue = polynomialHashFunction(OldValue, H1, ArraySize);
    //                 if (HashTable1[hashValue] == "")
    //                 {
    //                     HashTable1[hashValue] = OldValue;
    //                     break;
    //                 }
    //                 OldValue = HashTable1[hashValue];
    //             }
    //         }
    //         index++;
    //         numIteration++;
    //     }
    // }
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::printInsertStatements() const {
    std::cout << "HashTable1:" << std::endl;
    for (size_t i = 0; i < ArraySize; ++i) {
        std::cout << "[" << i << "]: " << HashTable1[i] << std::endl;
    }

    std::cout << "\nHashTable2:" << std::endl;
    for (size_t i = 0; i < ArraySize; ++i) {
        std::cout << "[" << i << "]: " << HashTable2[i] << std::endl;
    }
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
bool BaseWordSet<H1, H2, EvictThreshold>::contains(
    const std::string &string) const {

    size_t FirstHashValue{polynomialHashFunction(string, H1, ArraySize)}; //Get both Hash Values and check if value is in either one if not return false
    size_t SecondHashValue{polynomialHashFunction(string, H2, ArraySize)};

    if(HashTable1[FirstHashValue] == string)
    {
        return true;
    }

    if(HashTable2[SecondHashValue] == string)
    {
        return true;
    }

    return false;
}

// return how many distinct strings are in the set
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::size() const noexcept {
    return HashSize;
}

// return how large the underlying array is.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::capacity() const noexcept {
    return ArraySize;
}

// removes this word if it is in the wordset.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::erase(const std::string &string) {
    // TODO: Implement this.

    size_t FirstHashValue{polynomialHashFunction(string, H1, ArraySize)}; //Get both Hash Values and check if value is in either one if not return false
    size_t SecondHashValue{polynomialHashFunction(string, H2, ArraySize)};

    if(HashTable1[FirstHashValue] == string)
    {
        HashTable1[FirstHashValue] = "";
    }

    if(HashTable2[SecondHashValue] == string)
    {
        HashTable2[SecondHashValue] = "";
    }

}

}  // namespace shindler::ics46::project3

#endif
