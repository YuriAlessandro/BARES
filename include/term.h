#ifndef _TERM_H_
#define _TERM_H_

class Term
{
public:
    Term( std::string _sValue = "0", bool _bIsOperator = 0, bool _bIsUnary = 0) :
    msValue( _sValue ), mbIsOperator( _bIsOperator ), mbIsUnary( _bIsUnary )
    {}

    std::string getValue( void ){
        return msValue;
    }

    bool isOperator( void ){
        return mbIsOperator;
    }

private:
    std::string msValue;
    bool mbIsOperator;
    bool mbIsUnary;
};

#endif
