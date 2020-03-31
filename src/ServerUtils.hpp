#pragma once

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

struct ServerSockets {
    int shell;
    int file;
};

struct Accepted {
    int accepted{-1};
    int newsocket{-1};
};

class ServerUtils {
   private:
    static ServerSockets SocketReference;

   public:
    static bool bRunningBackground;
    static bool bIsDebugging;
    static std::mutex ShellServerLock;

    /**
     * Store a reference to opened socket for signal handling
     *  */
    static void setSocketsRef(ServerSockets &ref);
    static std::array<int, 2> getSocketsRef();

    /**
     * Helper function, contains the common code for passivesocket and
     * controlsocket (which are identical except for the IP address they
     * bind to).
     */
    static int CreateSocket(const unsigned short port,
                            const unsigned long int ip_addr,
                            const int backlog = 32);
    /**
     * Create the master socket for the server to listen to.
     */
    static int CreateSocketMaster(const unsigned short port,
                                  const int queue = 32);
    /**
     * Create a master socket for local connection only
     */
    static int CreateSocketMasterLocalOnly(const unsigned short port,
                                           const int queue = 32);

    /**
     * Poll from the two sockets, accepting when one become avalible.
     * */
    static Accepted PollEither(int *fds, int count, sockaddr *addr,
                               socklen_t *addrlen, int TimeOut = -1);

    /**
     *  display or logging.
     * */
    static void buoy(std::string message);
    static void rowdy(std::string message);

    static std::string GetTID();
};
