/**
 * Assignment for csc464/564

 *by

 * Jialin Li 002250729
 * Sun Jian 002244864
 **/

#include "main.hpp"

int main(int arg, char *argv_main[], char *envp[]) {
    const int iShPort{9000};
    const int iFiPort{9001};

    signal(SIGPIPE, SigPipeHandle);

    try {
        ServerSockets ServSockets = InitServer();

        PrintMessage(iShPort, iFiPort);

        StartServer(ServSockets, DoShellCallback, DoFileCallback);

    } catch (char const *msg) {
        Utils::buoy(msg);
    }

    // DoClient();

    return 0;
}

/**
 *
 * Main logics
 *
 **/
ServerSockets InitServer() {
    // throw "test";

    // init shell server.
    int iShServSocket{-1};
    int iFiServSocket{-1};

    iShServSocket = Utils::CreateSocketMaster(9000);
    iFiServSocket = Utils::CreateSocketMaster(9001);

    return {iShServSocket, iFiServSocket};
}

void StartServer(ServerSockets ServSockets,
                 std::function<void(const int)> ShellCallback,
                 std::function<void(const int)> FileCallback) {
    if (ServSockets.shell < 0 || ServSockets.file < 0) {
        Utils::buoy("Server unable to start.");
    }

    int iShClientSocket{-1};
    sockaddr_in ClientAddr;
    unsigned int ClientAddrLen = sizeof(ClientAddr);

    // loop accepting
    iShClientSocket = accept(ServSockets.shell, (sockaddr *)&ClientAddr,
                             (socklen_t *)&ClientAddrLen);
    if (iShClientSocket > 0) {
        Utils::buoy("Shell client incoming");
    } else {
        Utils::buoy("Failed to accept client");
    }

    ShellCallback(iShClientSocket);
    close(iShClientSocket);

    shutdown(iShClientSocket, 1);
}

void PrintMessage(const int iSh, const int iFi) {
    Utils::buoy("SHFD Shell and file server.");
    Utils::buoy("Shell Server is listening on port " + std::to_string(iSh));
    Utils::buoy("SHFD Shell and file server. " + std::to_string(iFi));
}

/**
 *
 * Callback functions
 *
 **/
void DoShellCallback(const int iServFD) {
    const int ALEN = 256;
    char req[ALEN];

    while ((lib::readline(iServFD, req, ALEN - 1)) != FLAG_NO_DATA) {
        const std::string sRequest(req);

        std::vector<char *> RequestTokenized = lib::Tokenize(sRequest);

        ShellClient NewClient;

        ShellResponse ShellRes{NewClient.RunShellCommand(RequestTokenized)};

        // send(iServFD, req, strlen(req), 0);
        send(iServFD, "\n", 1, 0);
    }
    Utils::buoy("Connection closed by client.");
    shutdown(iServFD, 1);
}

void DoFileCallback(const int iServFD) {}

/**
 *
 * Miscs
 *
 **/
void SigPipeHandle(int signum) { return; }