#include "pch.h"
#include "order.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testiki
{
	TEST_CLASS(testiki)
	{
	public:

		//Перевірка правильних відсотків знижки для кожного рівня
		TEST_METHOD(TestDiscountRates)
		{
			DiscountCard card1 = { "C1", 100.0 }; 
			DiscountCard card2 = { "C2", 300.0 }; 
			DiscountCard card3 = { "C3", 600.0 };

			Assert::AreEqual(0.03, card1.getDiscountInfo().first);
			Assert::AreEqual(0.05, card2.getDiscountInfo().first);
			Assert::AreEqual(0.10, card3.getDiscountInfo().first);
		}

		//Перевірка відповідності назв статусів (рангів) картки
		TEST_METHOD(TestDiscountRanks)
		{
			DiscountCard card1 = { "C1", 100.0 };
			DiscountCard card2 = { "C2", 300.0 };
			DiscountCard card3 = { "C3", 600.0 };

			Assert::AreEqual(string("First-come"), card1.getDiscountInfo().second);
			Assert::AreEqual(string("not-a-begginer"), card2.getDiscountInfo().second);
			Assert::AreEqual(string("!vip!"), card3.getDiscountInfo().second);
		}

		//Перевірка додавання та безпечного видалення товарів
		TEST_METHOD(TestAddAndRemoveProduct)
		{
			OnlineOrder order;

			try {
				order.addProduct("Item", 10.0, 1);
				order.removeProduct("Item");
				order.removeProduct("NonExisting"); 
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Product operations caused an exception.");
			}
		}

		//Перевірка модифікації кількості та зміни статусів
		TEST_METHOD(TestQuantityAndStatusUpdate)
		{
			OnlineOrder order;

			try {
				order.addProduct("Item2", 20.0, 2);
				order.updateQuantity("Item2", 5);
				order.setStatus("Shipped");
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Quantity or status update caused an exception.");
			}
		}
	};
}
