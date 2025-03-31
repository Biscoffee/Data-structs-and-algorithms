//测试map的使用
void testLanguage() {
	string key = "name";
	int value = 123;
	pair<string, int> p(key, value);
	cout << p.first << " is " << p.second << endl;
	map<string, int> m;
	m.insert(p);
	m["age"] = 18;
	map<string, int>::iterator it = m.find("age");
	if(it != m.end())
	{
		cout << it->first << " is " << it->second << endl;
	}
	m.erase(it);
	m.erase("name");
	m.insert(pair<string, int>("a", 3));
	m.insert(make_pair<string, int>("b", 4));
	for (map<string, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << " is " << it->second << endl;
	}
}
