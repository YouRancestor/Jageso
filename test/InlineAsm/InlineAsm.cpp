// TestAsm.cpp: 定义控制台应用程序的入口点。
//
#include <stdio.h>

class Node
{
public:
	Node(int n) :a(n) {}
	void print() { printf("%d\n",a); }
private:
	int a;
	//Node* p;
	friend Node operator+(Node a, Node b);
};

Node operator+(Node a, Node b)
{
	int n = a.a + b.a;
	Node ret(n);
	return ret;
}


Node AddNode(Node a, Node b, Node c, Node d, Node e, Node f, Node g, Node h)
{
	return a + b + c + d + e;
}

#if defined(_M_IX86) || defined(_X86_) || defined(i386) || defined(__i386) || defined(__i386__)
# define ARC_X86
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) || defined(_M_X64)
# define ARC_X86_64
#else
# error Instruction Set Architecture not surported
#endif


int main()
{
	Node a(1);
	Node b(2);
	Node c(1);
	Node d(2);
	Node e(1);
	Node x(0);
	Node y(9);
	Node z(8);

	Node f = a + b;

	Node return_val(233);
    f = AddNode(a, b, c, d, e, x, y, z);

#if defined(_MSC_VER) && defined(ARC_X86_64)
# error msvc doesn't support x64 inline assembly
#elif defined (_MSC_VER) && defined (ARC_X86)
	__asm
	{

		mov         eax, dword ptr[z]
		push        eax
		mov         ecx, dword ptr[y]
		push        ecx
		mov         edx, dword ptr[x]
		push        edx
		mov         eax, dword ptr[e]
		push        eax
		mov         ecx, dword ptr[d]
		push        ecx
		mov         edx, dword ptr[c]
		push        edx
		mov         eax, dword ptr[b]
		push        eax
		mov         ecx, dword ptr[a]
		push        ecx
		lea         edx, dword ptr[return_val]
		mov         eax, edx
		push        eax
		call        AddNode
		add         esp, 24h
    }
#elif defined (__GNUC__) && (defined (ARC_X86_64) /*|| defined (ARC_X86)*/)
# error not implemented
#else

#endif

	return_val.print();
    f.print();

	return 0;
}

