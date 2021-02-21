#pragma once
#include <iostream>
using namespace std;

/*Template class for holding an generic arrays - implempanting iterators (normal, const, reverse)*/



namespace elc
{
	template <class T>
	class DynamicArray
	{
	private:
		void resize() {
			_physicalSize *= 2;
			T* temp= nullptr;

			try
			{
				temp = new T[_physicalSize];

			}
			catch (bad_alloc& ex)
			{
				cout << ex.what() << endl;
			}

			for (int i = 0; i < _logicalSize; i++)
				temp[i] = _arr[i];

			delete[] _arr;
			_arr = temp;
		}

		T* _arr;
		int _logicalSize;
		int _physicalSize;

	public:

		DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size)
		{
	
			try 
			{
				_arr = new T[size]; 
			}
			catch (bad_alloc& ex)
			{
				cout << "Error with allocating new " << typeid(T).name() << " Array" << ex.what() << endl;
				return;
			}
	
			
		}

		DynamicArray(const DynamicArray& other) : _arr(nullptr) {
			*this = other;
		}
		~DynamicArray()
		{
			delete[] _arr;
		}


		const DynamicArray& operator=(const DynamicArray& other) {
			if (this != &other) {
				_logicalSize = other._logicalSize;
				_physicalSize = other._physicalSize;
				delete[] _arr;
				try
				{
					_arr = new T[_physicalSize];

				}
				catch (bad_alloc& ex)
				{
					cout << ex.what() << endl;
				}
				
				for (int i = 0; i < _logicalSize; i++)
					_arr[i] = other._arr[i];
			}
			return *this;
		}

		const T& operator[](int i) const { return _arr[i]; }
		
		T& operator[](int i) { return _arr[i]; }



		void push_back(const T& value) {
			if (_logicalSize == _physicalSize)
				resize();
			_arr[_logicalSize++] = value;
		}


		const T& front()    const { return _arr[0]; }
		int      size()     const { return _logicalSize; }
		int      capacity() const { return _physicalSize; }
		bool     empty()    const { return _logicalSize == 0; }
		void     clear() { _logicalSize = 0; }


		void set_logic_size(int size) { _logicalSize = size; }


		class iterator
		{
		private:
			DynamicArray* _da;
			int			  _i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
			iterator(const iterator& other) : _da(other._da), _i(other._i) {}

			friend class const_iterator;
			friend class rev_iterator;

			const iterator& operator=(const iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const iterator& other) const {
				return !(*this == other);
			}

			// smart-pointer iterator methods
			T& operator*() {
				return _da->_arr[_i];
			}

			T* operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			iterator& operator++() {
				++_i;
				return *this;
			}
			iterator operator++(int) {
				iterator temp(*this);
				++_i;
				return temp;
			}
			iterator& operator--() {
				--_i;
				return *this;
			}
			iterator operator--(int) {
				iterator temp(*this);
				--_i;
				return temp;
			}
			iterator operator+(int val) {
				_i += val;
				return *this;
			}
			iterator operator-(int val) {
				_i -= val;
				return *this;
			}

		};

		class const_iterator
		{
		private:
			const DynamicArray* _da;
			int			  _i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			friend class rev_iterator;

			const_iterator(const DynamicArray& arr, int i) : _da(&arr), _i(i) {}
			const_iterator(const const_iterator& other) : _da(other._da), _i(other._i) {}
			const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}


			const const_iterator& operator=(const const_iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			const const_iterator& operator=(const iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const const_iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const const_iterator& other) const {
				return !(*this == other);
			}

			// smart-pointer iterator methods
			const T& operator*() {
				return _da->_arr[_i];
			}
			const T* operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			const_iterator& operator++() {
				++_i;
				return *this;
			}
			const_iterator operator++(int) {
				iterator temp(*this);
				++_i;
				return temp;
			}
			const_iterator& operator--() {
				--_i;
				return *this;
			}
			const_iterator operator--(int) {
				iterator temp(*this);
				--_i;
				return temp;
			}
			const_iterator operator+(int val) {
				_i += val;
				return *this;
			}
			const_iterator operator-(int val) {
				_i -= val;
				return *this;
			}

		};

		class rev_iterator
		{

		private:
			DynamicArray* _da;
			int			  _i;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			rev_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
			rev_iterator(const rev_iterator& other) : _da(other._da), _i(other._i) {}
			rev_iterator(const iterator& other) : _da(other._da), _i(other._i) {}
			rev_iterator(const const_iterator& other) : _da(other._da), _i(other._i) {}


