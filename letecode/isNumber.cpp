#include <iostream>
//#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
#if 0
class Solution {
public:
    enum State{
        STATE_INITIAL,
        STATE_INT_SIGN,
        STATE_INTEGER,
        STATE_POINT,
        STATE_POINT_WITHOUT_INT,
        STATE_FRACTION,
        STATE_EXP,
        STATE_EXP_SIGN,
        STATE_EXP_NUMBER,
        STATE_END
    };
    enum CharType{
        CHAR_NUMBER,
        CHAR_EXP,
        CHAR_POINT,
        CHAR_SIGN,
        CHAR_ILLEGAL
    };
    CharType toCharTypr(char ch){
        if(ch>='0'&&ch<='9')
        {
            return CHAR_NUMBER;
        }else if(ch=='e'||ch=='E')
        {
            return CHAR_EXP;
        }else if(ch=='.')
        {
            return CHAR_POINT;
        }else if(ch=='+'||ch=='-'){
            return CHAR_SIGN;
        }else{
            return CHAR_ILLEGAL;
        }
    }
    bool isNumber(string s) {
        unordered_map<State,unordered_map<CharType,State>> transfer{
            {
                STATE_INITIAL,{
                    {CHAR_NUMBER,STATE_INTEGER},
                    {CHAR_POINT,STATE_POINT_WITHOUT_INT},
                    {CHAR_SIGN,STATE_INT_SIGN}
                }
            },{
                STATE_INT_SIGN,{
                    {CHAR_NUMBER,STATE_INTEGER},
                    {CHAR_POINT,STATE_POINT_WITHOUT_INT}
                }
            },{
                STATE_INTEGER,{
                    {CHAR_NUMBER,STATE_INTEGER},
                    {CHAR_EXP,STATE_EXP},
                    {CHAR_POINT,STATE_POINT}
                }
            },{
                STATE_POINT,{
                    {CHAR_NUMBER,STATE_FRACTION},
                    {CHAR_EXP,STATE_EXP}
                }
            },{
                STATE_POINT_WITHOUT_INT,{
                    {CHAR_NUMBER,STATE_FRACTION}
                }
            },{
                STATE_FRACTION,{
                    {CHAR_NUMBER,STATE_FRACTION},
                    {CHAR_EXP,STATE_EXP}
                }
            },{
                STATE_EXP,{
                    {CHAR_NUMBER,STATE_EXP_NUMBER},
                    {CHAR_SIGN,STATE_EXP_SIGN}
                }
            },{
                STATE_EXP_SIGN,{
                    {CHAR_NUMBER,STATE_EXP_NUMBER}
                }
            },{
                STATE_EXP_NUMBER,{
                    {CHAR_NUMBER,STATE_EXP_NUMBER}
                }
            }
        };
        int len=s.length();
        State st=STATE_INITIAL;
        for(int i=0;i<len;i++){
            CharType typ=toCharTypr(s[i]);
            if(transfer[st].find(typ)==transfer[st].end())
            {
                return false;
            }else{
                st=transfer[st][typ];
            }
        }
        return st==STATE_INTEGER||st==STATE_POINT||st==STATE_FRACTION||st==STATE_EXP_NUMBER||st==STATE_END;
    }
};
#endif
#if 1
class Solution {
public:
    bool isNumber(string s) {
        std::vector<std::unordered_map<char, int>> states = {
            { {' ', 0}, {'s', 1}, {'d', 2}, {'.', 4} },  // 0. start with 'blank'
            { {'d', 2}, {'.', 4} },                      // 1. 'sign' before 'e'
            { {'d', 2}, {'.', 3}, {'e', 5}, {' ', 8} },  // 2. 'digit' before 'dot'
            { {'d', 3}, {'e', 5}, {' ', 8} },            // 3. 'digit' after 'dot'
            { {'d', 3} },                                // 4. 'digit' after 'dot' (‘blank’ before 'dot')
            { {'s', 6}, {'d', 7} },                      // 5. 'e'
            { {'d', 7} },                                // 6. 'sign' after 'e'
            { {'d', 7}, {' ', 8} },                      // 7. 'digit' after 'e'
            { {' ', 8} }                                 // 8. end with 'blank'
        };

        int p = 0;                                       // start with state 0
        for (char c : s) {
            char t;
            if (c >= '0' && c <= '9') t = 'd';           // digit
            else if (c == '+' || c == '-') t = 's';      // sign
            else if (c == 'e' || c == 'E') t = 'e';      // e or E
            else if (c == '.' || c == ' ') t = c;        // dot, blank
            else t = '?';                                // unknown

            if (states[p].count(t) == 0) return false;
            p = states[p][t];
        }
        return p == 2 || p == 3 || p == 7 || p == 8;
    }
};
#endif
int main()
{
    string s="2324.23e+1";
    bool ab;
    Solution abc;
    ab=abc.isNumber(s);
    return 0;
}