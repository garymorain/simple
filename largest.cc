// Write a function that returns the largest element in a list.

#include <climits>
#include <list>
#include <stdio.h>

using std::list;

int largest(const list<int>& a_list) {
    int largest_element = INT_MIN;

    for (list<int>::const_iterator it = a_list.begin();
         it != a_list.end(); ++it) {
        int element = *it;
        if (element > largest_element) {
            largest_element = element;
        }
    }
    return largest_element;
}

int main(int argc, char **argv) {
    list<int> a;
    a.push_back(3);
    a.push_back(-1);
    a.push_back(99);
    a.push_back(-99);
    a.push_back(3);

    int largest_element = largest(a);
    printf("Largest element of [");
    for (list<int>::const_iterator it = a.begin();
         it != a.end(); ++it) {
        printf("%d ", *it);
    }
    printf("] is %d\n", largest_element);
}
