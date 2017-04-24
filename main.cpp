#include "stdafx.h"
#include <string>
#include "Hexer.h"

int main()
{
    string input;
    while (cin >> input) {
        zux::Hexer::transmogrify(input);
    }
    return 0;
}

