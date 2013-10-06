#ifndef __vr_CodeLineException_h__
#define __vr_CodeLineException_h__


#include <string>
#include <stdexcept>
#include <sstream>

namespace vr {

/// This class is for sharing static members
class BaseCodeLineException
{
    protected:
        static bool sm_notify_on_exception;
        static bool sm_dump_on_exception;
    public:
        static void setNotifyOnException( bool value )
        { sm_notify_on_exception = value; };
        static void setDumpOnException( bool value )
        { sm_dump_on_exception = value; };
};

template <typename EXCEPTION>
class CodeLineException : public EXCEPTION, public BaseCodeLineException {
    protected:
        std::string m_file;
        int m_line;
    public:
        /// Constructor
        CodeLineException( EXCEPTION e, const std::string& file, int line )
            : EXCEPTION( e ), m_file( file ), m_line( line )
        {
            if ( sm_notify_on_exception ) {
                std::cerr << "Exception: " << what() << std::endl;
            }
            if ( sm_dump_on_exception ) {
                assert( false );
            }
        };
        
        virtual ~CodeLineException() throw() {};

        virtual const char *what() const throw()
        {
            std::ostringstream s;
            s << m_file << ":" << m_line << " " << EXCEPTION::what();
            return s.str().c_str();
        }
};

} // namespace vrutils

#define CODELINE_EXCEPTION(T,e)   vrutils::CodeLineException<T>( e, __FILE__, __LINE__ )
#define CODELINE_RTEXCEPTION(what)   vrutils::CodeLineException<std::runtime_error>( std::runtime_error( what ), __FILE__, __LINE__ )
#define EXCEPTION_IF_NULL( var )   if ( var == NULL ) throw vrutils::CodeLineException<std::runtime_error>( std::runtime_error( "NULL: " #var ), __FILE__, __LINE__ )
#define EXCEPTION_IF_TRUE( expr )   if ( expr ) throw vrutils::CodeLineException<std::runtime_error>( std::runtime_error( "TRUE: " #expr ) __FILE__, __LINE__ )
#define EXCEPTION_IF_FALSE( expr )   if ( !(expr) ) throw vrutils::CodeLineException<std::runtime_error>( std::runtime_error( "FALSE: " #expr ) __FILE__, __LINE__ )

#endif // __vr_CodeLineException_h__
