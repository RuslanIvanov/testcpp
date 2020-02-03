template<typename T> complex; // объявление класса, чтобы можно было его использовать в операторе <<
// сам шаблонный оператор, тут всё ясно
template<typename T>
std::ostream& operator << (std::ostream& out, complex<T>& qqq) {
	...
}

template<typename T>
class complex {
	....
	// описание этого оператора в классе со словом friend нужно только для того, чтобы 
	// оператор ввода/вывода имел доступ к закрытым членам класса
	// << <T> (можно <<<T>) - явное указание типа для этого оператора
	// нужно чтобы компилятор понял какой именно оператор использовать
	friend std::ostream operator << <T> (ostream& out, complex<T>& qqq);
	....
};
