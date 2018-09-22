/*
 * c_exec01_01.cpp
 *
 *  Created on: 2018. 9. 15.
 *      Author: finegs
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class ContInfo {
	public:
		void operator() (T t) {
			num++;
			sum+=t;
		}

		int getSum() const { return sum; }
		int getSize() const { return num; }
		double getMean() const {
			return static_cast<double>(sum) / static_cast<double>(num);
		}

	private:
		T sum{0};
		int num{0};

};

int main(int argc, char* argv[]) {

	vector<double> myVec{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
	auto vecInfo = for_each(myVec.begin(), myVec.end(), ContInfo<double>());

	cout << "Router : Sum=" << vecInfo.getSum()
					<< ", Size=" << vecInfo.getSize()
					<< ", Mean=" << vecInfo.getMean() << endl;

	return EXIT_SUCCESS;
}
