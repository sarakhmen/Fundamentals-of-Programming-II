#include "Data.h"


void Data::pushBack(const vector<wstring>& elem) {
	vecData.push_back(elem);
	if (bMask)
		indexMask.push_back(vecData.size() - 1);
}


vector<vector<wstring>>::iterator Data::erase(int iPos) {
	if (bMask) {
		auto iter = vecData.erase(vecData.begin() + indexMask[iPos]);
		indexMask.erase(indexMask.begin() + iPos);
		return iter;
	}
	else
		return vecData.erase(vecData.begin() + iPos);
}


vector<wstring>& Data::operator[](int iPos) {
	if (bMask)
		return vecData[indexMask[iPos]];
	else
		return vecData[iPos];
}


void Data::clear() {
	if (bMask) {
		for (size_t i = 0; i < indexMask.size(); ++i) {
			erase(indexMask[i]);
		}
	}
	else
		vecData.clear();
}


bool Data::isMask() {
	return bMask;
}


size_t Data::size() {
	if (bMask)
		return indexMask.size();
	else
		return vecData.size();
}


void Data::setMask(bool flag) {
	bMask = flag;
	if (!flag)
		indexMask.clear();
}


void Data::pushMaskIndex(int iPos) {
	indexMask.push_back(iPos);
}