			const rev_iterator& operator=(const rev_iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			const rev_iterator& operator=(const const_iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			const rev_iterator& operator=(const iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const rev_iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const rev_iterator& other) const {
				return !(*this == other);
			}

			// smart-pointer iterator methods
			T& operator*() {
				return _da->_arr[_i];
			}
			T* operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			rev_iterator& operator++() {
				--_i;
				return *this;
			}
			rev_iterator operator++(int) {
				iterator temp(*this);
				--_i;
				return temp;
			}
			rev_iterator& operator--() {
				++_i;
				return *this;
			}
			rev_iterator operator--(int) {
				iterator temp(*this);
				++_i;
				return temp;
			}
			rev_iterator operator+(int val) {
				_i -= val;
				return *this;
			}
			rev_iterator operator-(int val) {
				_i += val;
				return *this;
			}

		};



		iterator begin() {
			return iterator(*this, 0);
		}
		iterator end() {
			return iterator(*this, _logicalSize);
		}
		const_iterator cbegin() const {
			return const_iterator(*this, 0);
		}
		const_iterator cend() const {
			return const_iterator(*this, _logicalSize);
		}


		rev_iterator rbegin() {
			return rev_iterator(*this, _logicalSize - 1);
		}
		rev_iterator rend() {
			return rev_iterator(*this, -1);
		}



		void insert(const iterator& pos, const T& val)
		{
			if (_logicalSize == _physicalSize)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}

			iterator p = pos;
			*p = val;
			++_logicalSize;
		}

		const iterator& erase(const iterator& pos)
		{
			iterator temp = pos; // To allow pos+1 in for loop
			if (pos == end()) {
				return end();
			}
			T* newElems = nullptr;
			int newsize = _logicalSize - 1;
			try
			{
				newElems = new T[newsize];

			}
			catch (bad_alloc& ex)
			{
				cout << ex.what() << endl;
			}
			int k = 0;
			for (iterator iter = begin(); iter != pos; iter++) {
				newElems[k] = _arr[*iter];
				k++;
			}

			for (iterator iter = temp + 1; iter != end(); iter++) {
				newElems[k] = _arr[*iter];
				k++;
			}
			delete[] _arr;
			_arr = newElems;
			_physicalSize = newsize;
			_logicalSize = newsize;
			return pos;
		}
		const iterator& erase(const iterator& first, const iterator& last)
		{
			if (first == end() && last == end())
			{
				return end();
			}

			T* newElems = nullptr;
			int newsize = _logicalSize - (last._i - first._i + 1);
			try
			{
				newElems = new T[newsize];

			}
			catch (bad_alloc& ex)
			{
				cout << ex.what() << endl;
			}
			for (iterator iter = begin(); iter != first; iter++) {
				newElems[*iter] = _arr[*iter];
			}
			for (iterator iter = last + 1; iter != end() - 1; iter++) {
				newElems[*iter] = _arr[*iter + 1];
			}
			delete[] _arr;
			_arr = newElems;
			_physicalSize = newsize;
			_logicalSize = newsize;
			return first;
		}



		void insert(const rev_iterator& pos, const T& val)
		{
			if (_logicalSize == _physicalSize)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}

			iterator p = pos;
			*p = val;
			++_logicalSize;
		}

		const  rev_iterator& erase(const  rev_iterator& pos)
		{
			rev_iterator temp = pos; // To allow pos+1 in for loop
			if (pos == end()) {
				return end();
			}
			T* newElems = nullptr;
			int newsize = _logicalSize - 1;
			try
			{
				newElems = new T[newsize];

			}
			catch (bad_alloc& ex)
			{
				cout << ex.what() << endl;
			}
			int k = 0;
			for (iterator iter = begin(); iter != pos; iter++) {
				newElems[k] = _arr[*iter];
				k++;
			}

			for (iterator iter = temp + 1; iter != end(); iter++) {
				newElems[k] = _arr[*iter];
				k++;
			}
			delete[] _arr;
			_arr = newElems;
			_physicalSize = newsize;
			_logicalSize = newsize;
			return pos;
		}



		const  rev_iterator& erase(const  rev_iterator& first, const  rev_iterator& last)
		{
			if (first == end() && last == end())
			{
				return end();
			}

			T* newElems = nullptr;
			int newsize = _logicalSize - (last._i - first._i + 1);
			try
			{
				newElems = new T[newsize];

			}
			catch (bad_alloc& ex)
			{
				cout << ex.what() << endl;
			}
			for (iterator iter = begin(); iter != first; iter++) {
				newElems[*iter] = _arr[*iter];
			}
			for (iterator iter = last + 1; iter != end() - 1; iter++) {
				newElems[*iter] = _arr[*iter + 1];
			}
			delete[] _arr;
			_arr = newElems;
			_physicalSize = newsize;
			_logicalSize = newsize;
			return first;
		}


		void print() const {
			for (int i = 0; i < _logicalSize; i++)
				cout << _arr[i] << " ";
			cout << endl;
		}

	};
}
