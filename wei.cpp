#include <iostream>
using namespace std;
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        /* 0xAAAAAAAA = 0b10101010101010101010101010101010 */
        /* 0x55555555 = 0b01010101010101010101010101010101 */
        n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
        cout<<n<<endl;
        /* 0xCCCCCCCC = 0b11001100110011001100110011001100 */
        /* 0x33333333 = 0b00110011001100110011001100110011*/
        n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
        cout<<n<<endl;
        /* 0xF0F0F0F0 = 0b11110000111100001111000011110000 */
        /* 0x0F0F0F0F = 0b00001111000011110000111100001111 */
        n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
        cout<<n<<endl;
        /* 0xFF00FF00 = 0b11111111000000001111111100000000 */
        /* 0x00FF00FF = 0b00000000111111110000000011111111 */
        n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
        cout<<n<<endl;
        /* 0xFFFF0000 = 0b11111111111111110000000000000000 */
        /* 0x0000FFFF = 0b00000000000000001111111111111111 */
        n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
        return n;
    }
    int hammingWeight(uint32_t n) {
        n = (n & 0x55555555) + ((n >> 1)  & 0x55555555);
        cout<<n<<endl;
        n = (n & 0x33333333) + ((n >> 2)  & 0x33333333);
        cout<<n<<endl;
        n = (n & 0x0f0f0f0f) + ((n >> 4)  & 0x0f0f0f0f);
        cout<<n<<endl;
        n = (n & 0x00ff00ff) + ((n >> 8)  & 0x00ff00ff);
        cout<<n<<endl;
        n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
        return n;

    }
};
int main(){
    uint32_t n=240;
    uint32_t result;
    int result32;
    Solution abc;
    result=abc.reverseBits(n);
    cout<<"next"<<endl;
    result32=abc.hammingWeight(n);
    cout<<result<<endl;
    cout<<result32<<endl;
    return 0;


}