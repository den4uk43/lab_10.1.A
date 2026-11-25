#include "pch.h"
#include "CppUnitTest.h"
#include "/ap_labs/lab_10.1 A/lab_10.1 A/lab_10.1.A.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStudent
{
	TEST_CLASS(UnitTestStudent)
	{
	public:

		// 1. Тест пошуку найбільшого середнього балу
		TEST_METHOD(TestFindMaxAverageGrade)
		{
			const int N = 3;
			Student students[N] = {
				{ "Іваненко", 2, KOMPYUTERNI_NAUKY, 4, 4, 4 },         // середній: 4.0
				{ "Петренко", 3, INFORMATYKA, 5, 5, 4 },               // середній: 4.666...
				{ "Сидоренко", 1, MATEMATYKA_TA_EKONOMIKA, 3, 4, 3 }   // середній: 3.333...
			};

			double maxAvg = FindMaxAverageGrade(students, N);

			// Для чисел типу double третім параметром передається похибка (tolerance)
			Assert::AreEqual(14.0 / 3.0, maxAvg, 0.001);
		}

		// 2. Тест обчислення відсотка студентів з "4" або "5" з фізики
		TEST_METHOD(TestCalcGoodPhysicsPercent)
		{
			const int N = 4;
			Student students[N] = {
				{ "Коваленко", 1, KOMPYUTERNI_NAUKY, 5, 3, 4 }, // підходить (5)
				{ "Бондаренко", 2, INFORMATYKA, 4, 5, 5 },      // підходить (4)
				{ "Ткаченко", 3, FIZYKA_TA_INFORMATYKA, 3, 4, 4 }, // не підходить (3)
				{ "Шевченко", 4, TRUDOVE_NAVCHANNYA, 2, 3, 3 }  // не підходить (2)
			};

			double percent = CalcGoodPhysicsPercent(students, N);

			// 2 з 4 студентів мають 4 або 5 з фізики -> це 50.0%
			Assert::AreEqual(50.0, percent, 0.001);
		}

		// 3. Тест обчислення середнього балу одного студента
		TEST_METHOD(TestCalcStudentAverage)
		{
			Student st = { "Мельник", 2, KOMPYUTERNI_NAUKY, 5, 4, 3 };
			double avg = CalcStudentAverage(st);

			Assert::AreEqual(4.0, avg, 0.001);
		}

		// 4. Тест отримання назви спеціальності
		TEST_METHOD(TestGetSpecialnistName)
		{
			string name = GetSpecialnistName(INFORMATYKA);
			Assert::AreEqual(string("Інформатика"), name);
		}
	};
}