/*
 * main.cpp
 *
 *  Created on: 2022/10/01
 *      Author: jun
 */
#include <algorithm>
#include <string>
#include <iostream>

//Factory Methodは生成に関するデザインパターンの１つで、
//スーパークラスでオブジェクトを作成するためのインターフェースが決まっている。
//サブクラスでは作成されるオブジェクトの型を変更することができる。
//　
//Factory Methodパターンに従うと new演算子を使用した直接のオブジェクト作成を呼び出しを
//特別なファクトリーメソッドへの呼び出しで置き換える。
//ファクトリーメソッドから返されるオブジェクトはプロダクトと呼ばれる。


//プロダクト(Product)はクリエーターとそのサブクラスによって生成されるすべてのオブジェクトに
//共通なインターフェースを宣言する。
class Product {
public:
	virtual ~Product() {};
	virtual std::string Operation() const = 0;
};


//具象プロダクト (ConcreteProduct)はプロダクトのインターフェースの種々の異なる実装
class ConcreteProduct1 : public Product {
public:
	std::string Operation() const override {
		return "クラス ConcreteProduct1からのリターン";
	}
};

class ConcreteProduct2 : public Product {
public:
	std::string Operation() const override {
		return "クラス ConcreteProduct2からのリターン";
	}
};


//クリエーター (Creator)クラスは新しいプロダクトのオブジェクトを返すファクトリーメソッドを宣言する。
//このメソッドの戻り値の型がプロダクトのインターフェースと一致していることが要点。
//ファクトリーメソッドをabstructと宣言して全てのサブクラスに独自のメソッドの実装を強制することができる。
//基底クラスのファクトリーメソッドで何らかのデフォルトのプロダクト型を返すようにできる。
//その名前に関わらず、プロダクトの作成はクリエーターの主要任務ではない。
//通常、クリエータークラスはすでにプロダクトに関連するいくつかの中核となるビジネスロジックを持っている。
//ファクトリー・メソッドは、 このロジックを具象クラスから分離するのに役立つ。
//例えるなら、ソフトウェア開発会社にはプログラマーのための研修部門があるが、会社の目的は、ソフト開発であり、プログラマーを育成ではない。
class Creator {
public:
	virtual ~Creator() {};
	virtual Product* FactoryMethod() const = 0;

	std::string SomeOperation() const {
		Product* product = this->FactoryMethod();
		std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
		delete product;
		return result;
	}

};

//具象クリエーター　(Concrete Creator)は、異なる型のプロダクトを返すように、
//基底クラスのファクトリーメソッドを上書きする。
//ファクトリーメソッドは常に新しいインスタンスを作成する必要がない。
//キャッシュ、オブジェクトプール、その他の方法で既存のオブジェクトを返しても構わない。
class ConcreteCreator1 : public Creator
{
public:
	Product* FactoryMethod() const override {
		return new ConcreteProduct1();
	}
};

class ConcreteCreator2 : public Creator
{
public:
	Product* FactoryMethod() const override {
		return new ConcreteProduct2();
	}
};

int main()
{
	std::cout << "ConcreteCreator1 実行" << std::endl;
	Creator* creator1 = new ConcreteCreator1();
	std::string str1 = creator1->SomeOperation();
	
	std::cout << "ConcreteCreator2 実行" << std::endl;
	Creator* creator2 = new ConcreteCreator2();
	std::string str2 = creator2->SomeOperation();

	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;

	delete creator1;
	delete creator2;
	
	return 0;
}
