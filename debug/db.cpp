#include<bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> p)
{
    out << '(' << p.first << ", " << p.second << ')';
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, vector<T> v)
{
    out << '[';
    if (!v.empty())
        out << v[0];
    for (int i = 1; i < (int)v.size(); i++)
        out << ", " << v[i];
    out << ']';
    return out;
}

int main(){
    
}