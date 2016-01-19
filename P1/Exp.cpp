#include <iostream>

using namespace std;

long fib (int);

int main()
{
	cout << fib (50);
	return 0;
}

long fib (int n)
{
	if (n <= 1 )
	{
		return 1;
	}
	else
		return fib(n-1) + fib(n-2);
}