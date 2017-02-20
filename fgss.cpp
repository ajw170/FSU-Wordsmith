/*
    fgss.cpp
    01/01/12
    Chris Lacher

    "generic sort & search"
    functionality test of generic sort (heap or insertion) and binary search
    on Vector<T>, Deque<T>, and arrays of T

    Copyright 2012, R.C. Lacher
*/

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <vector.h>
#include <deque.h>
#include <compare.h>
#include <gheap.h> // g_heap_sort
#include <gsort.h> // g_insertion_sort
#include <gbsearch.h> // iterative implementations
#include <rbsearch.h> // recursive implementations
#include <genalg.h>

int main(int argc, char* argv[])
{
  bool BATCH = 0;
  if (argc > 1) BATCH = 1;
  std::istream* isptr = &std::cin;
  std::ifstream ifs;
  if (BATCH)
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cout << " ** Error: cannot open file " << argv[1] << '\n';
      return 0;
    }
    isptr = &ifs;
  }

  typedef char ElementType; const char* e_t = "char";

  typedef fsu::LessThan <ElementType>    PredicateType1;
  typedef fsu::GreaterThan <ElementType> PredicateType2;

  fsu::Vector < ElementType > V;  // a vector
  fsu::Deque  < ElementType > D;  // a deque
  ElementType *               A;  // an array
  PredicateType1              LT; // predicate object
  PredicateType2              GT; // predicate object

  fsu::Vector < ElementType > ::Iterator Vitr, Vloc, altVloc;
  fsu::Deque  < ElementType > ::Iterator Ditr, Dloc, altDloc;
  ElementType                          * Aitr, * Aloc, *altAloc;
  fsu::Pair<fsu::Vector<ElementType>::Iterator,fsu::Vector<ElementType>::Iterator> pv;
  fsu::Pair<fsu::Deque<ElementType>::Iterator,fsu::Deque<ElementType>::Iterator> pd;
  fsu::Pair<ElementType*,ElementType*> pp;

  ElementType e, s; // entry, sentinel
  unsigned int i, size;

  std::cout << "Begin test of generic sort and generic binary search < " << e_t << " >\n\n";
    if (!BATCH)
      std::cout << "  You will enter characters for storage into a vector V. These will be\n"
		<< "  copied to a deque D and an array A in several ways, then sorted with\n"
		<< "  various order relations. Then the program enters an interactive phase\n"
		<< "  where you will be prompted to enter search values. The sentinel value\n"
		<< "  will be used to terminate your original input and to end the program.\n\n";
    std::cout << "Enter sentinel: ";
  *isptr >> s;
  if (BATCH) std::cout << s << '\n';
  std::cout << "Enter elements ('"
       << s
       << "' to end): ";
  *isptr >> e;
  while (e != s)
  {
    if (BATCH) std::cout << e;
    V.PushBack(e);
    *isptr >> e;
  }
  if (BATCH) std::cout << e << '\n';

  std::cout << "V as entered:                " << V << '\n';

  // copy to deque
  size = V.Size();
  for (i = 0; i < size; ++i)
  {
    if (i%2)
      D.PushFront(V[i]);
    else
      D.PushBack(V[i]);
  }
  std::cout << "D as instantiated:           " << D << '\n';

  // copy to array
  A = new ElementType [size];
  fsu::g_copy(V.Begin(), V.End(), A);
  std::cout << "A as copied:                 ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';

  /* // begin generic insertion sort
  // apply generic insertion sort to each container, display, and recopy
  fsu::g_insertion_sort(V.Begin(), V.End(), GT);
  std::cout << "g_insertion_sort(V,>):       " << V << '\n';
  fsu::g_copy(D.Begin(), D.End(), V.Begin());

  fsu::g_insertion_sort(D.Begin(), D.End(), GT);
  std::cout << "g_insertion_sort(D,>):       " << D << '\n';
  fsu::g_copy(V.Begin(), V.End(), D.Begin());

  fsu::g_insertion_sort(A, A + size, GT);
  std::cout << "g_insertion_sort(A,>):       ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';
  fsu::g_copy(D.Begin(), D.End(), A);

  std::cout << "V as recopied:               " << V << '\n';
  std::cout << "D as recopied:               " << D << '\n';
  std::cout << "A as recopied:               ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';

  // apply generic insertionsort again to each container and display
  fsu::g_insertion_sort(V.Begin(), V.End());
  std::cout << "g_insertion_sort(V):         " << V << '\n';

  fsu::g_insertion_sort(D.Begin(), D.End());
  std::cout << "g_insertion_sort(D):         " << D << '\n';

  fsu::g_insertion_sort(A, A + size, LT);
  std::cout << "g_insertion_sort(A,<):       ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';
  //  end generic insertion sort */

  // begin generic heap sort
  // apply generic heapsort to each container, display, and recopy
  fsu::g_heap_sort(V.Begin(), V.End(), GT);
  std::cout << "g_heap_sort(V,>):            " << V << '\n';
  fsu::g_copy(D.Begin(), D.End(), V.Begin());

  fsu::g_heap_sort(D.Begin(), D.End(), GT);
  std::cout << "g_heap_sort(D,>):            " << D << '\n';
  fsu::g_copy(V.Begin(), V.End(), D.Begin());

  fsu::g_heap_sort(A, A + size, GT);
  std::cout << "g_heap_sort(A,>):            ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';
  fsu::g_copy(D.Begin(), D.End(), A);

  std::cout << "V as recopied:               " << V << '\n';
  std::cout << "D as recopied:               " << D << '\n';
  std::cout << "A as recopied:               ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';

  // apply generic heapsort again to each container and display
  fsu::g_heap_sort(V.Begin(), V.End());
  std::cout << "g_heap_sort(V):              " << V << '\n';

  fsu::g_heap_sort(D.Begin(), D.End());
  std::cout << "g_heap_sort(D):              " << D << '\n';

  fsu::g_heap_sort(A, A + size, LT);
  std::cout << "g_heap_sort(A,<):            ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';
  // end generic heap sort */

  // now do binary search
  while(1)
  {
    std::cout << "Enter search value ('"
	 << s
	 << "' to quit): ";
    *isptr >> e;
    if (BATCH) std::cout << e << '\n';
    if (e == s) break;

    // calculate pair versions
    // pv = fsu::g_range (V.Begin(), V.End(),e,LT);
    // pd = fsu::g_range (D.Begin(), D.End(),e,LT);
    // pp = fsu::g_range (A,A+size,e,LT);
    pv = fsu::g_range (V.Begin(), V.End(),e);
    pd = fsu::g_range (D.Begin(), D.End(),e);
    pp = fsu::g_range (A,A+size,e);

    // test of g_lower_bound, g_upper_bound on Vector
    Vloc = fsu::g_lower_bound(V.Begin(), V.End(), e, LT);
    // check recursive version
    altVloc = alt::g_lower_bound(V.Begin(), V.End(), e, LT);
    if (Vloc != altVloc)
      std::cout << " ** Error: fsu:: and alt:: g_lower_bound do not agree on Vector\n";
    // */
    if  (pv.first_ != Vloc)
      std::cout << " ** Error: pv.first_ and lower bound iter do not agree on Vector\n";
    std::cout << "V = " << V << '\n';
    std::cout << "    ";
    for (Vitr = V.Begin(); Vitr != Vloc; ++Vitr) std::cout << ' ';
    std::cout << "^lb\n";

    Vloc = fsu::g_upper_bound(V.Begin(), V.End(), e, LT);
    // check recursive version
    altVloc = alt::g_upper_bound(V.Begin(), V.End(), e, LT);
    if (Vloc != altVloc)
      std::cout << " ** Error: fsu:: and alt:: g_upper_bound do not agree on Vector\n";
    // */
    if  (pv.second_ != Vloc)
      std::cout << " ** Error: pv.second_ and upper bound iter do not agree on Vector\n";
    std::cout << "V = " << V << '\n';
    std::cout << "    ";
    for (Vitr = V.Begin(); Vitr != Vloc; ++Vitr) std::cout << ' ';
    std::cout << "^ub\n";

    // test of g_lower_bound, g_upper_bound on Deque
    Dloc = fsu::g_lower_bound(D.Begin(), D.End(), e, LT);
    // check recursive version
    altDloc = alt::g_lower_bound(D.Begin(), D.End(), e, LT);
    if (Dloc != altDloc)
      std::cout << " ** Error: fsu:: and alt:: g_lower_bound do not agree on Deque\n";
    // */
    if  (pd.first_ != Dloc)
      std::cout << " ** Error: pd.first_ and lower bound iter do not agree on Deque\n";
    std::cout << "D = " << D << '\n';
    std::cout << "    ";
    for (Ditr = D.Begin(); Ditr != Dloc; ++Ditr) std::cout << ' ';
    std::cout << "^lb\n";
    Dloc = fsu::g_upper_bound(D.Begin(), D.End(), e, LT);
    // check recursive version
    altDloc = alt::g_upper_bound(D.Begin(), D.End(), e, LT);
    if (Dloc != altDloc)
      std::cout << " ** Error: fsu:: and alt:: g_upper_bound do not agree on Deque\n";
    // */
    if  (pd.second_ != Dloc)
      std::cout << " ** Error: pd.second_ and upper bound iter do not agree on Deque\n";
    std::cout << "D = " << D << '\n';
    std::cout << "    ";
    for (Ditr = D.Begin(); Ditr != Dloc; ++Ditr) std::cout << ' ';
    std::cout << "^ub\n";

    // test of g_lower_bound, g_upper_bound on array
    Aloc = fsu::g_lower_bound(A, A + size, e, LT);
    // check recursive version
    altAloc = alt::g_lower_bound(A, A + size, e, LT);
    if (Aloc != altAloc)
      std::cout << " ** Error: fsu:: and alt:: g_lower_bound do not agree on array\n";
    // */
    if  (pp.first_ != Aloc)
      std::cout << " ** Error: pp.first_ - Aloc = " << pp.first_ - Aloc << "\n";
    std::cout << "A = ";
    for (Aitr = A; Aitr != A + size; ++Aitr) std::cout << *Aitr; std::cout << '\n';
    std::cout << "    ";
    for (Aitr = A; Aitr != Aloc; ++Aitr) std::cout << ' ';
    std::cout << "^lb\n";
    Aloc = fsu::g_upper_bound(A, A + size, e, LT);
    // check recursive version
    altAloc = alt::g_upper_bound(A, A + size, e, LT);
    if (Aloc != altAloc) 
      std::cout << " ** Error: fsu:: and alt:: g_upper_bound do not agree on array\n";
    // */
    if  (pp.second_ != Aloc)
      std::cout << " ** Error: pp.second_ and upper bound iter do not agree on Array\n";
    std::cout << "A = ";
    for (Aitr = A; Aitr != A + size; ++Aitr) std::cout << *Aitr; std::cout << '\n';
    std::cout << "    ";
    for (Aitr = A; Aitr != Aloc; ++Aitr) std::cout << ' ';
    std::cout << "^ub\n";

    // test of g_binary_search
    std::cout << e << " is ";
    if (!fsu::g_binary_search(V.Begin(), V.End(), e, LT))
      std::cout << "not ";
    std::cout << "in V\n";
    std::cout << e << " is ";
    if (!fsu::g_binary_search(D.Begin(), D.End(), e, LT))
      std::cout << "not ";
    std::cout << "in D\n";
    std::cout << e << " is ";
    if (!fsu::g_binary_search(A, A + size, e, LT))
      std::cout << "not ";
    std::cout << "in A\n";

    // test alt version against fsu version
    int result = fsu::g_binary_search(V.Begin(), V.End(), e, LT);
    if (result != alt::g_binary_search(V.Begin(), V.End(), e, LT))
      std::cout << " ** Error: fsu:: and alt:: g_binary_search do not agree on Vector\n";
    result = fsu::g_binary_search(D.Begin(), D.End(), e, LT);
    if (result != alt::g_binary_search(D.Begin(), D.End(), e, LT))
      std::cout << " ** Error: fsu:: and alt:: g_binary_search do not agree on Deque\n";
    result = fsu::g_binary_search(A, A + size, e, LT);
    if (result != alt::g_binary_search(A, A + size, e, LT))
      std::cout << " ** Error: fsu:: and alt:: g_binary_search do not agree on array\n";
    // */
  }
  std::cout << "End test of g_heap_sort/g_binary_search < " << e_t << " >\n";
  return 0;
}
