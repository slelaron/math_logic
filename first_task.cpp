#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string s;
const int INF = 1e9 + 7;
const int simple = 4673;
const int maxN = 100009;

string axioms[] = {"-A)-B)A)", "--A)B)--A)-B)C)-A)C)", "-A)-B)&A)B)", "-&A)B)A)", "-&A)B)B)", "-A)|A)B)", "-B)|A)B)", "--A)C)--B)C)-|A)B)C)", "--A)B)--A)!B)!A)", "-!!A)A)"};

long long power[1000009];

const string characters[] = {"&", "|", "-", "!"};
const char symbols[] = {'&', '|', '-', '!'};
int positions['z' - 'a' + 1];

size_t pointer1 = 0;
vector <int> for_hash;

struct operation 
{
	virtual string print() = 0;
	virtual short id() = 0;
	virtual bool check_on_structure(string& s) = 0;
	virtual int get_left() = 0;
	virtual int get_right() = 0;
	size_t length = 0;
	unsigned long long hash = 0;
	virtual ~operation()
	{}
};

struct expression
{	
	string str;
	size_t pointer;
	operation* op;
	size_t check_on_axiom();
	size_t check_on_suppose();
	operation* first_act();
	operation* second_act();
	operation* third_act();
	operation* forth_act();
	expression(string const& _str): 
		str(_str),
		pointer(0)
	{
		op = first_act();
		//cout << "Hay!" << endl;
	}
	int get_left()
	{
		return op->get_left();
	}
	int get_right()
	{
		return op->get_right();
	}
	int get_hash()
	{
		return op->hash;
	}
	~expression()
	{
		delete op;
	}
	expression(expression const& a):
		str(a.str),
		pointer(0),
		op(a.op)
	{
		cout << "Here!" << endl;
	}
};

struct bin_operation: operation
{
	operation *l, *r;
	
	
	bool check_on_structure(string& s)
	{
		//cout << s << ' ' << pointer1 << ' ' << characters[id()] << " " << s[pointer1] << endl;
		if ('A' <= s[pointer1] && s[pointer1] <= 'Z')
		{
			for_hash.push_back(hash);
			while (s[pointer1] != ')')
				pointer1++;
			pointer1++;
			return true;
		}
		else if (symbols[id()] != s[pointer1])
			return false;
		else
		{
			pointer1++;
			if (l->check_on_structure(s) && r->check_on_structure(s))
			{
				return true;
			}
			return false;	
		}
	}
	
	int get_left()
	{
		return -1;
	}
	
	int get_right()
	{
		return -1;
	}
	
	string print()
	{
		return characters[id()] + l->print() + r->print();
	}
	
	virtual ~bin_operation()
	{
		delete l;
		delete r;
	}
};

struct unary_operation: operation
{
	operation *next;
	
	bool check_on_structure(string& s)
	{
		//cout << s << ' ' << pointer1 << ' ' << characters[id()] << " " << s[pointer1] << endl;
		if ('A' <= s[pointer1] && s[pointer1] <= 'Z')
		{
			for_hash.push_back(hash);
			while (s[pointer1] != ')')
				pointer1++;
			pointer1++;
			return true;
		}	
		else if (symbols[id()] != s[pointer1])
			return false;
		else
		{
			pointer1++;
			return next->check_on_structure(s);
		}
	}
	
	int get_left()
	{
		return -1;
	}
	
	int get_right()
	{
		return -1;
	}
	
	virtual ~unary_operation()
	{
		delete next;
	}
};

struct conjunction: bin_operation
{
	short id() {return 0;}
	conjunction(operation* _l, operation* _r)
	{
		l = _l;
		r = _r;
		length = l->length + r->length + 1;
		hash = ('&' * power[l->length + r->length] % INF + l->hash * power[r->length] % INF + r->hash) % INF;
		//cout << hash << endl;
	}
	~conjunction()
	{}
};

struct disjunction: bin_operation
{
	short id() {return 1;}
	disjunction(operation* _l, operation* _r)
	{
		l = _l;
		r = _r;
		length = l->length + r->length + 1;
		hash = ('|' * power[l->length + r->length] % INF + l->hash * power[r->length] % INF + r->hash) % INF;
		//cout << hash << endl;
	}
	~disjunction()
	{}
};

struct consequence: bin_operation
{
	short id() {return 2;}
	consequence(operation* _l, operation* _r)
	{
		l = _l;
		r = _r;
		length = l->length + r->length + 1;
		hash = ('-' * power[l->length + r->length] % INF + l->hash * power[r->length] % INF + r->hash) % INF;
		//cout << hash << endl;
	} 
	int get_left()
	{
		return l->hash;
	}
	
