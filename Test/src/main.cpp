#include<iostream>
#include<vector>
#include<cassert>
#include<fstream>
#include<list>
#include<deque>
#include<array>
#include<forward_list>
#include<stack>
#include<map>
#include<unordered_map>
#include<algorithm>
#include<numeric>
#include<functional>
#include<set>
#include<string>
#include<stdio.h>
#include<sstream>
#include<memory>
#include<utility>

using namespace std;
using namespace std::placeholders;

class Employee {
	static int all;
	string name;
	int num;
public:
	Employee() :num(all++) {}
	Employee(const string s) :name(s), num(all++) {}
	Employee(const Employee& e) :name(e.name), num(all++) {}
	Employee& operator=(Employee& e) {
		name = e.name;
		return *this;
	}
};
size_t hasher(const string& s) {
	return hash<string>()(s);
}
void wordChange(ifstream& rule, ifstream& beg, decltype(hasher)* f) {
	string key, value;
	unordered_map<string, string, decltype(hasher)*>change(20, f);
	while (rule >> key && getline(rule, value)) {
		if (value.size() > 1) {
			change[key] = value.substr(1);
		}
		else {
			throw runtime_error("no value");
		}
	}
	string lin;
	while (getline(beg, lin)) {
		istringstream str(lin);
		bool fir = 1;
		string word;
		while (str >> word) {
			if (fir) {
				fir = 0;
			}
			else {
				cout << ' ';
			}
			auto t = change.find(word);
			if (t == change.end()) {
				cout << word;
			}
			else {
				cout << t->second;
			}
		}
		cout << endl;
	}
}
bool bigger(const string& s, string::size_type sz) {
	if (s.size() <= sz) {
		return 0;
	}
	return 1;
}
void biggist(vector<string>& s, int sz) {
	sort(s.begin(), s.end());
	auto a = unique(s.begin(), s.end());
	s.erase(a, s.end());
	stable_sort(s.begin(), s.end(), [](const string& p, const string& q) {return p.size() < q.size(); });
	auto b = count_if(s.begin(), s.end(), bind(bigger, _1, sz));
	cout << b;
	//for_each(b, s.end(), [](const string& q) {cout << q << ' '; });
}
multimap<string, vector<pair<string, string>>>family;
void addFamiiyMumber(string x, string m, string birthday) {
	family.find(x)->second.push_back(make_pair(m, birthday));
}

