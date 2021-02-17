# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack <T> values;
    stack <T> minVal;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

template <class T> 
bool StackExt<T>::empty() const
{
	if (values.empty()) {
	    return true;
	}
	return false;
}

template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    return *novo;
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    T *novo = new T();
    return *novo;
}