	int get_right()
	{
		return r->hash;
	}
	~consequence()
	{}
};

struct variable: operation
{
	short id() {return 4;}
	string name;
	bool check_on_structure(string& s)
	{
		//cout << s << ' ' << pointer1 << ' ' << name << " (" << hash << " ) " << s[pointer1] << endl;
		if ('A' <= s[pointer1] && s[pointer1] <= 'Z')
		{
			while (s[pointer1] != ')')
				pointer1++;
			pointer1++;
			for_hash.push_back(hash);
			//cout << "Hyu!" << endl;
			return true;
		}
		return false;
	}
	variable(string& _name): name(_name)
	{
		length = name.size();
		hash = 0;
		for (size_t i = 0; i < name.size(); i++)
		{
			hash = ((hash * simple) % INF + name[i]) % INF;
		}
		//cout << hash << endl;
	}
	
	int get_left()
	{
		return -1;
	}
	
	int get_right()
	{
		return -1;
	}
	
	~variable()
	{}
	
	string print()
	{
		return name + ')';
	}
};

struct _negate: unary_operation
{
	short id() {return 3;}
	_negate(operation* _next)
	{
		next = _next;
		length = length + 1;
		hash = ('!' * power[_next->length] % INF + _next->hash) % INF;
		//cout << hash << endl;
	}
	string print()
	{
		return "!" + next->print();
	}
	_negate()
	{}
};

operation* expression::forth_act()
{
	//cout << "Forth act" << endl;
	if (pointer < str.size() && str[pointer] == '!')
	{
		pointer++;
		return new _negate(forth_act());
	}
	else if (pointer < str.size() && str[pointer] == '(')
	{
		pointer++;
		operation* op = first_act();
		pointer++;
		return op;
	}
	else 
	{
		string buf = "";
		while (pointer < str.size() && (('A' <= str[pointer] && str[pointer] <= 'Z') || ('0' <= str[pointer] && str[pointer] <= '9')))
		{
			buf += str[pointer];
			pointer++;
		}	
		return new variable(buf);
	}
}

operation* expression::third_act()
{
	//cout << "Third act" << endl;
	operation* op = forth_act();
	while (pointer < str.size() && str[pointer] == '&')
	{
		pointer++;
		op = new conjunction(op, forth_act());
	}
	return op;
}

operation* expression::second_act()
{
	//cout << "Second act" << endl;
	operation* op = third_act();
	while (pointer < str.size() && str[pointer] == '|')
	{
		pointer++;
		op = new disjunction(op, third_act());
	}
	return op;
}

operation* expression::first_act()
{
	//cout << "First act" << endl;
	operation* op = second_act();
	if (pointer + 1 < str.size() && str[pointer] == '-' && str[pointer + 1] == '>')
	{
		pointer += 2;
		return new consequence(op, first_act());
	}
	return op;
}

size_t expression::check_on_axiom()
{
	for (int i = 0; i < 10; i++)
	{
		pointer1 = 0;
		for_hash.clear();
		for (int i = 0; i < 'z' - 'a' + 1; i++)
		{
			positions[i] = -1;
		}
		if (op->check_on_structure(axioms[i]))
		{
			bool truth = true;
			int nxt = 0;
			for (size_t j = 0; j < axioms[i].size();)
			{
				if ('A' <= axioms[i][j] && axioms[i][j] <= 'Z')
				{
					if (positions[axioms[i][j] - 'A'] == -1)
					{
						positions[axioms[i][j] - 'A'] = for_hash[nxt];
					}
					else if (positions[axioms[i][j] - 'A'] != for_hash[nxt])
					{
						truth = false;
						break;
					}
					while (axioms[i][j] != ')')
					{
						j++;
					}
					j++;
					nxt++;
				}
				else
					j++;
			}
			if (truth)
				return i;
		}
	}
	return -1;
}


vector <string> supposes;
vector <pair <int, pair <int, int> > > ans(maxN, make_pair(-1, make_pair(-1, -1)));

size_t expression::check_on_suppose()
{
	for (size_t i = 0; i < supposes.size(); i++)
	{
		pointer1 = 0;
		for_hash.clear();
		if (op->check_on_structure(supposes[i]))
		{
			int nxt = 0;
			bool truth = true;
			for (size_t j = 0; j < supposes[i].size();)
			{
				if ('A' <= supposes[i][j] && supposes[i][j] <= 'Z')
				{
					int hash = 0;
					while (supposes[i][j] != ')')
					{
						hash = ((hash * simple) % INF + supposes[i][j]) % INF;
						j++;
					}
					j++;
					if (hash != for_hash[nxt])
					{
						truth = false;
						break;
					}
					nxt++;
				}
				else
					j++;
			}
			if (truth)
			{
				return i;
			}
		}
	}
	return -1;
}

