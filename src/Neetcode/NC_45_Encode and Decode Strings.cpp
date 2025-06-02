#include <bits/stdc++.h>
#define ll long long
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007
#define eps 1e-6

using namespace std;

typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef map<char, int> mci;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef map<int, int> mii;


/*
================================================================================
                                Problem Description
================================================================================

Problem: NC_45_Encode and Decode Strings
Topic: Hashing
Link: https://neetcode.io/problems/string-encode-and-decode

================================================================================
                                Problem Summary
================================================================================

Design an algorithm to encode a list of strings into a single string and decode it back to the original list.
The encoded string must be able to handle any characters, including delimiters like commas and special symbols.

You must implement two methods:
- `string encode(vector<string>& strs)`
- `vector<string> decode(string s)`

================================================================================
                                Intuition & Explanation
================================================================================

### Goal:
We need to encode multiple strings into one string in a reversible and unambiguous manner.

### 🔐 Encoding Strategy:
- For each string, store its length.
- Append all lengths separated by commas (`,`) followed by a delimiter (e.g. `#`) that separates the metadata from actual string content.
- After the delimiter, concatenate all strings in order.

✅ Example:
For `["cat", "hi", "a"]`
- Lengths: `"3,2,1,"`
- Content: `"cathi a"`
- Encoded string: `"3,2,1,#cathia"`

### 🔓 Decoding Strategy:
- Parse the string before `#` to retrieve lengths.
- Use these lengths to extract substrings from the second half of the encoded string.

📌 Important:
- This method avoids issues with strings containing commas or special characters.
- It ensures proper restoration of the original list regardless of content.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Let N = number of strings and E = total number of characters across all strings.

🔹 Approach: Hashing/Index Tracking
Time Complexity: O(N + E)
Space Complexity: O(N + E)

================================================================================
                                Code Implementation
================================================================================
*/

class Solution {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        if (strs.empty()) return "";

        string res;
        vector<int> sizes;

        // Collect lengths of each string
        for (const string& s : strs) {
            sizes.push_back(s.size());
        }

        // Append lengths to the result
        for (int len : sizes) {
            res += to_string(len) + ',';
        }

        // Add a unique delimiter
        res += '#';

        // Append all strings
        for (const string& s : strs) {
            res += s;
        }

        return res;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        if (s.empty()) return {};

        vector<int> sizes;
        vector<string> res;
        int i = 0;

        // Parse lengths from the encoded string
        while (s[i] != '#') {
            string num;
            while (s[i] != ',') {
                num += s[i];
                i++;
            }
            sizes.push_back(stoi(num));
            i++; // Skip the comma
        }

        i++; // Skip the '#' delimiter

        // Use lengths to extract each original string
        for (int len : sizes) {
            res.push_back(s.substr(i, len));
            i += len;
        }

        return res;
    }
};
