
#include "RemoteDebbuger.h"
#include "Meta/Any.h"
#include "LuaMachine/LogMessage.h"

NetNode* RemoteDebbuger::netNode = nullptr;

void CustomWork()
{
    Any message = LogMessage {"yo"};
    RemoteDebbuger::netNode->Send(message);
}

void MessageCallback(Any message)
{

}

void RemoteDebbuger::Start(int port)
{
    netNode = new NetNode();
    netNode->customWork = CustomWork;
    netNode->messageCallback = MessageCallback;
    netNode->Start(port);
}
