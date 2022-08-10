
#include "../include/EventLoop.h"
#include "../include/TcpServer.h"

#include "../include/Logger.h"

#include <memory>
#include <string>

class EchoServer
{
public:
    EchoServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const std::string &nameArg)
        : loop_(loop), server_(loop, listenAddr, nameArg)
    {
        server_.setConnectionCallback(std::bind(&EchoServer::onConnect, this, std::placeholders::_1));
        server_.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        //可以设置subloop数量
        // server_.setThreadNum(4);
    }

    void Start()
    {
        server_.start();
    }

    void onConnect(const TcpConnectionPtr &conn)
    {
        if (!conn->connected())
        {
            LOG_INFO("断开连接");
            conn->shutdown();
        }
    }

    void onMessage(const TcpConnectionPtr &conn,
                   Buffer *buf,
                   Timestamp ts)
    {
        std::string recv_str = buf->retrieveAllAsString();
        conn->send(recv_str);
    }

private:
    EventLoop *loop_;
    TcpServer server_;
};

int main()
{
    InetAddress addr(8989, "127.0.0.1");
    EventLoop loop;
    EchoServer echo_server(&loop, addr, "EchoServer");
    echo_server.Start();
    loop.loop();
}