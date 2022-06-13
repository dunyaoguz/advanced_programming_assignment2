#include <string>
#include "TokenList.h"

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

using std::string;

class Dictionary
{
    private:
        string filename;
        TokenList tokenListBuckets[27];                         // 26 alpha buckets + 1 none-alpha bucket
        size_t bucketIndex(const string& token) const;
    
    public:
        Dictionary(const string& filename);
        Dictionary() = delete;                                  // no default ctor
        ~Dictionary() = default;                                // default dtor
        Dictionary(const Dictionary& ) = default;               // copy ctor
        Dictionary(Dictionary&&) = default;                     // move ctor
        Dictionary& operator=(const Dictionary&) = default;     // copy assignment
        Dictionary& operator=( Dictionary&&) = default;         // move assignment

        void processToken(const string& token, int linenum);
        void print(std::ostream& out) const;

        string getFilename() const;
        TokenList getTokenListBuckets() const;
        size_t getBucketIndex(const string& token) const;
};
#endif