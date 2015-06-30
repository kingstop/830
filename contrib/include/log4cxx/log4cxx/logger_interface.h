#ifndef __LOGGER_INTERFACE_H__
#define __LOGGER_INTERFACE_H__

#include <stdexcept>
#include <string>
#pragma warning(disable:4290)
/**
 * @brief Exception class for configuration.
 */
class ConfigureException : public std::runtime_error
{
public:
    /**
     * @brief Constructor.
     * @param reason String containing the description of the exception.
     */
   ConfigureException( const std::string& reason ) : std::runtime_error( reason ) {}
};


/**
 * @brief Logger abstract interface class.
 */
class LoggerInterface
{
// Construction.
public:
    /// Destructor.
    virtual ~LoggerInterface() {}

// Method.
public:
    /// Load configure.
    virtual void Configure( const std::string& configFile ) throw( ConfigureException ) = 0;
    
    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const char* format, ... ) throw() = 0;

    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const std::string& message ) throw() = 0;
};

#endif // __LOGGER_INTERFACE_H__