class StrBlobPtr;
class StrBlob {
	shared_ptr<vector<string>>date;
	void check(vector<string>::size_type n, const string& err) const;
public:
	friend class StrBlobPtr;
	StrBlob() {}
	StrBlob(vector<string>vs) :date(make_shared<vector<string>>(vs)) {}
	StrBlob(const StrBlob& sb) :date(sb.date) {}
	StrBlob& operator=(const StrBlob& sb);
	bool operator==(const StrBlob& sb);
	bool operator!=(const StrBlob& sb);
	bool operator<(const StrBlob& sb);
	string& operator[](vector<string>::size_type si);
	const string& operator[](vector<string>::size_type si) const;
	vector<string>::size_type size() const { return date->size(); }
	bool empty() const { return date->empty(); }
	void push_back(string s) { date->push_back(s); }
	void push_back(string&& s){ date->push_back(s); }
	void pop_back();
	string& front() const;
	string& back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
};
class StrBlobPtr {
	shared_ptr<vector<string>> check(size_t n, const string& s)const;
	weak_ptr<vector<string>> wptr;
	size_t curr;
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob& a, size_t n = 0) :wptr(a.date), curr(n) {}
	StrBlobPtr(const StrBlob& a, size_t n = 0) :wptr(a.date), curr(n) {}
	bool operator==(const StrBlobPtr& sbp);
	bool operator!=(const StrBlobPtr& sbp);
	bool operator<(const StrBlobPtr& sbp);
	char& operator[](string::size_type si);
	const char& operator[](string::size_type si) const;
	StrBlobPtr& operator++();
	StrBlobPtr operator++(int);
	StrBlobPtr& operator--();
	StrBlobPtr operator--(int);
	StrBlobPtr operator+(const StrBlobPtr& sbp);
	StrBlobPtr operator-(const StrBlobPtr& sbp);
	string& deref() const;
	StrBlobPtr& incr();
};
void StrBlob::check(vector<string>::size_type n, const string& err) const {
	if (date->size() < n) {
		throw out_of_range(err);
	}
}
void StrBlob::pop_back() {
	check(0, "error");
	date->pop_back();
}
string& StrBlob::front() const {
	check(0, "error");
	return date->front();
}
string& StrBlob::back() const {
	check(0, "error");
	return date->back();
}
StrBlob& StrBlob::operator=(const StrBlob& sb) {
	date = sb.date;
	return *this;
}
bool StrBlob::operator==(const StrBlob& sb) {
	if (*date == *(sb.date)) {
		return 1;
	}
	return 0;
}
bool StrBlob::operator!=(const StrBlob& sb) {
	if (!(*this==sb)) {
		return 1;
	}
	return 0;
}
bool StrBlob::operator<(const StrBlob& sb) {
	if (*date < *(sb.date)) {
		return 1;
	}
	return 0;
}
string& StrBlob::operator[](vector<string>::size_type si){
	check(si, "error");
	return (*date)[si];
}
const string& StrBlob::operator[](vector<string>::size_type si) const {
	check(si, "error");
	return (*date)[si];
}
shared_ptr<vector<string>> StrBlobPtr::check(size_t n, const string& s) const {
	auto t = wptr.lock();
	if (!t) {
		throw runtime_error(s);
	}
	if (curr >= t->size()) {
		throw out_of_range(s + "2");
	}
	return t;
}
bool StrBlobPtr::operator==(const StrBlobPtr& sbp) {
	if ((*wptr.lock())[curr] == (*(sbp.wptr.lock()))[sbp.curr]) {
		return 1;
	}
	return 0;
}
bool StrBlobPtr::operator!=(const StrBlobPtr& sbp) {
	if (!(*this==sbp)) {
		return 1;
	}
	return 0;
}
bool StrBlobPtr::operator<(const StrBlobPtr& sbp) {
	if ((*wptr.lock())[curr] < (*(sbp.wptr.lock()))[sbp.curr]) {
		return 1;
	}
	return 0;
}
char& StrBlobPtr::operator[](string::size_type si) {
	return (*(check(si, "error")))[curr][si];
}
const char& StrBlobPtr::operator[](string::size_type si) const{
	check(si, "error");
	return (*(check(si, "error")))[curr][si];
}
StrBlobPtr& StrBlobPtr::operator++() {
	check(curr, "error");
	++curr;
	return *this;
}
StrBlobPtr StrBlobPtr::operator++(int) {
	auto t = *this;
	++* this;
	return t;
}
StrBlobPtr& StrBlobPtr::operator--() {
	--curr;
	check(curr, "error");
	return *this;
}
StrBlobPtr StrBlobPtr::operator--(int) {
	auto t = *this;
	--*this;
	return t;
}
StrBlobPtr StrBlobPtr::operator+(const StrBlobPtr& sbp) {
	if (*(wptr.lock()) == *(sbp.wptr.lock())) {
		auto t = curr + sbp.curr;
		return StrBlobPtr(StrBlob(*check(t, "errpr")), t);
	}
	return StrBlobPtr();
}
StrBlobPtr StrBlobPtr::operator-(const StrBlobPtr& sbp) {
	if (*(wptr.lock()) == *(sbp.wptr.lock())) {
		auto t = curr - sbp.curr;
		return StrBlobPtr(StrBlob(*check(t, "errpr")), t);
	}
	return StrBlobPtr();
}
string& StrBlobPtr::deref() const {
	auto t = check(curr, "error");
	return (*t)[curr];
}
StrBlobPtr& StrBlobPtr::incr() {
	check(curr, "error");
	++curr;
	return *this;
}
StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
	return StrBlobPtr(*this, date->size());
}

class HasPtr {
	string* s;
	int n;
	size_t* si;
public:
	HasPtr(const string& cs = "", int i = 0) :s(new string(cs)), n(i), si(new size_t(1)) {}
	HasPtr(const HasPtr& hp) :s(hp.s), n(hp.n), si(hp.si) { ++* si; }
	HasPtr& operator=(const HasPtr& hp);
	friend void swap(HasPtr& hp1, HasPtr& hp2);
	void show() {
		cout << *s << '\n' << n << '\n';
	}
	bool operator<(const HasPtr& hp);
	~HasPtr() {
		--* si;
		if (!*si) {
			delete s;
			delete si;
		}
	}
};
HasPtr& HasPtr::operator=(const HasPtr& hp) {
	++* hp.si;
	if (-- * si == 0) {
		delete si;
		delete s;
	}
	s = hp.s;
	si = hp.si;
	n = hp.n;
	return *this;
}
void swap(HasPtr& hp1, HasPtr& hp2) {
	swap(hp1.s, hp2.s);
	swap(hp1.si, hp2.si);
	swap(hp1.n, hp2.n);
	cout << "now";
}
bool HasPtr::operator<(const HasPtr& hp) {
	return n < hp.n;
}

