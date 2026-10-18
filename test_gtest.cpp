#include <gtest/gtest.h>
#include "calculatorengine.h"

// here CalculatorEngine is a group name
TEST(CalculatorEngine, Addition)
{
    CalculatorEngine engine;
    engine.appendNumber("2");
    engine.appendSign("+");
    engine.appendNumber("2");
    
    engine.evaluateExpression();
    
    EXPECT_EQ(engine.getCurrentExpression(), QString("4"));
    
}

TEST(CalculatorEngine, Multiplication)
{
    CalculatorEngine engine;
    engine.appendNumber("2");
    engine.appendSign("*");
    engine.appendNumber("4");
    
    engine.evaluateExpression();
    
    EXPECT_EQ(engine.getCurrentExpression(), QString("8"));
    
}

TEST(CalculatorEngine, IsSignReturnsTrue)
{
    CalculatorEngine engine;
    
    EXPECT_TRUE(engine.isSign("+"));
}

TEST(CalculatorEngine, IsSignReturnsFalse)
{
    CalculatorEngine engine;

    EXPECT_FALSE(engine.isSign("7"));
}

class CalculatorEngineTest: public ::testing::Test
{
protected:
    CalculatorEngine engine;
    
    // this means that all test will start with "100 + "
    // this may look tedious here, but we say that every application needs
    // to start with connect, then load, then create something, we can avoid repetition
    /*
    void SetUp() override
    {
        engine.appendNumber("100");
        engine.appendSign("+");
    }
     */
};

TEST_F(CalculatorEngineTest, UndoNumber)
{
    engine.appendNumber("1");
    engine.appendNumber("2");
    engine.appendNumber("3");

    EXPECT_EQ(engine.getCurrentExpression(), QString("123"));

    engine.undo();

    EXPECT_EQ(engine.getCurrentExpression(), QString("12"));
}

TEST_F(CalculatorEngineTest, UndoAndAppend)
{
    engine.appendNumber("1");
    engine.appendNumber("2");
    engine.appendNumber("3");

    EXPECT_EQ(engine.getCurrentExpression(), QString("123"));

    engine.undo();

    EXPECT_EQ(engine.getCurrentExpression(), QString("12"));
    
    engine.appendNumber("4");
    EXPECT_EQ(engine.getCurrentExpression(), QString("124"));
}

TEST_F(CalculatorEngineTest, MultipleUndo)
{
    engine.appendNumber("1");
    engine.appendNumber("2");
    engine.appendNumber("3");

    engine.undo();
    EXPECT_EQ(engine.getCurrentExpression(), QString("12"));

    engine.undo();
    EXPECT_EQ(engine.getCurrentExpression(), QString("1"));

    engine.undo();
    EXPECT_EQ(engine.getCurrentExpression(), QString("0"));
}

TEST_F(CalculatorEngineTest, MultipleRedo)
{
    engine.appendNumber("1");
    engine.appendNumber("2");
    engine.appendNumber("3");

    engine.undo();
    engine.undo();

    EXPECT_EQ(engine.getCurrentExpression(), QString("1"));

    engine.redo();

    EXPECT_EQ(engine.getCurrentExpression(), QString("12"));

    engine.redo();

    EXPECT_EQ(engine.getCurrentExpression(), QString("123"));
}
