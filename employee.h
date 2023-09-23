struct Employee
{
	int id;
	wchar_t name[10];
	double hours;

	friend std::ostream& operator << (std::ostream& os, const Employee& employee)
	{
		return os << employee.id << " " << employee.name << " " << employee.hours;
	}

	friend std::wostream& operator << (std::wostream& os, const Employee& employee)
	{
		return os << employee.id << " " << employee.name << " " << employee.hours;
	}

	friend std::wistream& operator >> (std::wistream& in, Employee& person)
	{
		return in >> person.id >> person.name >> person.hours;
	}

	bool operator < (const Employee &other) {
		return wcscmp(name, other.name) < 0;
	}

	bool operator > (const Employee& other) {
		return wcscmp(name, other.name) > 0;
	}
};