class QueryResult;
class TextQuery {
	shared_ptr <vector<string>> text;
	map<string, shared_ptr<set<vector<string>::size_type>>> wordMap;
public:
	TextQuery(ifstream& file);
	QueryResult search(const string& Word)const;
};
class QueryResult {
	shared_ptr<vector<string>> ppv;
	shared_ptr<set<vector<string>::size_type >> ppse;
	string pps;
public:
	QueryResult(string s, shared_ptr<vector<string>>pv, shared_ptr<set<vector<string>::size_type >>ps) :pps(s), ppv(pv), ppse(ps) {}
	friend void print(const QueryResult& qr);
	set<vector<string>::size_type >::iterator begin() { return (*ppse).begin(); }
	set<vector<string>::size_type >::iterator end() { return (*ppse).end(); }
	shared_ptr<vector<string>> get_file() { return ppv; }
};
TextQuery::TextQuery(ifstream& file) {
	text = shared_ptr <vector<string>>(new vector<string>);
	wordMap = map<string, shared_ptr<set<vector<string>::size_type>>>();
	string t;
	while (getline(file, t)) {
		text->push_back(t);
		auto tn = (*text).size() - 1;
		stringstream tss(t);
		string n;
		while (tss >> n) {
			auto& ps = wordMap[n];
			if (!ps) {
				ps.reset(new set<vector<string>::size_type >);
			}
			ps->insert(tn);
		}
	}
}
QueryResult TextQuery::search(const string& Word)const {
	static shared_ptr<set<vector<string>::size_type >> no(new set< vector<string>::size_type >);
	auto t = wordMap.find(Word);
	if (t == wordMap.end()) {
		return QueryResult(Word, text, no);
	}
	return QueryResult(Word, text, (*t).second);
}
void print(const QueryResult& qr) {
	for (auto i : *(qr.ppse)) {
		cout << i + 1 << ' ' << *((*qr.ppv).begin() + i) << '\n';
	}
}

class Folder;
class Message {
	string contents;
	set<Folder*>folders;
	void add_to_folders(Message& m);
	void remove_folders();
public:
	friend class Folder;
	explicit Message(const string& s) :contents(s) {}
	Message(Message& m);
	Message(Message&& m) noexcept;
	Message& operator=(Message& m);
	void save(Folder& f);
	void remove(Folder& f);
	~Message();
};
class Folder {
	set<Message*>messages;
public:
	void savMes(Message& m);
	void remMes(Message& m);
	~Folder();
};
void Message::add_to_folders(Message& m) {
	for (auto i : m.folders) {
		i->savMes(*this);
	}
}
void Message::remove_folders() {
	for (auto i : folders) {
		i->remMes(*this);
	}
	folders.clear();
}
Message::Message(Message& m) :contents(m.contents), folders(m.folders) {
	add_to_folders(m);
}
Message::Message(Message&& m) noexcept{
	add_to_folders(m);
	contents = move(m.contents);
	folders = move(m.folders);
	m.contents.clear();
	m.folders.clear();
}
Message& Message:: operator=(Message& m) {
	this->remove_folders();
	add_to_folders(m);
	contents = m.contents;
	folders = m.folders;
	return *this;
}
void Message::save(Folder& f) {
	f.savMes(*this);
	folders.insert(&f);
}
void Message::remove(Folder& f) {
	f.remMes(*this);
	folders.erase(&f);
}
Message::~Message() {
	remove_folders();
}
void Folder::savMes(Message& m) {
	messages.insert(&m);
}
void Folder::remMes(Message& m) {
	messages.erase(&m);
}
Folder::~Folder() {
	for (auto i : messages) {
		i->folders.erase(this);
	}
}

