#include <bits/stdc++.h>
#include "my_big_library.h"

using namespace std;

string prelude[266];
string some_theorem[71];

void get_prelude()
{
	FILE* input = freopen("another_change", "r", stdin);

	for (int i = 0; i < 266; i++)
	{
		cin >> prelude[i];
	}

	fclose(input);
}

void get_some_theorem()
{
	FILE* input = freopen("some_theorem", "r", stdin);

	for (int i = 0; i < 71; i++)
	{
		cin >> some_theorem[i];
	}

	fclose(input);
}

string get_null(int a)
{
	string res = "0";
	for (int i = 0; i < a; i++)
	{
		res += '\'';
	}
	return res;
}

string substitute_str(string& s, map <char, string>& str)
{
	string ans = "";
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '_')
		{
			ans += str[s[i + 1]];
			i++;
		}
		else
		{
			ans += s[i];
		}
	}
	return ans;
}

void get_evidence(const string& s, vector <string>& to_add)
{
	cout << s << '\n';
	cout << "0=0->0=0->0=0\n";
	cout << "(" << s << ")->(0=0->0=0->0=0)->(" << s << ")\n";
	cout << "(0=0->0=0->0=0)->(" << s << ")\n";
	string s1 = "(" + s + ")";
	for (size_t i = 0; i < to_add.size(); i++)
	{
		cout << "(0=0->0=0->0=0)->" << s1 << '\n';
		s1 = "@" + to_add[i] + s1;
		cout << "(0=0->0=0->0=0)->" << s1 << '\n';
	}
	cout << s1 << '\n';
}

void make_something_good(int a, int b)
{
	for (int i = 0; i < 266; i++)
	{
		cout << prelude[i] << '\n';
	}
	vector <string> to_add;
	to_add.push_back("a");
	get_evidence("a+0=a", to_add);
	to_add.pop_back();
	to_add.push_back("b");
	to_add.push_back("a");
	get_evidence("a+b'=(a+b)'", to_add);
	get_evidence("a=b->a'=b'", to_add);
	get_evidence("a'=b'->a=b", to_add);
	string op1 = "@a@b@c(b=a->a=c->b=c)->@b@c(b=_d->_d=c->b=c)";
	string op1_1 = "@b@c(b=_d->_d=c->b=c)";
	string op2 = "@b@c(b=_d->_d=c->b=c)->@c(_e=_d->_d=c->_e=c)";
	string op2_1 = "@c(_e=_d->_d=c->_e=c)";
	string op3 = "@c(_e=_d->_d=c->_e=c)->(_e=_d->_d=_f->_e=_f)";
	string op3_1 = "_e=_d->_d=_f->_e=_f";
	string op4 = "_d=_f->_e=_f";
	string op5 = "_e=_f";
	string before1 = "@a@b(a+b'=(a+b)')->@b(_d+b'=(_d+b)')";
	string before1_1 = "@b(_d+b'=(_d+b)')";
	string before2 = "@b(_d+b'=(_d+b)')->(_d+_e'=(_d+_e)')";
	string before2_1 = "_d+_e'=(_d+_e)'";
	map <char, string> mp;
	for (int i = 0; i < b - a; i++)
	{
		mp['d'] = get_null(a);
		mp['e'] = get_null(b - a - i - 1);
		cout << substitute_str(before1, mp) << '\n';
		cout << substitute_str(before1_1, mp) << '\n';
		cout << substitute_str(before2, mp) << '\n';
		cout << substitute_str(before2_1, mp) << '\n';
	}
	string smth = "@a(a+0=a)->(_d+0=_d)";
	string smth1 = "_d+0=_d";
	mp['d'] = get_null(a);
	cout << substitute_str(smth, mp) << '\n';
	cout << substitute_str(smth1, mp) << '\n';
	string middle1 = "@a@b(a=b->a'=b')->@b(_r=b->_r'=b')";
	string middle1_1 = "@b(_r=b->_r'=b')";
	string middle2 = "@b(_r=b->_r'=b')->(_r=_k->_r'=_k')";
	string middle2_1 = "_r=_k->_r'=_k'";
	string middle3 = "_r'=_k'";
	for (int i = 0; i < b - a; i++)
	{
		mp['e'] = get_null(a) + "+" + get_null(i + 1);
		mp['d'] = "(" + get_null(a) + "+" + get_null(i) + ")'";
		mp['f'] = get_null(a + i + 1);
		mp['k'] = get_null(a + i);
		mp['r'] = "(" + get_null(a) + "+" + get_null(i) + ")";
		cout << substitute_str(op1, mp) << '\n';
		cout << substitute_str(op1_1, mp) << '\n';
		cout << substitute_str(op2, mp) << '\n';
		cout << substitute_str(op2_1, mp) << '\n';
		cout << substitute_str(op3, mp) << '\n';
		cout << substitute_str(op3_1, mp) << '\n';
		cout << substitute_str(middle1, mp) << '\n';
		cout << substitute_str(middle1_1, mp) << '\n';
		cout << substitute_str(middle2, mp) << '\n';
		cout << substitute_str(middle2_1, mp) << '\n';
		cout << substitute_str(middle3, mp) << '\n';
		cout << substitute_str(op4, mp) << '\n';
		cout << substitute_str(op5, mp) << '\n';
	}
	cout << get_null(a) << "+" << get_null(b - a) << "=" << get_null(b) << "->" << "?p(" << get_null(a) << "+p=" << get_null(b) << ")\n";
	cout << "?p(" << get_null(a) << "+p=" << get_null(b) << ")\n";
}

