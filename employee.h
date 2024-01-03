struct Employee
{
	int id;
	char name[10];
	double hours;

	Employee() {}

	Employee(int _id, const char* _name, double _hours) {
		id = _id;
		strncpy_s(name, _name, sizeof(name));
		name[sizeof(name) - 1] = '\0';
		hours = _hours;
	}

	friend std::ostream& operator << (std::ostream& os, const Employee& employee)
	{
		return os << employee.id << " " << employee.name << " " << employee.hours;
	}

	friend std::wostream& operator << (std::wostream& os, const Employee& employee)
	{
		return os << employee.id << " " << employee.name << " " << employee.hours;
	}

	friend std::istream& operator >> (std::istream& in, Employee& person)
	{
		return in >>  person.id >> person.name >> person.hours;
	}

	bool operator < (const Employee &other) const {
		return strcmp(name, other.name) < 0;
	}

	bool operator > (const Employee& other) const {
		return strcmp(name, other.name) > 0;
	}

	bool operator == (const Employee& other) const {
		return id == other.id && strcmp(name, other.name) == 0 && hours == other.hours;
	}
};