/*
 * main.cpp
 *
 *  Created on: 2023/06/26
 *      Author: jun
 */

#include <algorithm>
#include <string>
#include <iostream>

//AbstractFactory(抽象ファクトリー、抽象工場)は、生成に関するデザインパターンの一つで、
//関連したオブジェクトの集まりを具象クラスを指定することなく生成することを可能とする。
//　
//AbstructFactoryパターンでは、製品ファミリーを構成する個別製品ごとに明示的なインターフェースを宣言する


class AbstractProductA {
public:
	virtual ~AbstractProductA() {};
	virtual std::string UsefulFunctionA() const = 0;

};

class ConcreteProductA1 : public AbstractProductA {
public:
	std::string UsefulFunctionA() const override {
		return "The result of the product A1.";
	}
};

class ConcreteProductA2 : public AbstractProductA {
public:
	std::string UsefulFunctionA() const override {
		return "The result of the product A2.";
	}
};

class AbstractProductB {
public:
	virtual ~AbstractProductB() {};
	virtual std::string UsefulFunctionB() const = 0;

	virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;

};

class ConcreteProductB1 : public AbstractProductB {
public:
	std::string UsefulFunctionB() const override {
		return "The result of the product B1.";
	}

	std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override {
		const std::string result = collaborator.UsefulFunctionA();
		return "The result of the B1 collaborating with (" + result + " )";
	}

};

class ConcreteProductB2 : public AbstractProductB {
public:
	std::string UsefulFunctionB() const override {
		return "The result of the product B2.";
	}

	std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override {
		const std::string result = collaborator.UsefulFunctionA();
		return "The result of the B2 collaborating with ( " + result + " )";
	}
};

class AbstractFactory {
public:
	virtual AbstractProductA *createProductA() const = 0;
	virtual AbstractProductB *createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
	AbstractProductA *createProductA() const {
		return new ConcreteProductA1();
	}

	AbstractProductB *createProductB() const {
		return new ConcreteProductB1();
	}
};

class ConcreteFactory2 : public AbstractFactory {
public:
	AbstractProductA *createProductA() const {
		return new ConcreteProductA2();
	}
	AbstractProductB *createProductB() const {
		return new ConcreteProductB2();
	}
};


void ClientCode(const AbstractFactory &factory) {
	const AbstractProductA *product_a = factory.createProductA();
	const AbstractProductB *product_b = factory.createProductB();

	std::cout << product_b->UsefulFunctionB() << "\n";
	std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";

	delete product_a;
	delete product_b;
}



int main()
{
	std::cout << "OK" << "\n";
	std::cout << "Client: Testing client code with the first factory type:\n";
	ConcreteFactory1 cf1;

	ClientCode(cf1);


	return 0;
}
