#include <bits/stdc++.h>

using namespace std;

using lli = __int128_t;

lli fastexponentiation( lli a, lli n){
    lli acum = a;
    lli result = 1;
    while(n != 0){
        if(n & 1){
            result *= acum;
        }
        acum *= acum;
        n >>= 1;
    }
    return result;
}

ostream &operator<<(ostream &os, const __int128 & value){
    char buffer[64];
    char *pos = end(buffer) - 1;
    *pos = '\0';
    __int128 tmp = value < 0 ? -value : value;
    do{
        --pos;
        *pos = tmp % 10 + '0';
        tmp /= 10;
    }while(tmp != 0);
    if(value < 0){
        --pos;
        *pos = '-';
    }
    return os << pos;
}

int main(){
    cout << pow(12,8) << '\n';
    cout << (fastexponentiation(12,8)) << '\n';
    return 0;
}