#ifndef __tcp_thread_h__
#define __tcp_thread_h__
#include "common_header.h"
#include "net_type.h"
enum
{
    _flag_run_thread = 0,
    _flag_stop_thread = 1,
};

struct conn_rec ;
typedef void (*pop_message)(conn_rec* p);
typedef void (*push_message)(conn_rec* p);
typedef conn_rec* (*init_conn)();

void fun_pop(conn_rec* p);
void fun_push(conn_rec* p);
conn_rec* fun_init();

struct TCPThreadBase
{
    TCPThreadBase(const net_info& info)
    {
        _loop = NULL;
        _tcp_thread = NULL;
        _net_info = info;
        _run_flag = _flag_run_thread;
    }

    void begin();
    void stop();

    uv_loop_t*      _loop;
    uv_thread_t*    _tcp_thread;
    net_info        _net_info;
    volatile int    _run_flag;
    
    virtual void run() = 0;
    virtual void send( char* buff, unsigned int len) = 0;
};

struct TCPThreadServer : public TCPThreadBase
{
    TCPThreadServer(const net_info& info) : TCPThreadBase(info)
    {

    }

    virtual void run();
    virtual void send(char* buff, unsigned int len);
};
struct TCPThreadClient: public TCPThreadBase
{
    TCPThreadClient(const net_info& info) : TCPThreadBase(info)
    {
        _conn = NULL;
    }
    virtual void run();
    virtual void send(char* buff, unsigned int len);
    session_runtime_data* _conn;
};



#endif