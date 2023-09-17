struct Employee
{
	int id;
	char name[10];
	double hours;

	friend std::ostream& operator << (std::ostream& os, const Employee& employee)
	{
		return os << employee.id << " " << employee.name << " " << employee.hours;
	}

	friend std::istream& operator >> (std::istream& in, Employee& person)
	{
		return in >>  person.id >> person.name >> person.hours;
	}

	bool operator < (const Employee &other) {
		return strcmp(name, other.name) < 0;
	}

	bool operator > (const Employee& other) {
		return strcmp(name, other.name) > 0;
	}
};