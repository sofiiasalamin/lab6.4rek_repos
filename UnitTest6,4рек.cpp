#include "pch.h"
#include "CppUnitTest.h"
#include "../6,4рек/6,4рек.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest6
{
    TEST_CLASS(UnitTest6)
    {
    public:

        
        TEST_METHOD(TestCreate_Double_RangeAndStep)
        {
            double a[50];
            Create(a, 50, -5, 5, 0);
            for (int i = 0; i < 50; i++)
            {
                Assert::IsTrue(a[i] >= -5 && a[i] <= 5);                        
                Assert::AreEqual((double)(int)(a[i] * 2), a[i] * 2, 1e-9);      
            }
        }

        
        TEST_METHOD(TestCreate_Int_Range)
        {
            int a[50];
            Create<int>(a, 50, -5, 5, 0);
            for (int i = 0; i < 50; i++)
                Assert::IsTrue(a[i] >= -5 && a[i] <= 5);
        }

        TEST_METHOD(TestMin_Int)
        {
            int a[] = { 3, -1, 2 };
            Assert::AreEqual(-1, Min<int>(a, 3, 1, a[0]));
        }
        TEST_METHOD(TestSumRange_Whole)
        {
            double a[] = { 1, 2.5, 3, 4 };
            Assert::AreEqual(10.5, SumRange(a, 0, 4), 1e-9);
        }
               
        TEST_METHOD(TestSumRange_Int)
        {
            int a[] = { 1, 2, 3, 4 };
            Assert::AreEqual(10, SumRange<int>(a, 0, 4));
            Assert::AreEqual(0, SumRange<int>(a, 2, 2));
        }
         
        TEST_METHOD(TestSumBetweenPositives_OnlyOne)
        {
            double a[] = { -1, 5, -1 };             
            int first = IFirstPositive(a, 3, 0);
            int last = ILastPositive(a, 2);
            Assert::AreEqual(first, last);
        }
    };
}