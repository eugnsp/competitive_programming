/*********************************************************************
498-bis
-------
UVa ID: 102 68

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "io.hpp"
#include <vector>

using T = int;

// Returns the derivative of the polynomial (as) at the point (x)
T derivative(const std::vector<T>& as, T x)
{
	T d = 0;
	const auto end = as.end() - 1;
	for (auto it = as.begin(); it != end; ++it)
		d = d * x + *it * static_cast<T>(end - it);

	return d;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		return (in >> x_) && read_vector_line(in, as_);
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{	
		out << derivative(as_, x_) << '\n';
	}

private:
	std::vector<T> as_;
	T x_;
};

int main()
{
	CP p;
	return p.run();
}
