#include "calculatorengine.h"

#include <cassert>
#include <iostream>

void testSimpleAddition()
{
    CalculatorEngine engine;
    
    engine.appendNumber("2");
    engine.appendSign("+");
    engine.appendNumber("2");
    
    engine.evaluateExpression();
    
    assert(engine.getCurrentExpression() == "4");
    
    std::cout << "testSimpleAddition passed\n";
    
}

void testSimpleMultiplication()
{
    CalculatorEngine engine;
    
    engine.appendNumber("2");
    engine.appendSign("*");
    engine.appendNumber("4");
    
    engine.evaluateExpression();
    
    assert(engine.getCurrentExpression() == "8");
    
    std::cout << "testSimpleMultiplication passed\n";
    
}

void testSimpleDivision()
{
    CalculatorEngine engine;
    
    engine.appendNumber("3");
    engine.appendSign("/");
    engine.appendNumber("8");
    
    engine.evaluateExpression();
    
    assert(engine.getCurrentExpression() == "0.375");
    
    std::cout << "testSimpleDivision passed\n";
    
}

void testSimpleSubtraction()
{
    CalculatorEngine engine;
    
    engine.appendNumber("10");
    engine.appendSign("-");
    engine.appendNumber("20");
    
    engine.evaluateExpression();
    
    assert(engine.getCurrentExpression() == "-10");
    
    std::cout << "testSimpleSubtraction passed\n";
    
}

void testBrackets()
{
    CalculatorEngine engine;
    
    engine.appendNumber("10");
    engine.appendSign("-");
    engine.addBracket("(");
    engine.appendNumber("2");
    engine.appendSign("*");
    engine.appendNumber("3");
    engine.addBracket(")");
    
    engine.evaluateExpression();
    
    assert(engine.getCurrentExpression() == "4");
    
    std::cout << "testBrackets passed\n";
    
}

int main()
{
    testSimpleAddition();
    testSimpleMultiplication();
    testSimpleDivision();
    testSimpleSubtraction();
    testBrackets();
    
    std::cout << "All tests passed\n";
}




