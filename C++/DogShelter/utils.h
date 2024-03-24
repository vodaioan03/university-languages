#pragma once

#include <iostream>
#include <string>

using namespace std;
/// <summary>
/// Transform a string to lower value
/// </summary>
/// <param name="stringCombine"></param>
void toLower(string& stringCombine);
/// <summary>
/// Delete all spaces from a given string
/// </summary>
/// <param name="stringCombine"></param>
void delSpaces(string& stringCombine);
/// <summary>///Compare 2 strings without spaces and lower cases /// </summary>/// <param name="firstString"></param>/// <param name="secondString"></param>/// <returns></returns>
bool compareLower(string firstString, string secondString);