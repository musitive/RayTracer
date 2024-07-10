#include "TestVec.h"

TestVec::TestVec(std::string name) : TestCase(name) {}

void TestVec::testEmptyConstructor() {
    Vec3<int> v;
    assert(v.x == 0);
    assert(v.y == 0);
    assert(v.z == 0);
}

void TestVec::testSingleValueConstructor() {
    Vec3<int> v(1);
    assert(v.x == 1);
    assert(v.y == 1);
    assert(v.z == 1);
}

void TestVec::testThreeValueConstructor() {
    Vec3<int> v(1, 2, 3);
    assert(v.x == 1);
    assert(v.y == 2);
    assert(v.z == 3);
}

void TestVec::testAddition() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2(4, 5, 6);
    Vec3<int> v3 = v1 + v2;
    assert(v3.x == 5);
    assert(v3.y == 7);
    assert(v3.z == 9);
}

void TestVec::testSubtraction() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2(4, 5, 6);
    Vec3<int> v3 = v1 - v2;
    assert(v3.x == -3);
    assert(v3.y == -3);
    assert(v3.z == -3);
}

void TestVec::testMultiplication() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2(4, 5, 6);
    Vec3<int> v3 = v1 * v2;
    assert(v3.x == 4);
    assert(v3.y == 10);
    assert(v3.z == 18);
}

void TestVec::testScalarMultiplication() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2 = v1 * 2;
    assert(v2.x == 2);
    assert(v2.y == 4);
    assert(v2.z == 6);
}

void TestVec::testScalarDivision() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2 = v1 / 2;
    assert(v2.x == 0);
    assert(v2.y == 1);
    assert(v2.z == 1);
}

void TestVec::testNegation() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2 = -v1;
    assert(v2.x == -1);
    assert(v2.y == -2);
    assert(v2.z == -3);
}

void TestVec::testAdditionAssignment() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2(4, 5, 6);
    v1 += v2;
    assert(v1.x == 5);
    assert(v1.y == 7);
    assert(v1.z == 9);
}

void TestVec::testSubtractionAssignment() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2(4, 5, 6);
    v1 -= v2;
    assert(v1.x == -3);
    assert(v1.y == -3);
    assert(v1.z == -3);
}

void TestVec::testMultiplicationAssignment() {
    Vec3<int> v1(1, 2, 3);
    Vec3<int> v2(4, 5, 6);
    v1 *= v2;
    assert(v1.x == 4);
    assert(v1.y == 10);
    assert(v1.z == 18);
}

void TestVec::testScalarMultiplicationAssignment() {
    Vec3<int> v1(1, 2, 3);
    v1 *= 2;
    assert(v1.x == 2);
    assert(v1.y == 4);
    assert(v1.z == 6);
}

void TestVec::testScalarDivisionAssignment() {
    Vec3<int> v1(1, 2, 3);
    v1 /= 2;
    assert(v1.x == 0);
    assert(v1.y == 1);
    assert(v1.z == 1);
}

void TestVec::testInputStream() {
    Vec3<int> v;
    std::istringstream is("1 2 3");
    is >> v;
    assert(v.x == 1);
    assert(v.y == 2);
    assert(v.z == 3);
}

void TestVec::testOutputStream() {
    Vec3<int> v(1, 2, 3);
    std::ostringstream os;
    os << v;
    assert(os.str() == "1 2 3");
}