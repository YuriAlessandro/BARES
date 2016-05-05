#ifndef _TERM_H_
#define _TERM_H_

class Term 
{
public:
    Term( std::string _sValue = "0", bool _bIsOperand = 0 ) :
    msValue( _sValue ), mbIsOperand( _bIsOperand ){}
    
    std::string getValue( void ){
        return msValue;
    }
    
    bool isOperand( void ){
        return mbIsOperand;
    }

private:
    std::string msValue;
    bool mbIsOperand;
};

#endif