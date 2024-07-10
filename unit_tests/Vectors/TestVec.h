#ifndef TestVec_h
#define TestVec_h

#include <iostream>
#include <string>

#include "TestCase.h"
#include "TestSuite.h"
#include "TestCaller.h"
#include "TestRunner.h"

#include "Vec.h"

class TestVec : public TestCase {
public:
    TestVec(std::string name);

    void testEmptyConstructor();
    void testSingleValueConstructor();
    void testThreeValueConstructor();
    void testAddition();
    void testSubtraction();
    void testMultiplication();
    void testScalarMultiplication();
    void testScalarDivision();
    void testNegation();
    void testAdditionAssignment();
    void testSubtractionAssignment();
    void testMultiplicationAssignment();
    void testScalarMultiplicationAssignment();
    void testScalarDivisionAssignment();
    void testInputStream();
    void testOutputStream();

    static Test* suite();
};
#endif