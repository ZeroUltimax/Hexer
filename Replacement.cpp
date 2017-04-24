#include "stdafx.h"
#include "Replacement.h"
using zux::Replacement;

Replacement::Replacement(string match, string replace, int cost) :
    _match(match),
    _replace(replace),
    _cost(cost)
{}

bool Replacement::match(const string&s, int pos)const {
    return !s.compare(pos, _match.length(), _match); // compare returns 0 if equals
}

int Replacement::replace(string&s, int pos)const {
    s.replace(pos, _match.length(), _replace);
    return pos + _replace.length();
}

bool Replacement::tryReplacement(std::string &s, int &pos, int &cost)const
{
    if (!match(s, pos))
        return false;

    cost += _cost;
    pos = replace(s, pos);
    return true;
}

int Replacement::matchLength()const {
    return _match.length();
}