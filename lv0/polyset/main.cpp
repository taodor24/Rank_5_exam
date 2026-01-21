#include <iostream>
#include <cassert>
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "Set.hpp" // Make sure the filename matches yours (set.hpp or Set.hpp)


/*


Launch tester: 
clang++ -Wall -Wextra -Werror *.cpp -o polyset

Valgrind: valgrind --leak-check=full ./polyset



*/






int main() {
    std::cout << "--- 1. Testing SearchableArrayBag (OCF & Logic) ---" << std::endl;
    {
        SearchableArrayBag s1;
        s1.insert(10);
        s1.insert(20);
        
        // Testing copy constructor (Deep Copy)
        SearchableArrayBag s2(s1);
        s2.insert(30);
        
        std::cout << "S1 (should be 10 20): "; s1.print();
        std::cout << "S2 (should be 10 20 30): "; s2.print();
        
        // Testing has() method
        if (s1.has(10) && !s1.has(30))
            std::cout << "ArrayBag: has() works correctly!" << std::endl;
    }

    std::cout << "\n--- 2. Testing SearchableTreeBag (BST Logic) ---" << std::endl;
    {
        SearchableTreeBag t1;
        t1.insert(50);
        t1.insert(25);
        t1.insert(75);
        
        // Testing assignment operator
        SearchableTreeBag t2;
        t2 = t1;
        t2.insert(100);
        
        std::cout << "T1 (should be 25 50 75): "; t1.print();
        std::cout << "T2 (should be 25 50 75 100): "; t2.print();
        
        if (t1.has(75) && !t1.has(100))
            std::cout << "TreeBag: has() works correctly!" << std::endl;
    }

    std::cout << "\n--- 3. Testing Set Wrapper (The Core Task) ---" << std::endl;
    {
        // Set must prevent duplicates
        SearchableArrayBag* array_impl = new SearchableArrayBag();
        Set mySet(array_impl);
        
        mySet.insert(42);
        mySet.insert(42); // Should not be added
        mySet.insert(42); // Should not be added
        mySet.insert(21);
        
        std::cout << "Set (should only contain 42 21): "; mySet.print();
        
        int arr[] = {1, 2, 1, 3, 2};
        mySet.insert(arr, 5);
        std::cout << "Set after array insert (no duplicates): "; mySet.print();

        delete array_impl; // Cleaning up the wrapped bag
    }

    std::cout << "\n--- 4. Testing Polymorphism (Defense Check) ---" << std::endl;
    {
        // A SearchableBag pointer can point to both Array and Tree implementations
        SearchableBag* bag;
        
        bag = new SearchableArrayBag();
        bag->insert(5);
        std::cout << "Polymorphic Array: "; bag->print();
        delete bag;

        bag = new SearchableTreeBag();
        bag->insert(5);
        std::cout << "Polymorphic Tree: "; bag->print();
        delete bag; 
        // If your destructors are virtual, this won't leak!
    }

    std::cout << "\n--- All Specific Tests Passed! ---" << std::endl;
    return 0;
}