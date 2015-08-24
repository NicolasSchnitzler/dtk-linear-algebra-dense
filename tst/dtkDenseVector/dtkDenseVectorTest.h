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
    void testClear(void);
    void testGetValue(void);
    void testSetValue(void);
    void testResize(void);
    void testFill(void);
    void testAppend(void);
    void testAssign(void);
    void testAddAssign(void);
    void testSubAssign(void);
    void testAssignValue(void);
    void testScal(void);
    void testIterator(void);
    void testData(void);
    void testView(void);
    void testConstView(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

// 
// dtkDenseVectorTest.h ends here
