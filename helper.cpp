#include <bits/stdc++.h>

using namespace std;

enum verdict
{
	MODUS_PONANS,
	EVERY,
	EXIST,
	ASSUMPTION,
	AXIOM_SCHEME,
	AXIOM,
	ERROR
};

int main()
{
	freopen("comment_for_exist", "r", stdin);
	freopen("output", "w", stdout);

	for (int i = 0; i < 106; i++)
	{
		string s;
		cin >> s;
		cerr << s << endl;
		if (s == "Assumption")
		{
			int a;
			cin >> a;
			cout << ASSUMPTION << ' ' << a - 1 << ' ' << -1 << endl;
		}
		if (s == "M.P.")
		{
			int a, b;
			cin >> a >> b;
			cout << MODUS_PONANS << ' ' << a - 1 << ' ' << b - 1 << endl;
		}
		if (s == "Axiom_scheme")
		{
			int a;
			cin >> a;
			cout << AXIOM_SCHEME << ' ' << a << ' ' << -1 << endl;
		}
		if (s == "Every")
		{
			int a;
			cin >> a;
			cout << EVERY << ' ' << a - 1 << ' ' << -1 << endl;
		}
		if (s == "Exist")
		{
			int a;
			cin >> a;
			cout << EXIST << ' ' << a - 1 << ' ' << -1 << endl;
		}
	}

	return 0;
}
