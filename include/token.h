#ifndef _TERM_H_
#define _TERM_H_

class Token
{
public:
    Token( std::string _sValue = "0", bool _bIsOperator = 0, bool _bIsUnary = 0) :
    msValue( _sValue ), mbIsOperator( _bIsOperator ), mbIsUnary( _bIsUnary )
    {}

    std::string getValue( void ) const{
        return msValue;
    }

    bool isOperator( void ) const{
        return mbIsOperator;
    }

    bool isUnary( void ) const{
        return mbIsUnary;
    }

private:
    std::string msValue;
    bool mbIsOperator;
    bool mbIsUnary;
};

#endif
