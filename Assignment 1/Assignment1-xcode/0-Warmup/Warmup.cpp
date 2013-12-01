//
//  Warmup.cpp
//  Warmup
//
//  Created by Adam Li on 9/4/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "stack.h"
#include "TokenScanner.h"

bool ProcessOpenTag(TokenScanner& scanner, Stack<string>& tagStack)
{
    string tag = scanner.nextToken();
    tagStack.push(tag);
    return true;
}
bool ProcessCloseTag(TokenScanner& scanner, Stack<string>& tagStack)
{
    string tag = scanner.nextToken();
    if (!tagStack.isEmpty() && tag == tagStack.pop()) {
        return true;
    }else {
        return false;
    } }
bool ProcessTag(TokenScanner& scanner, Stack<string>& tagStack)
{
    // read the next token to see if we found an
    // opening or closing tag
    string token = scanner.nextToken();
    if (token == "/")
    {
        return ProcessCloseTag(scanner, tagStack);
    }
    else {
        scanner.saveToken(token); //So ProcessOpenTag can use it
        return ProcessOpenTag(scanner, tagStack);
    }
}
bool IsCorrectlyNested(string htmlStr)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    Stack<string> tagStack;
    scanner.setInput(htmlStr);
    // start by assuming it is balanced
    bool isBalanced = true;
    while (scanner.hasMoreTokens())
    {
        string token = scanner.nextToken();
        if (token == "<")
        {
            if (!ProcessTag(scanner, tagStack))
            {
                isBalanced = false;
                break; }
            // get rid of ">" part of tag
            scanner.nextToken();
        }
    }
    if (!tagStack.isEmpty()) isBalanced = false;
    return isBalanced;
}

int main() {
    string htmlStr = "<abc><br>agbd</b></abc>";
    if (IsCorrectlyNested(htmlStr)) {
        cout << "it is correct." << endl;
    } else {
        cout << "it is incorrect." << endl;
    }
    return 0;
}