#ifndef __LOG4CPP_LOGGER_H__
#define __LOG4CPP_LOGGER_H__

#include "logger_interface.h"

#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"

#include <stdio.h>
#include <stdarg.h>
#include <string>


#ifdef LOG_PRIORITY_CRITICAL
#undef LOG_PRIORITY_CRITICAL
#endif
#define LOG_PRIORITY_CRITICAL Log4cppLogger::CRITICAL

#ifdef LOG_PRIORITY_ERROR
#undef LOG_PRIORITY_ERROR
#endif
#define LOG_PRIORITY_ERROR    Log4cppLogger::ERR

#ifdef LOG_PRIORITY_WARNING
#undef LOG_PRIORITY_WARNING
#endif
#define LOG_PRIORITY_WARNING  Log4cppLogger::WARNING

#ifdef LOG_PRIORITY_INFO
#undef LOG_PRIORITY_INFO
#endif
#define LOG_PRIORITY_INFO     Log4cppLogger::INFO

#ifdef LOG_PRIORITY_DEBUG
#undef LOG_PRIORITY_DEBUG
#endif
#define LOG_PRIORITY_DEBUG    Log4cppLogger::DEBUG

#ifdef LOG_CONFIGURE
#undef LOG_CONFIGURE
#endif
#define LOG_CONFIGURE Log4cppLogger::Instance().Configure

#ifdef LOG_MESSAGE
#undef LOG_MESSAGE
#endif
#define LOG_MESSAGE Log4cppLogger::Instance().Print


/**
 * @brief log4cpp wrapper class.
 */
class Log4cppLogger : public LoggerInterface
{
// Type definition and constant.
public:
    enum PriorityLevel
    {
        CRITICAL = 0,
        ERR		 = 1,
        WARNING  = 2,
        INFO     = 3,
        DEBUG    = 4,
    };

// Construction.
private:
    /// Constructor.
    Log4cppLogger(){ }

    /// Destructor.
    virtual ~Log4cppLogger(){ }

// Overload operator.
private:
    /// Disable copy constructor.
    Log4cppLogger( const Log4cppLogger& object );

    /// Disable assignment operator.
    Log4cppLogger& operator =( const Log4cppLogger& object );

// Method.
public:
    /// Instantiation Log4cppLogger object.
    static Log4cppLogger& Instance()
    {
        static Log4cppLogger logger;
        return logger;
    }

// Override.
public:
    /// Load configure.
    virtual void Configure( const std::string& configFile ) throw( ConfigureException )
    {
        try
        { 
            log4cxx::PropertyConfigurator::configure(configFile);
        } 
        catch( ConfigureException& reason )
        {
            throw ConfigureException( reason.what()  );
        }
    }

    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const char* format, ... ) throw()
    {
        log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(categoryName);
        if (NULL == logger) 
        {
            return;
        }
        memset(_PrintrBuff,0,sizeof(_PrintrBuff));

        va_list args;
        va_start( args, format );
        vsprintf( _PrintrBuff,format, args );
        //log4cpp::Category::getInstance( categoryName ).logva( priority, format, args );
        va_end( args );
        
		try
		{
			switch(priority)
			{
			case CRITICAL:
				LOG4CXX_FATAL(logger,_PrintrBuff);
				break;
			case ERR:
				LOG4CXX_ERROR(logger,_PrintrBuff);
				break;
			case WARNING:
				LOG4CXX_WARN(logger,_PrintrBuff);
				break;
			case INFO:
				LOG4CXX_INFO(logger,_PrintrBuff);
				break;
			case DEBUG:
				LOG4CXX_DEBUG(logger,_PrintrBuff);
				break;
			default:
				LOG4CXX_INFO(logger,_PrintrBuff);
				break;
			};
		}catch(...)
		{
			return;
		}
        
    };

    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const std::string& message ) throw()
    {
        log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(categoryName);
        if (NULL == logger) 
        {
            return;
        }

        //log4cpp::Category::getInstance( categoryName ).log( priority, message );
		try
		{
			switch(priority)
			{
			case CRITICAL:
				LOG4CXX_FATAL(logger,_PrintrBuff);
				break;
			case ERR:
				LOG4CXX_ERROR(logger,_PrintrBuff);
				break;
			case WARNING:
				LOG4CXX_WARN(logger,_PrintrBuff);
				break;
			case INFO:
				LOG4CXX_INFO(logger,_PrintrBuff);
				break;
			case DEBUG:
				LOG4CXX_DEBUG(logger,_PrintrBuff);
				break;
			default:
				LOG4CXX_INFO(logger,_PrintrBuff);
				break;
			};
		}catch(...)
		{
			return ;
		}
    };
private:
    char _PrintrBuff[4096];
};

#endif // __LOG4CPP_LOGGER_H__
