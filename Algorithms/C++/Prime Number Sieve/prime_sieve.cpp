#include <bits/stdc++.h>
#define ll long long
using namespace std;

//Print number of prime numbers in range a to b using prime sieve.

int primes[1000001];  // prime sieve array of range 10^6


//Prints the primes in range a to b inclusive.
void print(ll a,ll b) {
    for(ll i=a;i<=b;i++) {
       if(primes[i]==1) {
           cout<<i<<" ";    
       }     
    }
}


// Generating prime sieve

void prime_sieve() {

    for(ll i=1;i<=1000000;i+=2){   //assuming all odd numbers to be prime
        primes[i]=1;
    }

    for(ll i=3;i<=1000000;i+=2) {   //iterate over all odd numbers 
        for(ll j=i*i;j<=1000000;j+=i) {   //marking all multiple of primes as not prime.
             if(primes[j]==1) {    //if a multiple of odd number is marked prime mark it as non-prime.
                primes[j]=0;
              }
        }
    }

    primes[2]=1;   //mark 2 as prime 
    primes[1]=primes[0]=0;  //mark 1 and 0 as not prime
}


int main() {
        prime_sieve();   //sieve generated
        ll a,b;
        cin>>a>>b;
        print(a,b);
        cout<<endl;
    return 0;
}
