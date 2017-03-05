



#include <iostream>


class DummyOldTarget
{
};

class DummyTarget
{
public:
    DummyTarget() : m_nCnt(0) {} ;
    ~DummyTarget();

    request();


private:
    int m_nCnt;

};


class DummyAdapter : public DummyTarget, public DummyOldTarget
{
public:
    DummyAdapter();
    ~DummyAdapter();






};


