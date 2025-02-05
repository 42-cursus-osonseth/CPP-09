template <typename T>
void PmergeMe::swap(T a, T b)
{
    if (*b > *a)
    {
        int tmp = *b;
        *b = *a;
        *a = tmp;
    }
}
template <typename T>
void PmergeMe::sortPairs(T begin, T end)
{
    for (T it = begin; it != end - 1 && it != end; it += 2)
        swap<T>(it, it + 1);
}
template <typename T, typename C>
void PmergeMe::groupSmallAndLarge(T begin, T end, C &smallNbr, C &largeNbr)
{
    int size = std::distance(begin, end);
    if (size % 2 == 0)
        groupEven<T, C>(begin, end, smallNbr, largeNbr);
    else
        groupOdd<T, C>(begin, end, smallNbr, largeNbr);
}
template <typename T, typename C>
void PmergeMe::groupEven(T begin, T end, C &smallNbr, C &largeNbr)
{
    for (T it = begin; it != end; it += 2)
        largeNbr.push_back(*it);
    for (T it = begin + 1; it != end; it += 2)
    {
        if (it == end - 1)
        {
            smallNbr.push_back(*it);
            break;
        }
        smallNbr.push_back(*it);
    }
}
template <typename T, typename C>
void PmergeMe::groupOdd(T begin, T end, C &smallNbr, C &largeNbr)
{
    for (T it = begin; it != end - 1; it += 2)
        largeNbr.push_back(*it);
    for (T it = begin + 1; it != end; it += 2)
        smallNbr.push_back(*it);
    smallNbr.insert(smallNbr.begin(), *(end - 1));
}
template <typename C>
void PmergeMe::linkPairs(std::set<std::pair<int, int> > &link, C &largeNbr, C &smallNbr, int size)
{
    typename C::iterator itl = largeNbr.begin();
    typename C::iterator its;
    if (size % 2 == 0)
        its = smallNbr.begin();
    else
        its = smallNbr.begin() + 1;
    for (; itl != largeNbr.end(); ++itl)
    {
        link.insert(std::make_pair(*itl, *its));
        ++its;
    }
}
template <typename C>
void PmergeMe::reorganizationSmallNbr(std::set<std::pair<int, int> > &link, C &largeNbr, C &smallNbr, int size)
{
    typename C::iterator itl = largeNbr.begin();
    typename C::iterator its;
    itl = largeNbr.begin();
    if (size % 2 == 0)
        its = smallNbr.begin();
    else if (smallNbr.size() > 1)
        its = smallNbr.begin() + 1;
    for (; itl != largeNbr.end(); ++itl)
    {
        std::set<std::pair<int, int> >::iterator it = link.lower_bound(std::make_pair(*itl, 0));
        *its = it->second;
        its++;
    }
}

template <typename T, typename C>
void PmergeMe::insertSmallNbr(T begin, C &smallNbr, C &largeNbr)
{
    initData<C>(smallNbr);
    int i = 0;
    std::vector<int *> ptr;
    recoveryPTR<C>(ptr, smallNbr, size);
    while (size > 0)
    {
        long unsigned int lastJacob = jacob;
        if (jacob == 1)
        {
            insertFirstNbr<C>(lastJacob, smallNbr, largeNbr);
            i++;
            continue;
        }
        else if (jacob >= size)
        {
            insertAll<C>(smallNbr, largeNbr);
            break;
        }
        else
            insertFromJacobNumber<C>(smallNbr, largeNbr, ptr, i);
        updateData<C>(smallNbr, lastJacob);
        i++;
    }
    std::copy(largeNbr.begin(), largeNbr.end(), begin);
}
template <typename C>
void PmergeMe::insertFirstNbr(long unsigned int lastJacob, C &smallNbr, C &largeNbr)
{
    largeNbr.push_back(smallNbr.back());
    smallNbr.pop_back();
    total_insert++;
    jacob = jacob + (2 * prev);
    prev = lastJacob;
    size = smallNbr.size();
}
template <typename C>
void PmergeMe::insertAll(C &smallNbr, C &largeNbr)
{
    for (typename C::iterator it = smallNbr.begin(); it != smallNbr.end(); it++)
    {

        int pos = binarySearch<C>(largeNbr, *it);
        largeNbr.insert(largeNbr.begin() + pos, *it);
    }
}
template <typename C>
void PmergeMe::insertFromJacobNumber(C &smallNbr, C &largeNbr, std::vector<int *> ptr, int i)
{
    insertCount = 0;
    int value = *ptr[i];
    typename C::iterator it = std::find(smallNbr.begin(), smallNbr.end(), value);

    C veccopy(largeNbr.end() - (jacob + total_insert), largeNbr.end());
    for (; it != smallNbr.end();)
    {

        int pos = binarySearch<C>(veccopy, *it);
        veccopy.insert(veccopy.begin() + pos, *it);
        it = smallNbr.erase(it);
        insertCount++;
    }

    typename C::iterator itStart = largeNbr.end() - (jacob + total_insert);
    largeNbr.erase(largeNbr.end() - (jacob + total_insert), largeNbr.end());
    largeNbr.insert(itStart, veccopy.begin(), veccopy.end());
    total_insert += insertCount;
}
template <typename C>
int PmergeMe::binarySearch(C &container, int value)
{
    int left = 0, right = container.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (container[mid] > value)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}
template <typename C>
void PmergeMe::initData(C &smallNbr)
{
    size = smallNbr.size();
    jacob = 1;
    prev = 1;
    total_insert = 0;
}
template <typename C>
void PmergeMe::updateData(C &smallNbr, long unsigned int lastJacob)
{
    jacob = jacob + (2 * prev);
    prev = lastJacob;
    size = smallNbr.size();
}
template <typename C>
void PmergeMe::recoveryPTR(std::vector<int *> &ptr, C &smallNbr, long unsigned size)
{
    long unsigned int jacob = 1;
    long unsigned int prev = 1;
    int i = 0;

    while (jacob <= size)
    {
        unsigned int last_jacob = jacob;
        ptr.push_back(&smallNbr[smallNbr.size() - jacob]);
        jacob = jacob + (2 * prev);
        prev = last_jacob;
        i++;
    }
}
template <typename T, typename C>
void PmergeMe::recursiveMergeInsert(T begin, T end)
{
    int size = std::distance(begin, end);
    if (size <= 1)
        return;
    C largeNbr;
    C smallNbr;
    std::set<std::pair<int, int> > link;

    sortPairs<T>(begin, end);
    groupSmallAndLarge<T, C>(begin, end, smallNbr, largeNbr);
    linkPairs<C>(link, largeNbr, smallNbr, size);
    recursiveMergeInsert<T, C>(largeNbr.begin(), largeNbr.end());
    reorganizationSmallNbr<C>(link, largeNbr, smallNbr, size);
    insertSmallNbr<T, C>(begin, smallNbr, largeNbr);
}