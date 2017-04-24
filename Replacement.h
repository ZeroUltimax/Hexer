#pragma once
namespace zux {
    class Replacement {
        string _match, _replace;
        int _cost;

    public:
        Replacement(string match, string replace, int cost);
        bool match(const string&s, int pos)const;
        int replace(string&s, int pos)const;
        bool tryReplacement(std::string &s, int &pos, int &cost)const;
        int matchLength()const;
    };
}