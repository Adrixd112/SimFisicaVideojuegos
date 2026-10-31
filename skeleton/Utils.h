#pragma once

//Si es un stack se punteros al heap, no hace delete de la memoria dinámica de estos al borrar
template <typename T, int SIZE>
class Stack {
	T array[SIZE];

	//indica la primera posicion vacía
	int tam;
public:
	Stack() {
		tam = 0;
	}
	~Stack() {
	}

	void push(const T& value) {
		if(tam<SIZE)
		{
			array[tam++] = value;
		}
	}

	void pop() {
		if(!empty()) tam--;
	}
	T top() {
		return array[tam];
	}

	bool empty() {
		return tam == 0;
	}

	void clear() {
		tam = 0;
	}
};