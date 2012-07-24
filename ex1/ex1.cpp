#include "stdafx.h"

template <class T, T defaultVal=4, int dim=255> 
class Vec 
{ 
    T _vec[dim]; 
    int _dim; 
public: 
    Vec () : _dim(dim) 
    { 
        for (int i=0;i<_dim;++i) 
        { 
            _vec[i] = defaultVal; 
        } 
    } 
    ~Vec () {}; 
    // other operators and stuff 
}; 
int main () 
{ 
    const int defValue = 0; 
    Vec <int> vecWithDefVal;
	return 0;
}
