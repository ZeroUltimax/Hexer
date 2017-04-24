#include "stdafx.h"
#include "Hexer.h"
#include "Replacement.h"

using zux::Replacement;

// pre-sort match size in descending order
const zux::Replacement
prefix[] = { { "ox","0X",0 } }, // Constants starting with 0X
suffix[] = { //  Constants type endings
{ "ull","ULL",0 }, 
{ "ul","UL",0 },
{ "ll","LL",0 },
{ "u","U",0 },
{ "l","L",0 },
},
infix[] = {
{ "tree","3",5 }, // verbatim replaces
{ "hate","8",5 },
{ "tri","3",5 },
{ "tri","3",5 },
{ "for","4",5 },
{ "fur","4",5 },
{ "ate","8",5 },
{ "eit","8",5 },
{ "ite","8",5 },
{ "au","0",5 }, 
{ "ck","CC",4 },  // ck-> cc ex.: luck -> lucc
{ "a","A",0 }, // Exact replaces
{ "b","B",0 },
{ "c","C",0 },
{ "d","D",0 },
{ "e","E",0 },
{ "f","F",0 },
{ "o","0",1 }, // almost perfect
{ "i","1",2 },
{ "l","1",2 },
{ "s","5",2 },
{ "t","7",2 },
{ "z","2",3 }, // streching it
{ "g","6",3 },
{ "u","00",4 }, // u -> oo ex.: judo -> joodo
{ "k","CC",4 }, // k -> cc ex.: ink -> incc
}
;

using zux::Hexer;

string burn(const string& s){
    char* buffer = new char[s.length() + 1];
    char* write = buffer;
    for (char c : s) {
        if ('a' <= c && c <= 'z') {
            *write++ = c;
        }
        else if ('A' <= c && c <= 'Z') {
            *write++ = c + ('a' - 'A');
        }
    }
    *write = 0;

    string result = string(buffer);
    delete buffer;
    return result;
}

void ApplyPrefixes(std::string &target, int &pos, int &cost);
void ApplySuffixes(std::string &target, int &cost, int &dEnd);
void ApplyInfixes(std::string &target, int &pos, int &cost);

void Hexer::transmogrify(string in){
    string target = burn(in);
    int pos = 0, dEnd = 0;
    int cost = 0;

    ApplyPrefixes(target, pos, cost);
    ApplySuffixes(target, cost, dEnd);
    ApplyInfixes(target, pos, cost);

    if (pos + dEnd == target.length()) {
        cout << in << '\t' << target << '\t' << cost << endl;
    }
}

void ApplyPrefixes(std::string &target, int &pos, int &cost)
{
    //prefixes
    for (const Replacement& pre : prefix) {
        if (pre.tryReplacement(target, pos, cost)) {
            break; // break after 1, only 1 prefix allowed
        }
    }
}

void ApplySuffixes(std::string &target, int &cost, int &dEnd)
{
    //suffixes
    for (const Replacement& suf : suffix) {
        int tmpPos = target.length() - suf.matchLength();
        if (tmpPos >= 0 && suf.tryReplacement(target, tmpPos, cost)) {
            dEnd = suf.matchLength();
            break;
        }
    }
}

void ApplyInfixes(std::string &target, int &pos, int &cost)
{
    //infixes
    bool hasMatch;
    do {
        hasMatch = false;
        //try applying prefix
        for (const Replacement& in : infix) {
            if (in.tryReplacement(target, pos, cost)) {
                hasMatch = true;
                break;
            }
        }
    } while (hasMatch);
}
