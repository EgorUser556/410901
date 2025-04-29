#include <iostream>
#include <string>
#include<stack>

using namespace std;
stack <char> Stack;

void check(char let, string& answ);

void task_two(string& answ, string enterData) {
	for (int i = 0; i < enterData.length(); i++) {

		//Если число, то сразу записываем
		if (isdigit(enterData[i])) {
			answ += enterData[i];
		}
		else {
			check(enterData[i], answ);
		}
	}

	//добавляем в ответ оставшиеся элементы
	while (!Stack.empty()) {
		answ += Stack.top();
		Stack.pop();
	}
}

int task_one(string& str_in) {
	stack<int> val_stack;  // Стек для хранения операндов
	int n1, n2, res;

	for (int i = 0; i < str_in.length(); ++i) {
		char c = str_in[i];

		if (isdigit(c)) {
			val_stack.push(c - '0');  // Преобразуем символ в число и помещаем в стек
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			n2 = val_stack.top(); val_stack.pop();
			n1 = val_stack.top(); val_stack.pop();

			switch (c) {
			case '+': res = n1 + n2; break;
			case '-': res = n1 - n2; break;
			case '*': res = n1 * n2; break;
			case '/':
				res = n1 / n2;
				break;
			}
			val_stack.push(res);  // Добавляем результат в стек после вычисления
		}
	}
	return val_stack.top();
}


//проверка приоритета
int priority(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

void check(char let, string& answ) {
	//just push
	if (let == '(') {
		Stack.push(let);
	}

	//пока не встретим ) добавляем элементы в ответ
	else if (let == ')') {

		while (!Stack.empty() && Stack.top() != '(') {
			answ += Stack.top();
			Stack.pop();
		}
		Stack.pop();
	}

	//сравнение приоритета
	else {

		while (!Stack.empty() && priority(let) <= priority(Stack.top())) {
			answ += Stack.top();
			Stack.pop();
		}
		Stack.push(let);
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	string answ = "";
	string enterData;
	int userChoise;

	cout << "Введите выражение для преобразования: \n";
	getline(cin, enterData);
	
	cout << "Выберите: " << endl << "1) Посчитать ОПЗ" << endl << "2) Преобразовать в ОПЗ" << endl;
	cin >> userChoise;

	while (userChoise != 1 && userChoise != 2) {
		cout << endl << "Ошибка\n";
		cin >> userChoise;
	}
	if (userChoise == 1) {
		cout << task_one(enterData);
	}
	else {
		task_two(answ, enterData);
		cout << answ << endl;
	}
	return 0;
}