class Quote {
	string bookNo;
protected:
	double price = 0.0;
public:
	Quote() = default;
	Quote(const string& book, double pr) :bookNo(book), price(pr) {}
	Quote(const Quote& q) :bookNo(q.bookNo), price(q.price) {};
	string isbn() const { return bookNo; }
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual double net_price(size_t n) const { return n * price; }
	virtual void debug() const { cout << "bookNo is : " << bookNo << '\n' << "price is :" << price << endl; }
	virtual ~Quote() = default;
};
class Disc_quote :public Quote{
protected:
	size_t quantity;
	double discount;
public:
	Disc_quote() = default;
	Disc_quote(const string& book, double pr, size_t min, double dis) :Quote(book, pr), quantity(min), discount(dis) {}
	Disc_quote(const Disc_quote& dq) :Quote(dq), quantity(dq.quantity), discount(dq.discount) {}
	double net_price(size_t n) const = 0;
	void debug()const override;
};
class Bulk_quote : public Disc_quote{
public:
	Bulk_quote() = default;
	using Disc_quote::Disc_quote;
	Bulk_quote(const Bulk_quote& bq) :Disc_quote(bq) {}
	Bulk_quote* clone() const & override { return new Bulk_quote(*this); }
	double net_price(size_t n) const override;
};
class Another_quote: public Disc_quote{
public:
	Another_quote() = default;
	Another_quote(const string& book, double pr, size_t min, double dis) :Disc_quote(book, pr, min, dis) {}
	double net_price(size_t n)const override;
};
double Bulk_quote::net_price(size_t n)const {
	if (n >= quantity) {
		return n * (1 - discount) * price;
	}
	return n * price;
}
void Disc_quote::debug()const {
	Quote::debug();
	cout << "quantity is :" << quantity << '\n' << "discount is :" << discount << endl;
}
double Another_quote::net_price(size_t n)const {
	if (n > quantity) {
		return n * price - quantity * discount * price;
	}
	return n * (1 - discount) * price;
}
double print_total(const Quote& q, size_t n) {
	double all = q.net_price(n);
	cout << "ISBN: " << q.isbn() << " has sold " << n << ". The price is " << all << endl;
	return all;
}
class Backet {
	static bool compare(const shared_ptr<Quote> l, const shared_ptr<Quote> r) { return l->isbn() < r->isbn(); }
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
public:
	void add_item(shared_ptr<Quote> sq) { items.insert(sq); }
	void add_item(const Quote& q) { items.insert(shared_ptr<Quote>(q.clone())); }
	double total_receipt()const;
};
double Backet::total_receipt()const {
	double sum = 0.0;
	for (auto i = items.cbegin(); i != items.cend(); i = items.upper_bound(*i)) {
		sum += print_total(**i, items.count(*i));
	}
	cout << "Total receipt is :" << sum << endl;
	return sum;
}

template<typename T>
int compare(const T& l, const T& r) {
	if (less<T>()(l, r)) { return -1; }
	if (less<T>()(r, l)) { return 1; }
	return 0;
}//定义放头文件
template<typename T,typename U>
T my_find(T begin, T end, U ele) {
	for (auto i = begin; i != end; ++i) {
		if (*i == ele) {
			return i;
		}
	}
	return end;
}
template<typename T,size_t N>
const T* my_begin(const T(&arr)[N]) {
	return &arr[0];
}
template<typename T, size_t N>
const T* my_end(const T(&arr)[N]) {
	return &arr[0] + N;
}
template<typename T, size_t N>
size_t my_constexper(const T(&arr)[N]) {
	return N;
}
template <typename T>
void g(T&& l, T& r) {
	cout << l << ' ' << ++r;
}
template <typename T=int,typename T1,typename T2>
void flip(T1&& l, T2&& r,void(*)(T&&, T&)=g) {
	g(forward<T2>(r), forward<T1>(l));
}
template <typename T>
ostream& print(ostream & o,const T &t) {
	o << t << ' ';
	return o;
}
template<typename T,typename ...pag1>
ostream& print(ostream& o,const T& t, const pag1&...pag2  ) {
	o << t << ' ';
	return print(o,pag2...);
}
template<typename T>
unsigned count(const vector<T>& vt, T t) {
	return count(vt.begin(),vt.end(), t);
}
template<>
unsigned count(const vector<const char*>& vt, const char* t) {
	cout << "hear" << '\n';
	return count(vt.begin(), vt.end(), t);
}

int main(int argc,char**argv) {
	//vector<int>vi{ 1,2,3,4,5,6,7,8,8,9,0,1025,1026 };
	//ifstream f("D:\\td\\test.txt");
	//ofstream of1("D:\\td\\test1.txt"), of2("D:\\td\\test2.txt");
	const char* a = "111", * b = "222", * c = "333";
	vector<const char*>e{ a,b,c };
	cout << count(e, "111");
	/*for (auto i : a) {
		cout << i.first << ' ' << i.second << '\n';
	}*/
	return 0;
}