//map <int, size_t> mp;
vector <expression*> expr;
map <int, size_t> first_passage;
map <int, size_t> second_passage;
map <int, size_t> third_passage;
map <int, size_t> forth_passage;
vector <int> have_mp(maxN, -1);
vector <int> have_mp1(maxN, -1);

int main()
{
	//FILE* input = freopen("input", "r", stdin);
	//FILE* output = freopen("output", "w", stdout);

	setlocale(LC_ALL, "Russian");
	
	power[0] = 1;
	for (int i = 1; i < maxN; i++)
	{
		power[i] = (long long)(power[i - 1] * simple) % INF;
	}

	string str;
	string header;
	string last = "";
	cin >> header;
	{
		size_t i = 0;
		for (; header[i] != '|' || header[i + 1] != '-'; i++)
		{
			//cout << i << endl;
			string s = "";
			for (;header[i] != ',' && (header[i] != '|' || header[i + 1] != '-'); i++)
			{
				//cout << "^ " << i << endl;
				s += header[i];
			}
			supposes.push_back(expression(s).op->print());
			if (header[i] == '|' && header[i + 1] == '-')
				i--;
		}
		//cout << "Hello!" << endl;
		//for (size_t j = 0; j < supposes.size(); j++)
			//cout << supposes[j] << endl;
		i += 2;
		for (; i < header.size(); i++)
		{
			last += header[i];
		}
		//cout << last << endl;
	}
	do
	{
		cin >> str;
		//cout << a.op->print() << endl;
		expr.push_back(new expression (str));
	} while (str != last);
	
	for (size_t i = 0; i < expr.size(); i++)
	{
		int res = expr[i]->check_on_suppose();
		if (res != -1)
		{
			ans[i] = make_pair(1, make_pair(res, -1));
		}
	}
	for (size_t i = 0; i < expr.size(); i++)
	{
		int l = expr[i]->get_left();
		if (l != -1)
		{
			if (first_passage.find(l) != first_passage.end())
			{
				have_mp[i] = first_passage[l];
			}
		}
		first_passage[expr[i]->get_hash()] = i;
	}
	for (size_t i = 0; i < expr.size(); i++)
	{
		int that = expr[i]->get_hash();
		if (that != -1)
		{
			if (second_passage.find(that) != second_passage.end())
			{
				int number = second_passage[that];
				if (ans[i].first == -1)
					ans[i] = make_pair(2, make_pair(have_mp[number], number));
			}
		}
		int r = expr[i]->get_right();
		if (have_mp[i] != -1 && r != -1)
		{
			second_passage[r] = i;
		}
	}
	for (int i = expr.size() - 1; i >= 0; i--)
	{
		int l = expr[i]->get_left();
		if (l != -1)
		{
			if (third_passage.find(l) != third_passage.end())
			{
				have_mp1[i] = third_passage[l];
			}
		}
		third_passage[expr[i]->get_hash()] = i;
	}
	for (size_t i = 0; i < expr.size(); i++)
	{
		int that = expr[i]->get_hash();
		if (that != -1)
		{
			if (forth_passage.find(that) != forth_passage.end())
			{
				int number = forth_passage[that];
				if (ans[i].first == -1 && have_mp1[number] < (int)i)
					ans[i] = make_pair(2, make_pair(have_mp1[number], number));
			}
		}
		int r = expr[i]->get_right();
		if (have_mp1[i] != -1 && r != -1)
		{
			forth_passage[r] = i;
		}
	}
	for (size_t i = 0; i < expr.size(); i++)
	{
		int res = expr[i]->check_on_axiom();
		if (res != -1)
		{
			if (ans[i].first == -1)
				ans[i] = make_pair(0, make_pair(res, -1));
		}
	}
	cout << header << '\n';
	for (size_t i = 0; i < expr.size(); i++)
	{
		cout << '(' << i + 1 << ") " << expr[i]->str << " (";
		switch (ans[i].first)
		{
			case -1:
				//cout << "Not shown";
				cout << "Не доказано";
				break;
			case 0:
				cout << "Сх. акс. " << ans[i].second.first + 1;
				break;
			case 1:
				cout << "Предп. " << ans[i].second.first + 1;
				break;
			case 2:
				cout << "M.P. " << ans[i].second.first + 1 << ", " << ans[i].second.second + 1;
				break;
		}
		cout << ")\n";
	}
	for (size_t i = 0; i < expr.size(); i++)
	{
		delete expr[i];
	}
	
	//fclose(input);
	//fclose(output);

	return 0;	
}
