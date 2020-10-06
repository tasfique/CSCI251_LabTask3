#include <iostream>
#include <deque>
#include <iterator>
using namespace std;

int main()
{
	deque <int> scores;

	for(int i=0; i<5; i++)
	{
		int score;
		cout << "Input a score : ";
		cin >> score;
		if(score >= 50)
		{
			scores.push_back(score);
		}
		else
		{
			scores.push_front(score);
		}
	}
	deque<int>::iterator iter;
	for(iter=scores.begin(); iter!=scores.end(); ++iter)
	{
		cout << iter* << "\t";
	}
	cout << endl;

	return 0;
}
