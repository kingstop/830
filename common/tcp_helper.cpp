#include "tcp_helper.h"

struct conn_rec
{
    uv_tcp_t handle;
    uv_shutdown_t shutdown;
};
void fun_pop(conn_rec* p)
{

}
void fun_push(conn_rec* p)
{

}
conn_rec* fun_init()
{
    conn_rec* p = (conn_rec*)malloc(sizeof *p);
    return p;
}

uv_buf_t cb_alloc(uv_handle_t* handle, size_t len)
{
    return uv_buf_init((char*)malloc(len), len);
}

void cb_close(uv_handle_t* handle)
{
    conn_rec* conn = container_of(handle, conn_rec, handle);
    free(conn);
}

void cb_shutdown(uv_shutdown_t* req, int status)
{
    conn_rec* conn = container_of(req, conn_rec, shutdown);
    uv_close((uv_handle_t*)&conn->handle, cb_close);
}
void cb_read(uv_stream_t* stream, ssize_t nread, uv_buf_t buf)
{
    int r;
    if (nread >=0)
    { 
        if (nread > 0)
        {   printf("s:read data :%s %u", buf.base, buf.len);}
        return;
    }

    
    
    conn_rec* conn = container_of(stream, conn_rec, handle);
    r = uv_shutdown(&conn->shutdown, stream, cb_shutdown);
    CHECK_NET_STATE("s:cb_read", r);
    
}


void cb_connect(uv_connect_t* req, int status)
{
    if (status == 0)
    {
        printf("cl:connected \n");
        int r;
        r = uv_read_start((uv_stream_t*)(req->handle), cb_alloc, cb_read);
        CHECK_NET_STATE("cl:uv_read_start", r);
    }else
    {
       printf("cl:error code:%d\n", status);
    }
    
}

void cb_afterwrite(uv_write_t* req, int status)
{

}


void cb_connection(uv_stream_t* tcp, int status)
{
    assert(status == 0);
    conn_rec* conn = fun_init();
    int r;
    printf("s:add a new connection \n");
    r = uv_tcp_init(tcp->loop, (uv_tcp_t*)&conn->handle);
    CHECK_NET_STATE("s:uv_tcp_init", r);
    r = uv_accept(tcp,(uv_stream_t*)&conn->handle);
    CHECK_NET_STATE("s:uv_accept", r);
    r = uv_read_start((uv_stream_t*)&conn->handle, cb_alloc, cb_read);
    CHECK_NET_STATE("s:uv_read_start", r);   
}

void thread_run(void* p)
{
    TCPThreadBase* ower = static_cast<TCPThreadBase*>(p);
    if (ower)
    {   ower->run();}
}
void TCPThreadBase::begin()
{
    _tcp_thread = (uv_thread_t*)malloc(sizeof(uv_thread_t));
     uv_thread_create(_tcp_thread, thread_run, this);
}
void TCPThreadBase::stop()
{
    uv_thread_join(_tcp_thread);
    Sleep(10000);
}
void TCPThreadServer::send( char* buff, unsigned int len)
{

}

void TCPThreadServer::run()
{
    struct sockaddr_in addr = uv_ip4_addr(_net_info._ip, _net_info._port);
    _loop = uv_loop_new();
    uv_tcp_t* _tcp_obj = (uv_tcp_t*)malloc(sizeof*_tcp_obj);
ENTER_FUN   
    int r;
    r = uv_tcp_init(_loop, _tcp_obj);
    CHECK_NET_STATE("s:uv_tcp_init", r);
    r = uv_tcp_bind(_tcp_obj, addr);
    CHECK_NET_STATE("s:uv_tcp_bind", r);
    r = uv_listen((uv_stream_t*)_tcp_obj, _net_info._max_connect, cb_connection);
    CHECK_NET_STATE("s:uv_listen", r);
    r = uv_run(_loop, UV_RUN_DEFAULT);
    CHECK_NET_STATE("s:uv_run", r);
LEAVE_FUN
    uv_loop_delete(_loop);
    _loop = NULL;
    free(_tcp_obj);
    printf("s:out thread \n");
}