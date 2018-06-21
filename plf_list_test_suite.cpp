#if defined(_MSC_VER)
	#define PLF_FORCE_INLINE __forceinline

	#if _MSC_VER < 1600
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
	#elif _MSC_VER == 1600
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
	#elif _MSC_VER == 1700
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
	#elif _MSC_VER == 1800
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT // Variadics, in this context, means both variadic templates and variadic macros are supported
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
		#define PLF_INITIALIZER_LIST_SUPPORT
	#elif _MSC_VER >= 1900
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT noexcept
		#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::is_always_equal::value)
		#define PLF_INITIALIZER_LIST_SUPPORT
	#endif
#elif defined(__cplusplus) && __cplusplus >= 201103L
	#define PLF_FORCE_INLINE // note: GCC creates faster code without forcing inline

	#if defined(__GNUC__) && defined(__GNUC_MINOR__) && !defined(__clang__) // If compiler is GCC/G++
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || __GNUC__ > 4 // 4.2 and below do not support variadic templates
			#define PLF_VARIADICS_SUPPORT
		#endif
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 4) || __GNUC__ > 4 // 4.3 and below do not support initializer lists
			#define PLF_INITIALIZER_LIST_SUPPORT
		#endif
		#if (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || __GNUC__ < 4
			#define PLF_NOEXCEPT throw()
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator)
			#define PLF_NOEXCEPT_SWAP(the_allocator)
		#elif __GNUC__ < 6
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept
		#else // C++17 support
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::is_always_equal::value)
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value)
		#endif
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7) || __GNUC__ > 4
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#endif
		#if __GNUC__ >= 5 // GCC v4.9 and below do not support std::is_trivially_copyable
			#define PLF_TYPE_TRAITS_SUPPORT
		#endif

	#elif defined(__GLIBCXX__) // Using another compiler type with libstdc++ - we are assuming full c++11 compliance for compiler - which may not be true
		#if __GLIBCXX__ >= 20080606 	// libstdc++ 4.2 and below do not support variadic templates
			#define PLF_VARIADICS_SUPPORT
		#endif
		#if __GLIBCXX__ >= 20090421 	// libstdc++ 4.3 and below do not support initializer lists
			#define PLF_INITIALIZER_LIST_SUPPORT
		#endif
		#if __GLIBCXX__ >= 20160111
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::is_always_equal::value)
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value)
		#elif __GLIBCXX__ >= 20120322
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept
		#else
			#define PLF_NOEXCEPT throw()
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator)
			#define PLF_NOEXCEPT_SWAP(the_allocator)
		#endif
		#if __GLIBCXX__ >= 20150422 // libstdc++ v4.9 and below do not support std::is_trivially_copyable
			#define PLF_TYPE_TRAITS_SUPPORT
		#endif
	#elif defined(_LIBCPP_VERSION) // No type trait support in libc++ to date
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT
		#define PLF_INITIALIZER_LIST_SUPPORT
		#define PLF_NOEXCEPT noexcept
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::is_always_equal:value)
		#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept
	#else // Assume type traits and initializer support for non-GCC compilers and standard libraries
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT
		#define PLF_INITIALIZER_LIST_SUPPORT
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_NOEXCEPT noexcept
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::is_always_equal:value)
		#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept
	#endif

	#define PLF_MOVE_SEMANTICS_SUPPORT
#else
	#define PLF_FORCE_INLINE
	#define PLF_NOEXCEPT throw()
	#define PLF_NOEXCEPT_SWAP(the_allocator)
	#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator)
#endif



#include <functional> // std::greater
#include <vector> // range-insert testing
#include <iostream>
#include <algorithm> // std::find
#include <cstdio> // log redirection
#include <cstdlib> // abort

#ifdef PLF_MOVE_SEMANTICS_SUPPORT
	#include <utility> // std::move
#endif


#include "plf_list.h"




void title1(const char *title_text)
{
	std::cout << std::endl << std::endl << std::endl << "*** " << title_text << " ***" << std::endl;
	std::cout << "===========================================" << std::endl << std::endl << std::endl; 
}



void title2(const char *title_text)
{
	std::cout << std::endl << std::endl << "--- " << title_text << " ---" << std::endl << std::endl;
}

	
void title3(const char *title_text)
{
	std::cout << std::endl << title_text << std::endl;
}

	

void failpass(const char *test_type, bool condition)
{
	std::cout << "\n" << test_type << ": ";
	
	if (condition) 
	{ 
		std::cout << "Pass\n\n";
	} 
	else 
	{
		std::cout << "Fail" << std::endl;
		std::cin.get(); 
		abort(); 
	}
}



// Fast xorshift+128 random number generator function (original: https://codingforspeed.com/using-faster-psudo-random-generator-xorshift/)
unsigned int xor_rand()
{
	static unsigned int x = 123456789;
	static unsigned int y = 362436069;
	static unsigned int z = 521288629;
	static unsigned int w = 88675123;
	
	const unsigned int t = x ^ (x << 11); 

	// Rotate the static values (w rotation in return statement):
	x = y;
	y = z;
	z = w;

	return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}



