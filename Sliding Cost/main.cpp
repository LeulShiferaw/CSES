#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

//Modified sliding mean
//Added sumMax and sumMin
//They are changed everytime we modify maxHeap and minHeap
ll sumMax = 0, sumMin = 0;
/*Used the two heap algorithm. Max heap is always greater b/c of reshape function*/
int median(const multiset<int> &minHeap, const multiset<int, greater<int>> &maxHeap)
{
    if(minHeap.size() == maxHeap.size())//If they are equal get the lowest one
    {
        return min(*minHeap.begin(), *maxHeap.begin());
    }
    return *maxHeap.begin();//Max heap has more elements
}

//Remove x from one of them
void remove(const int &x, multiset<int, greater<int>> &maxHeap, multiset<int> &minHeap)
{
    auto itr = maxHeap.find(x);
    if(itr != maxHeap.end())
    {
        sumMax -= x;
        maxHeap.erase(itr);
        return;
    }

    itr = minHeap.find(x);
    if(itr != minHeap.end())
    {
        sumMin -= x;
        minHeap.erase(itr);
        return;
    }
}

//Display heap
void display(const multiset<int, greater<int>> &heap)
{
    for(const int &x : heap)
        cout << x << " ";
    cout << endl;
}

void display(const multiset<int> &heap)
{
    for(const int &x : heap)
        cout << x << " ";
    cout << endl;
}

//First make sure that maxHeap doesn't have more than one element.
//Then make sure that maxHeap is not less therefore maxHeap.size() >= minHeap.size
void reshape(multiset<int> &minHeap, multiset<int, greater<int>> &maxHeap)
{
    if(minHeap.size() == maxHeap.size()) return;
    while(maxHeap.size() > minHeap.size() + 1) {
        minHeap.insert(*maxHeap.begin());
        sumMin += *maxHeap.begin();
        sumMax -= *maxHeap.begin();
        maxHeap.erase(maxHeap.begin());
    }

    while(maxHeap.size() < minHeap.size()) {
        maxHeap.insert(*minHeap.begin());
        sumMax += *minHeap.begin();
        sumMin -= *minHeap.begin();
        minHeap.erase(minHeap.begin()); 
    }
}

//Add on to maxHeap then move greatest element to minHeap
void add(const int &x, multiset<int> &minHeap, multiset<int, greater<int>> &maxHeap)
{
    maxHeap.insert(x);
    sumMax += x;

    minHeap.insert(*maxHeap.begin());
    sumMin += *maxHeap.begin();
    sumMax -= *maxHeap.begin();
    maxHeap.erase(maxHeap.begin());
    reshape(minHeap, maxHeap);
}

//The cost is just this formula. It doesn't matter where the mean is.
long long cost(const multiset<int> &minHeap, const multiset<int, greater<int>> &maxHeap)
{
    long long med = median(minHeap, maxHeap);
    return (long long)maxHeap.size() * med - sumMax + sumMin - (long long)minHeap.size() * med;
}

void solve()
{
    int n, k;
    cin >> n >> k;

    vi x(n);
    for(int i= 0; i<n; ++i) cin >> x[i];

    multiset<int> minHeap;
    multiset<int, greater<int>> maxHeap;

    for(int i = 0; i<k; ++i) {
        add(x[i], minHeap, maxHeap);
    }

    cout << cost(minHeap, maxHeap) << " ";
    for(int i = k; i<n; ++i)
    {
        add(x[i], minHeap, maxHeap);
        remove(x[i-k], maxHeap, minHeap);
        reshape(minHeap, maxHeap);
        cout << cost(minHeap, maxHeap) << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}