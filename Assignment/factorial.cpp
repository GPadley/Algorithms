#include <iostream>
#include <string>

using namespace std;

int fact(int nin);

int main(){
    cout << "Enter value you would like the factorial of:" << endl;
    int x, factorial;
    cin >> x;

    factorial = fact(x);
    cout << x << " factorial is: " << factorial << endl;
}

int fact(int nin){
    if(nin <= 1){
        return 1;
    }
    else {
        return(nin*fact(nin-1));
    }
}
