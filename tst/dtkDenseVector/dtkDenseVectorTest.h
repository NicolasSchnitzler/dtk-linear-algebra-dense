// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

#include <dtkTest>

class dtkDenseVectorTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreate(void);
    void testAssign(void);
    void testClearAndReset(void);
    void testResize(void);
    void testReserve(void);
    void testFill(void);
    void testIterator(void);
    // void testAddAssign(void);
    // void testSubAssign(void);
    // void testMulAssign(void);
    // void testScalAssign(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

// 
// dtkDenseVectorTest.h ends here