void make_something_bad(int a, int b)
{
	for (int i = 0; i < 266; i++)
	{
		cout << prelude[i] << '\n';
	}
	vector <string> to_add;
	to_add.push_back("a");
	get_evidence("!(a'=0)", to_add);
	cout << "@a!(a'=0)->!((" << get_null(a - b - 1) << "+p)'=0)\n";
	cout << "!(" << get_null(a - b - 1) << "+p)'=0\n";
	string op0 = "@e@c(c'+p=e->(c+p)'=e)->@c(c'+p=_t->(c+p)'=_t)";
	string op0_0 = "@c(c'+p=_t->(c+p)'=_t)";
	string op0_1 = "@c(c'+p=_t->(c+p)'=_t)->(_r'+p=_t->(_r+p)'=_t)";
	string op2 = "(_r'+p=_t->(_r+p)'=_t)";
	string op3 = "!(_r+p)'=_t->_r'+p=_t->!(_r+p)'=_t";
	string op4 = "_r'+p=_t->!(_r+p)'=_t";
	string op5 = "(_r'+p=_t->(_r+p)'=_t)->(_r'+p=_t->!(_r+p)'=_t)->!_r'+p=_t";
	string op6 = "(_r'+p=_t->!(_r+p)'=_t)->!_r'+p=_t";
	string op7 = "!_r'+p=_t";
	string op8 = "@a@b(!(a=b)->!(a'=b'))->@b(!((_r+p)=b)->!((_r+p)'=b'))";
	string op9 = "@b(!((_r+p)=b)->!((_r+p)'=b'))";
	string op10 = "@b(!((_r+p)=b)->!((_r+p)'=b'))->!((_r+p)=_t)->!((_r+p)'=_t')";
	string op11 = "!((_r+p)=_t)->!((_r+p)'=_t')";
	string op12 = "!((_r+p)'=_t')";
	map <char, string> mp;
	for (int i = 0; i < b + 1; i++)
	{
		mp['r'] = get_null(a - b + i - 1);
		mp['t'] = get_null(i);
		cout << substitute_str(op0, mp) << '\n';
		cout << substitute_str(op0_0, mp) << '\n';
		cout << substitute_str(op0_1, mp) << '\n';
		cout << substitute_str(op2, mp) << '\n';
		cout << substitute_str(op3, mp) << '\n';
		cout << substitute_str(op4, mp) << '\n';
		cout << substitute_str(op5, mp) << '\n';
		cout << substitute_str(op6, mp) << '\n';
		cout << substitute_str(op7, mp) << '\n';
		if (i != b)
		{
			mp['r'] = get_null(a - b + i);
			cout << substitute_str(op8, mp) << '\n';
			cout << substitute_str(op9, mp) << '\n';
			cout << substitute_str(op10, mp) << '\n';
			cout << substitute_str(op11, mp) << '\n';
			cout << substitute_str(op12, mp) << '\n';
		}
	}
	mp['b'] = get_null(a) + "+p=" + get_null(b);
	mp['a'] = "(0=0->0=0->0=0)";
	for (int i = 0; i < 71; i++)
	{
		cout << substitute_str(some_theorem[i], mp) << '\n';
	}
	mp['b'] = get_null(a) + "+p=" + get_null(b);
	mp['a'] = "!(0=0->0=0->0=0)";
	for (int i = 0; i < 71; i++)
	{
		cout << substitute_str(some_theorem[i], mp) << '\n';
	}
	string ans = "!" + get_null(a) + "+p=" + get_null(b);
	cout << ans << "->(0=0->0=0->0=0)->" << ans << '\n';
	cout << "(0=0->0=0->0=0)->" << ans << '\n';
	cout << ans << "->!(0=0->0=0->0=0)->" << ans << '\n';
	cout << "!(0=0->0=0->0=0)->" << ans << '\n';
	ans = get_null(a) + "+p=" + get_null(b);
	cout << ans << "->!(0=0->0=0->0=0)\n";
	cout << ans << "->!!(0=0->0=0->0=0)\n";
	string s1 = "?p(" + ans + ")->!(0=0->0=0->0=0)";
	string s2 = "?p(" + ans + ")->!!(0=0->0=0->0=0)";
	cout << s1 << '\n' << s2 << '\n';
	cout << "(" << s1 << ")->(" << s2 << ")->!?p(" << ans << ")\n";
	cout << "(" << s2 << ")->!?p(" << ans << ")\n";
	cout << "!?p(" << ans << ")\n";
}

int main()
{
	get_prelude();
	get_some_theorem();
	FILE* input = freopen("input", "r", stdin);
	FILE* output = freopen("output", "w", stdout);
	
	int a, b;
	//cout << get_exp("@a@b@c(b=a->a=c->b=c)->@b@c(b=(0'''+0)'->(0'''+0)'=c->b=c)")->print() << endl;
	//cout << get_exp("(0'''+0)'=c")->print() << endl;
	cin >> a >> b;
	if (a <= b)
	{
		make_something_good(a, b);
	}
	else
	{
		make_something_bad(a, b);
	}

	fclose(input);
	fclose(output);
	return 0;
}