struct small_struct
{
	double *empty_field_1;
	double unused_number;
	unsigned int empty_field2;
	double *empty_field_3;
	double number;
	unsigned int empty_field4;

	small_struct(const int num): number(num) {};
};





// For remove_if testing:

template <class T>
struct larger_than_fifteen
{
	bool operator() (const T &value)
	{
		return value > 15;
	}
};



#ifdef PLF_VARIADICS_SUPPORT
	struct perfect_forwarding_test
	{
		const bool success;

		perfect_forwarding_test(int&& /*perfect1*/, int& perfect2)
			: success(true)
		{
			perfect2 = 1;
		}

		template <typename T, typename U>
		perfect_forwarding_test(T&& /*imperfect1*/, U&& /*imperfect2*/)
			: success(false)
		{}
	};
#endif




int main(int argc, char **argv)
{
	freopen("errors.log","w", stderr);

	using namespace plf;

	unsigned int loop_counter = 0;

	#if defined(PLF_INITIALIZER_LIST_SUPPORT) || defined(PLF_MOVE_SEMANTICS_SUPPORT)
		bool passed = true;
	#endif

	#ifndef PLF_INITIALIZER_LIST_SUPPORT
		std::cout << "Initializer_list support (C++11 or higher) is required for most tests. Most tests will skipped without it. Press ENTER to continue." << std::endl;
		std::cin.get();
	#endif

	while (++loop_counter != 50)
	{
		int test_counter = 1;

		#ifdef PLF_INITIALIZER_LIST_SUPPORT
		{
			title2("Merge tests");	
			plf::list<int> list1;
			list1.insert(list1.end(), {1, 3, 5, 7, 9});
			plf::list<int> list2 = {2, 4, 6, 8, 10};
			
			list1.merge(list2);
			
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if (test_counter++ != *it)
				{
					passed = false;
				}
			}
			
			failpass("Merge test", passed);	



			list1.clear();
			list2.clear();
			

			title2("Splice tests");	

			list1 = {1, 2, 3, 4, 5};
			list2 = {6, 7, 8, 9, 10};
			
			
			list1.splice(list1.end(), list2);
			
			test_counter = 1;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if (test_counter++ != *it)
				{
					passed = false;
				}
			}
			
			failpass("Test splice at end", passed);	


			list1.clear();
			list2.clear();


			
			list1 = {1, 2, 3, 4, 5};
			list2 = {6, 7, 8, 9, 10};
			
			
			list1.splice(list1.begin(), list2);
			
			
			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				test_counter += *it;
			}
			
			failpass("Test splice at begin", test_counter == 55);	



			list1.clear();
			list2.clear();
			
			list1 = {1, 2, 3, 4, 5};
			list2 = {6, 7, 8, 9, 10};
			
			plf::list<int>::iterator it2 = list1.begin();
			std::advance(it2, 3);
			
			list1.splice(it2, list2);
			
			test_counter = 0;
			
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				test_counter += *it;
			}

			list1.clear();
			list2.clear();
			

			for (unsigned int counter = 1; counter != 25; ++counter)
			{
				list1.push_back(counter);
				list2.push_back(counter + 25);
			}
			
			
			plf::list<int>::iterator it3 = list1.begin();
			std::advance(it3, 18);
			
			list1.splice(it3, list2);
			
			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				test_counter += *it;
			}
			
			failpass("Test splice past middle", test_counter == 1200);


			list1.clear();
			list2.clear();
			
			for (unsigned int counter = 5; counter != 36; ++counter)
			{
				list1.push_back(counter);
				list2.push_front(counter);
			}


			list1.splice(list1.begin(), list2);
			
			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				test_counter += *it;
			}
			
			failpass("Large list splice", test_counter == 1240);



			title2("Sort tests");

			list1.sort();

			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if(*it < test_counter)
				{
					passed = false;
				}

				test_counter = *it;
			}
			
			failpass("Sort ((default) less than)", passed);
			
			
			list1.sort(std::greater<int>());
			
			test_counter = 65535;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				
				if(*it > test_counter)
				{
					passed = false;
				}
				
				test_counter = *it;
			}

			failpass("Sort ((predicate), greater than)", passed);



			title2("Reverse tests");

			list1.reverse();

			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if(*it < test_counter)
				{
					passed = false;
				}
				
				test_counter = *it;
			}
			
			failpass("Test reverse", passed);



			title2("Unique tests");

			list1.unique();
			
			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if(*it == test_counter)
				{
					passed = false;
				}
				
				test_counter = *it;
			}

			failpass("Unique test", passed);

			


			title2("Remove tests");

			list1.remove_if(larger_than_fifteen<int>());

			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if (*it > 15)
				{
					passed = false;
				}
			}
			
			failpass("remove_if ( > 15) test", passed);


			list1.clear();
			list2.clear();
			

			
			list1 = {5, 5, 4, 4};
			
			list1.remove(5);
			
			
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if(*it == 5)
				{
					passed = false;
				}
			}
			
			failpass("remove ( == 5) test", passed);


			list1.remove(4);
			failpass("Remove to create empty list test", list1.empty());
			
		
			title2("Reserve tests");

			list1.clear();
			list2.clear();
			

			list1.reserve(4097);

			std::cout << "\nInitial capacity after reserve = " << list1.capacity() << std::endl;
			
			failpass("Reserve from empty test", list1.capacity() >= 4097);



			list1.push_back(15);
			
			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				++test_counter;
			}

			failpass("Push_back singular test", list1.size() == static_cast<unsigned int>(test_counter));
			
			

			
			list1.insert(list1.end(), 10000, 15);
			
			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				++test_counter;
			}
			
			std::cout << "\nSize (after iteration) = " << test_counter << std::endl;
			std::cout << "\nCapacity after insertion = " << list1.capacity() << std::endl;

			failpass("Fill-insert test", list1.size() == 10001 && test_counter == 10001 && list1.capacity() >= 10001);



			list1.reserve(15000);
			std::cout << "\nCapacity after 2nd reserve = " << list1.capacity() << std::endl;
			failpass("Reserve post-insertion test", list1.capacity() >= 15000);



			title2("Resize tests");

			list1.resize(2);
			std::cout << "\nCapacity after resize = " << list1.capacity() << std::endl;

			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				++test_counter;
			}
			
			failpass("Resize test", list1.size() == 2 && test_counter == 2);
			


			title2("Assign tests");

			std::vector<int> test_vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			
			list1.assign(test_vector.begin(), test_vector.end());
			std::cout << "\nCapacity after range-assign = " << list1.capacity() << std::endl;

			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				
				if (++test_counter != *it)
				{
					passed = false;
				}
			}
			
			failpass("Range-assign test", list1.size() == 10 && test_counter == 10 && passed);
			
			
			
			list1.assign(20, 1);
			std::cout << "\nCapacity after fill-assign = " << list1.capacity() << std::endl;

			test_counter = 0;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";
				++test_counter;
				
				if (*it != 1)
				{
					passed = false;
				}
			}
			
			failpass("Fill-assign test", list1.size() == 20 && test_counter == 20 && passed);
			
			

			
			std::initializer_list<int> inlist = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

				
			list1.assign(inlist);
			std::cout << "\nCapacity after initializer-list assign = " << list1.capacity() << std::endl;

			test_counter = 11;
			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				std::cout << *it << ",  ";

				if (--test_counter != *it)
				{
					passed = false;
				}
			}

			failpass("Initializer-list assign test", list1.size() == 10 && test_counter == 1 && passed);
			
			
			title2("Insert tests");
			
			
			list2.insert(list2.end(), test_vector.begin(), test_vector.end());
			
			test_counter = 1;
			
			for (plf::list<int>::iterator it = list2.begin(); it != list2.end(); ++it)
			{
				std::cout << *it << ",  ";

				if (test_counter++ != *it)
				{
					passed = false;
				}
			}
			
			failpass("Range-insert test", passed);	



			list2.insert(list2.begin(), 50, 50000);
			

			test_counter = 0;
			
			for (plf::list<int>::iterator it = list2.begin(); it != list2.end(); ++it)
			{
				++test_counter;
			}
			
			failpass("Fill-insert post range-insert test", test_counter == 60 && list2.size() == 60);	



			test_counter = 0;
			
			while (!list2.empty())
			{
				for (plf::list<int>::iterator it = list2.begin(); it != list2.end();)
				{
					if ((xor_rand() & 15) == 0)
					{
						list2.insert(it, 13);
					}
					
					if ((xor_rand() & 7) == 0)
					{
						it = list2.erase(it);
					}
					else
					{
						++it;
					}

					++test_counter;
				}


				unsigned int size_counter = 0;
				
				for (plf::list<int>::iterator it = list2.begin(); it != list2.end(); ++it)
				{
					++size_counter;
				}
				
				if (size_counter != list2.size())
				{
					std::cout << "Failing at counter == " << test_counter << std::endl;
				}
			}
			
			failpass("Erase and insert randomly till empty test", list2.empty());	


			list1.clear();
			list2.clear();
			
		}
		#endif


		#if defined(PLF_MOVE_SEMANTICS_SUPPORT) && defined(PLF_VARIADICS_SUPPORT)
		{
			title2("Emplace, move and Reverse iterate tests");

			plf::list<small_struct> s_list1;


			for (unsigned int counter = 0; counter != 254; ++counter)
			{
				s_list1.emplace_back(counter);
			}

			small_struct temp = s_list1.emplace_back(254);

			failpass("Emplace_back return value test", temp.number == 254);


			test_counter = 0;

			for (plf::list<small_struct>::iterator it = s_list1.begin(); it != s_list1.end(); ++it)
			{
				if (test_counter++ != it->number)
				{
					passed = false;
					break;
				}
			}

			failpass("Emplace_back test", passed);


			for (plf::list<small_struct>::reverse_iterator rit = s_list1.rbegin(); rit != s_list1.rend(); ++rit)
			{
				if (--test_counter != rit->number)
				{
					passed = false;
					break;
				}
			}
			
			failpass("Reverse iteration test", passed);	


			for (int counter = -1; counter != -255; --counter)
			{
				s_list1.emplace_front(counter);
			}
			
			temp = s_list1.emplace_front(-255);
			
			failpass("Emplace_front return value test", temp.number == -255);
			

			test_counter = -255;
			
			for (plf::list<small_struct>::iterator it = s_list1.begin(); it != s_list1.end(); ++it)
			{
				if (test_counter++ != it->number)
				{
					passed = false;
					break;
				}
			}
			
			failpass("Emplace_front test", passed);	
			
			
			test_counter = 255;

			for (plf::list<small_struct>::reverse_iterator rit = s_list1.rbegin(); rit != s_list1.rend(); ++rit)
			{
				if (--test_counter != rit->number)
				{
					passed = false;
					break;
				}
			}
			
			failpass("Reverse iteration test 2", passed);	
			
			
			
			title2("Move tests");

			plf::list<small_struct> s_list2(std::move(s_list1));
			
			
			test_counter = 255;

			for (plf::list<small_struct>::reverse_iterator rit = s_list2.rbegin(); rit != s_list2.rend(); ++rit)
			{
				if (--test_counter != rit->number)
				{
					passed = false;
					break;
				}
			}
			
			failpass("Move constructor", passed && s_list1.empty());
			
			
			s_list1 = std::move(s_list2);
			
			test_counter = 255;

			for (plf::list<small_struct>::reverse_iterator rit = s_list1.rbegin(); rit != s_list1.rend(); ++rit)
			{
				if (--test_counter != rit->number)
				{
					passed = false;
					break;
				}
			}
			
			failpass("Move assignment", passed && s_list2.empty());

			
			title2("Copy tests");
			
			

			s_list2 = s_list1;
			
			
			test_counter = 255;

			for (plf::list<small_struct>::reverse_iterator rit = s_list2.rbegin(); rit != s_list2.rend(); ++rit)
			{
				if (--test_counter != rit->number)
				{
					passed = false;
					break;
				}
			}
			
			failpass("Copy assignment", passed);


			plf::list<small_struct> s_list3(s_list1);
			
			
			test_counter = 255;

			for (plf::list<small_struct>::reverse_iterator rit = s_list3.rbegin(); rit != s_list3.rend(); ++rit)
			{
				if (--test_counter != rit->number)
				{
					passed = false;
					break;
				}
			}
			
			failpass("Copy constructor", passed);
		}
		#endif


		{
			title2("Reorder tests");
			
			plf::list<int> list1;
			

			for (int counter = 0; counter != 255; ++counter)
			{
				list1.push_back(counter);
			}


			unsigned int original_total = 0;

			for (plf::list<int>::iterator it = list1.begin(); it != list1.end(); ++it)
			{
				original_total += *it;
			}

			plf::list<int>::iterator it1 = list1.begin(), it2 = list1.begin(), it3 = list1.begin();
			
			std::advance(it1, 25);
			std::advance(it2, 5);
			
			list1.reorder(it2, it1);
			
			it1 = list1.begin();
			std::advance(it1, 5);
			
			failpass("Single reorder", *it1 == 25);
			
			
			it1 = list1.begin();
			std::advance(it1, 152);
			
			list1.reorder(list1.begin(), it1);

			failpass("Single reorder to begin", *(list1.begin()) == 152);
			
			list1.reorder(list1.end(), it2);
			
			it1 = --(list1.end());
			
			failpass("Single reorder to end", *it1 == 5);
			
			it2 = it1 = list1.begin();

			std::advance(it1, 50);
			std::advance(it2, 60);
			std::advance(it3, 70);
			
			list1.reorder(it3, it1, it2);
			
			bool pass = true;
			
			it3 = list1.begin();
			std::advance(it3, 60);
			
			for (int test = 50; test != 60; ++test)
			{
				if (*it3 != test)
				{
					pass = false;
				}
				++it3;
			}
			
			failpass("Range reorder", pass == true);
			

			it2 = it1 = list1.begin();
			
			std::advance(it1, 80);
			std::advance(it2, 120);


			list1.reorder(list1.end(), it1, it2);
			
			pass = true;
			
			it3 = list1.end();
			std::advance(it3, -41);
			
			for (int test = 80; test != 120; ++test)
			{
				if (*it3 != test)
				{
					pass = false;
				}
				++it3;
			}
			
			failpass("Range reorder to end", pass == true);



			it2 = it1 = list1.begin();
			
			std::advance(it1, 40);
			std::advance(it2, 45);

			list1.reorder(list1.begin(), it1, it2);
			
			pass = true;
			
			it3 = list1.begin();
			
			for (int test = 40; test != 45; ++test)
			{
				if (*it3 != test)
				{
					pass = false;
				}
				++it3;
			}
			
			failpass("Range reorder to begin", pass == true);
			
			unsigned int total = 0;
			for (it1 = list1.begin(); it1 != list1.end(); ++it1)
			{
				total += *it1;
			}
			
			failpass("Post-reordering data consistency", total == original_total);
		}
		
		{
			title1("List");
			title2("Test Basics");
			
			list<int *> p_list;

			failpass("List empty", p_list.empty());
			
			int ten = 10;
			p_list.push_front(&ten);
			
			failpass("List not-empty", !p_list.empty());

			title2("Iterator tests");
			
			failpass("Begin() working", **p_list.begin() == 10);
			failpass("End() working", p_list.begin() != p_list.end());
			

			p_list.clear();

			failpass("Begin = End after clear", p_list.begin() == p_list.end());

			int twenty = 20;
			
			for (unsigned int temp = 0; temp != 200; ++temp)
			{
				p_list.push_back(&ten);
				p_list.push_back(&twenty);
			}
			
			unsigned int total = 0, numtotal = 0;
			
			for(list<int *>::iterator the_iterator = p_list.begin(); the_iterator != p_list.end(); ++the_iterator)
			{
				++total;
				numtotal += **the_iterator;
			}
			
			failpass("Iteration count test", total == 400);
			failpass("Iterator access test", numtotal == 6000);

			list<int *>::iterator plus_twenty = p_list.begin();
			std::advance(plus_twenty, 20);
			list<int *>::iterator plus_two_hundred = p_list.begin();
			std::advance(plus_two_hundred, 200);
			
			failpass("Iterator + distance test", std::distance(p_list.begin(), plus_twenty) == 20);
			failpass("Iterator + distance test 2", std::distance(p_list.begin(), plus_two_hundred) == 200);
			
			#ifdef PLF_INITIALIZER_LIST_SUPPORT
				list<int *>::iterator next_iterator = std::next(p_list.begin(), 5);
				list<int *>::const_iterator prev_iterator = std::prev(p_list.cend(), 300);
			#else
				list<int *>::iterator next_iterator = p_list.begin();
				list<int *>::const_iterator prev_iterator = p_list.cend();
				std::advance(next_iterator, 5);
				std::advance(prev_iterator, -300);
			#endif
			
			failpass("Iterator next test", std::distance(p_list.begin(), next_iterator) == 5);
			failpass("Const iterator prev test", std::distance(prev_iterator, p_list.cend()) == 300);
			
			#if defined(__cplusplus) && __cplusplus >= 201402L
				list<int *>::iterator prev_iterator2 = std::prev(p_list.end(), 300);
				failpass("Iterator/Const iterator equality operator test", prev_iterator == prev_iterator2);
			#endif
			
			
			list<int *> p_list2;
			p_list2 = p_list;
			list<int *> p_list3(p_list);
			list<int *> p_list4(p_list2, p_list2.get_allocator());
			
			list<int *>::iterator it1 = p_list.begin();
			list<int *>::const_iterator cit(it1);
			
			failpass("Copy test", p_list2.size() == 400);
			failpass("Copy construct test", p_list3.size() == 400);
			failpass("Allocator-extended copy construct test", p_list4.size() == 400);
		

			failpass("Equality operator test", p_list == p_list2);
			failpass("Equality operator test 2", p_list2 == p_list3);
			
			p_list2.push_back(&ten);
			
			failpass("Inequality operator test", p_list2 != p_list3);

			numtotal = 0;
			total = 0;

			for (list<int *>::reverse_iterator the_iterator = p_list.rbegin(); the_iterator != p_list.rend(); ++the_iterator)
			{
				++total;
				numtotal += **the_iterator;
			}


			failpass("Reverse iteration count test", total == 400);
			failpass("Reverse iterator access test", numtotal == 6000);
			
			list<int *>::reverse_iterator r_iterator = p_list.rbegin();
			std::advance(r_iterator, 50);
			
			failpass("Reverse iterator advance and distance test", std::distance(p_list.rbegin(), r_iterator) == 50);

			#ifdef PLF_INITIALIZER_LIST_SUPPORT
				list<int *>::reverse_iterator r_iterator2 = std::next(r_iterator, 2);
			#else
				list<int *>::reverse_iterator r_iterator2 = r_iterator;
				std::advance(r_iterator2, 2);
			#endif

			failpass("Reverse iterator next and distance test", std::distance(p_list.rbegin(), r_iterator2) == 52);

			numtotal = 0;
			total = 0;

			for(list<int *>::iterator the_iterator = p_list.begin(); the_iterator != p_list.end(); std::advance(the_iterator, 2))
			{
				++total;
				numtotal += **the_iterator;
			}

			failpass("Multiple iteration test", total == 200);
			failpass("Multiple iteration access test", numtotal == 2000);

			numtotal = 0;
			total = 0;

			for(list<int *>::const_iterator the_iterator = p_list.cbegin(); the_iterator != p_list.cend(); ++the_iterator)
			{
				++total;
				numtotal += **the_iterator;
			}

			failpass("Const_iterator test", total == 400);
			failpass("Const_iterator access test", numtotal == 6000);


			numtotal = 0;
			total = 0;

			for(list<int *>::const_reverse_iterator the_iterator = --list<int *>::const_reverse_iterator(p_list.crend()); the_iterator != list<int *>::const_reverse_iterator(p_list.crbegin()); --the_iterator)
			{
				++total;
				numtotal += **the_iterator;
			}

			failpass("Const_reverse_iterator -- test", total == 399);
			failpass("Const_reverse_iterator -- access test", numtotal == 5980);

			total = 0;
			
			for(list<int *>::iterator the_iterator = ++list<int *>::iterator(p_list.begin()); the_iterator != p_list.end(); ++the_iterator)
			{
				++total;
				the_iterator = p_list.erase(the_iterator);
				
				if (the_iterator == p_list.end())
				{
					break;
				}
			}

			failpass("Partial erase iteration test", total == 200);
			failpass("Post-erase size test", p_list.size() == 200);
			
			const unsigned int temp_capacity = static_cast<unsigned int>(p_list.capacity());
			p_list.shrink_to_fit();
			failpass("Shrink_to_fit test", p_list.capacity() < temp_capacity);
			failpass("Shrink_to_fit test 2", p_list.capacity() == 200);
			
			total = 0;

			for(list<int *>::reverse_iterator the_iterator = p_list.rbegin(); the_iterator != p_list.rend();)
			{
				++the_iterator;
				list<int *>::iterator it = the_iterator.base(); // grabs the_iterator--, essentially
				p_list.erase(it);
				++total;
			}

			failpass("Full erase reverse iteration test", total == 200);
			failpass("Post-erase size test", p_list.size() == 0);

			for (unsigned int temp = 0; temp != 200; ++temp)
			{
				p_list.push_back(&ten);
				p_list.push_back(&twenty);
			}
			
			total = 0;

			for(list<int *>::iterator the_iterator = --list<int *>::iterator(p_list.end()); the_iterator != p_list.begin(); --the_iterator)
			{
				++total;
			}

			failpass("Negative iteration test", total == 399);


			total = 0;

			for(list<int *>::iterator the_iterator = --(list<int *>::iterator(p_list.end())); the_iterator != p_list.begin() && the_iterator != ++plf::list<int *>::iterator(p_list.begin()); std::advance(the_iterator, -2))
			{
				++total;
			}

			failpass("Negative multiple iteration test", total == 199);
			
			#ifdef PLF_MOVE_SEMANTICS_SUPPORT
				p_list2 = std::move(p_list);
				failpass("Move test", p_list2.size() == 400);

				list<int *> p_list5(p_list2);
				list<int *> p_list6(std::move(p_list5), p_list2.get_allocator());

				failpass("Allocator-extended move construct test", p_list6.size() == 400);
			#else
				p_list2 = p_list;
			#endif

			p_list3 = p_list2;

			failpass("Copy test 2", p_list3.size() == 400);

			p_list2.push_back(&ten);

			p_list2.swap(p_list3);

			failpass("Swap test", p_list2.size() == p_list3.size() - 1);

			swap(p_list2, p_list3);

			failpass("Swap test 2", p_list3.size() == p_list2.size() - 1);

			failpass("max_size() test", p_list2.max_size() > p_list2.size());

		}


		{
			title2("Insert and Erase tests");

			list<int> i_list;

			for (unsigned int temp = 0; temp != 500000; ++temp)
			{
				i_list.push_back(temp);
			}
			
			
			failpass("Size after insert test", i_list.size() == 500000);


			list<int>::iterator found_item = std::find(i_list.begin(), i_list.end(), 5000);;
			
			failpass("std::find iterator test", *found_item == 5000);
			
			
			list<int>::reverse_iterator found_item2 = std::find(i_list.rbegin(), i_list.rend(), 5000);;
			
			failpass("std::find reverse_iterator test", *found_item2 == 5000);
			
			
			for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end(); ++the_iterator)
			{
				the_iterator = i_list.erase(the_iterator);
			}

			failpass("Erase alternating test", i_list.size() == 250000);

			do
			{
				for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end();)
				{
					if ((xor_rand() & 7) == 0)
					{
						the_iterator = i_list.erase(the_iterator);
					}
					else
					{
						++the_iterator;
					}
				}
				
			} while (!i_list.empty());
			
			failpass("Erase randomly till-empty test", i_list.size() == 0);


			i_list.clear();
			
			for (unsigned int temp = 0; temp != 30000; ++temp)
			{
				i_list.push_back(1);
			}
			
			failpass("Size after reinitialize + insert test", i_list.size() == 30000);

			unsigned short count2 = 0;
			
			do
			{
				for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end();)
				{
					if ((xor_rand() & 7) == 0)
					{
						the_iterator = i_list.erase(the_iterator);
						++count2;
					}
					else
					{
						++the_iterator;
					}
				}
				
			} while (count2 < 15000);
			
			failpass("Erase randomly till half-empty test", i_list.size() == 30000u - count2);

			for (unsigned int temp = 0; temp != count2; ++temp)
			{
				i_list.push_front(1);
			}
			
			failpass("Size after reinsert test", i_list.size() == 30000);




			unsigned int sum = 0;

			for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end();)
			{
				if (++sum == 3)
				{
					sum = 0;
					the_iterator = i_list.erase(the_iterator);
				}
				else
				{
					i_list.insert(the_iterator, 1);
					++the_iterator;
				}
			}
			
			failpass("Alternating insert/erase test", i_list.size() == 40000);

			
			do
			{
				for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end();)
				{
					if ((xor_rand() & 3) == 0)
					{
						++the_iterator;
						i_list.push_front(1);
					}
					else
					{
						the_iterator = i_list.erase(the_iterator);
					}
				}
			} while (!i_list.empty());
			
			failpass("Random insert/erase till empty test", i_list.size() == 0);

			
			for (unsigned int temp = 0; temp != 500000; ++temp)
			{
				i_list.push_back(10);
			}

			failpass("Insert post-erase test", i_list.size() == 500000);
			list<int>::iterator it2 = i_list.begin();
			std::advance(it2, 250000);
			

			for (; it2 != i_list.end();)
			{
				it2 = i_list.erase(it2);
			}
			
			failpass("Large multi-increment iterator test", i_list.size() == 250000);

			
			for (unsigned int temp = 0; temp != 250000; ++temp)
			{
				i_list.push_back(10);
			}
			
			list<int>::iterator end_iterator = i_list.end();
			std::advance(end_iterator, -250000);
			
			for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != end_iterator;)
			{
				the_iterator = i_list.erase(the_iterator);
			}

			failpass("Large multi-decrement iterator test", i_list.size() == 250000);

			
			for (unsigned int temp = 0; temp != 250000; ++temp)
			{
				i_list.push_front(10);
			}
			
			
			unsigned int total = 0;
			
			for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end(); ++the_iterator)
			{
				total += *the_iterator;
			}

			failpass("Re-insert post-heavy-erasure test", total == 5000000);
			

			end_iterator = i_list.end();
			std::advance(end_iterator, -50001);
			list<int>::iterator begin_iterator = i_list.begin();
			std::advance(begin_iterator, 300000);

			for (list<int>::iterator the_iterator = begin_iterator; the_iterator != end_iterator;)
			{
				the_iterator = i_list.erase(the_iterator);
			}

			failpass("Non-end decrement + erase test", i_list.size() == 350001);
			

			for (unsigned int temp = 0; temp != 100000; ++temp)
			{
				i_list.push_back(10);
			}
			
			begin_iterator = i_list.begin();
			std::advance(begin_iterator, 300001);
			
			
			for (list<int>::iterator the_iterator = begin_iterator; the_iterator != i_list.end();)
			{
				the_iterator = i_list.erase(the_iterator);
			}
			
			failpass("Non-beginning increment + erase test", i_list.size() == 300001);

			list<int>::iterator temp_iterator = i_list.begin();
			std::advance(temp_iterator, 2); // Advance test 1

			i_list.erase(temp_iterator);
			temp_iterator = i_list.begin(); // Check edge-case with advance when erasures present in initial group
			std::advance(temp_iterator, 500);

			for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end();)
			{
				the_iterator = i_list.erase(the_iterator);
			}
			
			failpass("Total erase test", i_list.empty());

			
			i_list.clear();
			i_list.shrink_to_fit();

			const unsigned int temp_capacity2 = static_cast<unsigned int>(i_list.capacity());
			i_list.reserve(1000);
			failpass("List reserve test", temp_capacity2 != i_list.capacity());
			failpass("List reserve test2", i_list.capacity() == 1000);

			unsigned int count = 0;

			for (unsigned int loop1 = 0; loop1 != 50000; ++loop1)
			{
				for (unsigned int loop = 0; loop != 10; ++loop)
				{
					if ((xor_rand() & 7) == 0)
					{
						i_list.push_back(1);
						++count;
					}
				}

				for (list<int>::iterator the_iterator = i_list.begin(); the_iterator != i_list.end();)
				{
					if ((xor_rand() & 7) == 0)
					{
						the_iterator = i_list.erase(the_iterator);
						--count;
					}
					else
					{
						++the_iterator;
					}
				}
			}

			failpass("Multiple sequential small insert/erase commands test", count == i_list.size());
		}

		{
			title2("Range-erase tests");
		
			list<int> i_list;
			
			for (int counter = 0; counter != 1000; ++counter)
			{
				i_list.push_back(counter);
			}
			
			
			list<int>::iterator it1 = i_list.begin(), it2 = i_list.begin();
			
			std::advance(it1, 500);
			std::advance(it2, 800);
			
			i_list.erase(it1, it2);
			
			unsigned int counter = 0;

			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				++counter;
			}

			failpass("Simple range-erase test 1", counter == 700 && i_list.size() == 700);

		
			it1 = it2 = i_list.begin();
			
			std::advance(it1, 400);
			std::advance(it2, 500); // This should put it2 past the point of previous erasures
			
			i_list.erase(it1, it2);
			
			counter = 0;

			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				++counter;
			}

			failpass("Simple range-erase test 2", counter == 600 && i_list.size() == 600);

			

			it2 = it1 = i_list.begin();
			
			std::advance(it1, 4);
			std::advance(it2, 9); // This should put it2 past the point of previous erasures
			
			i_list.erase(it1, it2);

			counter = 0;

			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				++counter;
			}

			failpass("Simple range-erase test 3", counter == 595 && i_list.size() == 595);

			


			it2 = it1 = i_list.begin();
			
			std::advance(it2, 50); 
			
			i_list.erase(it1, it2);
			
			counter = 0;

			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				++counter;
			}

			failpass("Range-erase from begin() test 1", counter == 545 && i_list.size() == 545);




			it1 = i_list.begin();
			it2 = i_list.end();
			
			std::advance(it1, 345); // Test erasing and validity when it removes the final group in list
			i_list.erase(it1, it2);
			
			counter = 0;

			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				++counter;
			}

			failpass("Range-erase to end() test 1", counter == 345 && i_list.size() == 345);



			i_list.clear();

			for (counter = 0; counter != 3000; ++counter)
			{
				i_list.push_back(counter);
			}
			
			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				it = i_list.erase(it);
				
				if (it == i_list.end())
				{
					break;
				}
			}
			
			it2 = it1 = i_list.begin();

			std::advance(it1, 4);
			std::advance(it2, 600);
			i_list.erase(it1, it2);
			
			counter = 0;

			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				++counter;
			}

			failpass("Range-erase with list already half-erased, alternating erasures", counter == 904 && i_list.size() == 904);



			i_list.clear();

			for (counter = 0; counter != 3000; ++counter)
			{
				i_list.push_back(counter);
			}
			
			test_counter = 0;
			
			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				if ((xor_rand() & 1) == 0)
				{
					it = i_list.erase(it);
					++test_counter;
				}
			}
			
			failpass("Random erasures vs size check", test_counter == static_cast<int>(3000 - i_list.size()));
			
			if (i_list.size() < 500)
			{
				i_list.resize(800, 1);
			}

			it1 = i_list.begin();
			it2 = i_list.end();

			std::advance(it1, 400);
			i_list.erase(it1, it2);

			counter = 0;

			for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
			{
				++counter;
			}

			failpass("Range-erase with list already third-erased, randomizes erasures", counter == 400 && i_list.size() == 400);



			unsigned int size, range1, range2, internal_loop_counter;

			for (unsigned int loop_counter = 0; loop_counter != 50; ++loop_counter)
			{
				i_list.clear();

				for (counter = 0; counter != 1000; ++counter)
				{
					i_list.push_back(counter);
				}

				internal_loop_counter = 0;

				while (!i_list.empty())
				{
					it2 = it1 = i_list.begin();

					size = static_cast<unsigned int>(i_list.size());
					range1 = xor_rand() % size;
					range2 = range1 + 1 + (xor_rand() % (size - range1));
					std::advance(it1, range1);
					std::advance(it2, range2);

					i_list.erase(it1, it2);

					counter = 0;

					for (list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
					{
						++counter;
					}

					if (i_list.size() != counter)
					{
						std::cout << "Fail. loop counter: " << loop_counter << ", internal_loop_counter: " << internal_loop_counter << "." << std::endl;
						std::cin.get(); 
						abort(); 
					}
					
					if (i_list.size() > 2)
					{ // Test to make sure our stored erased_locations are valid
						i_list.push_back(1);
						i_list.push_back(10);
					}

					++internal_loop_counter;
				}
			}

			failpass("Fuzz-test range-erase randomly until empty", i_list.size() == 0);
		}


		{
			title2("Sort tests");
			
			list<int> i_list;
			
			i_list.reserve(50000);

			for (unsigned int temp = 0; temp != 50000; ++temp)
			{
				i_list.push_back(xor_rand() & 65535);
			}
			
			i_list.sort();
			
			bool sorted = true;
			int previous = 0;
			
			for (list<int>::iterator current = i_list.begin(); current != i_list.end(); ++current)
			{
				if (previous > *current)
				{
					sorted = false;
					break;
				}
				
				previous = *current;
			}

			failpass("Less-than sort test", sorted);

			i_list.sort(std::greater<int>());

			previous = 65536;
			
			for (list<int>::iterator current = i_list.begin(); current != i_list.end(); ++current)
			{
				if (previous < *current)
				{
					sorted = false;
					break;
				}

				previous = *current;
			}
			
			failpass("Greater-than sort test", sorted);
		}			



		{
			title2("Different insertion-style tests");

			#ifdef PLF_INITIALIZER_LIST_SUPPORT
				list<int> i_list = {1, 2, 3};

				failpass("Initializer-list constructor test", i_list.size() == 3);
			#else
				list<int> i_list(3, 1);
			#endif
			
			list<int> i_list2(i_list.begin(), i_list.end());
			
			failpass("Range-based constructor test", i_list2.size() == 3);
			
			list<int> i_list3(5000, 2);
			
			failpass("Fill construction test", i_list3.size() == 5000);
			
			i_list2.insert(i_list2.end(), 500000, 5);
			
			failpass("Fill insertion test", i_list2.size() == 500003);
			
			std::vector<int> some_ints(500, 2);
			
			i_list2.insert(i_list2.begin(), some_ints.begin(), some_ints.end());
			
			failpass("Fill insertion test", i_list2.size() == 500503);
		}


		#ifdef PLF_VARIADICS_SUPPORT
		{
			title2("Perfect Forwarding tests");

			list<perfect_forwarding_test> pf_list;

			int lvalue = 0;
			int &lvalueref = lvalue;

			pf_list.emplace(pf_list.end(), 7, lvalueref);

			failpass("Perfect forwarding test", (*pf_list.begin()).success);
			failpass("Perfect forwarding test 2", lvalueref == 1);
		}
		#endif
	}


	title1("All tests passed! Press Enter to Exit.");
	std::cin.get();

	return 0;
}
