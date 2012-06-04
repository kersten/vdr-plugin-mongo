#include <iostream>
#include "client/dbclient.h"

#include <vdr/epg.h>

class cMongoEpgHandler : public cEpgHandler {
public:
    cMongoEpgHandler();
    virtual bool SetDescription(cEvent *Event, const char *Description);
};

cMongoEpgHandler::cMongoEpgHandler() {
    mongo::DBClientConnection c;
    c.connect("localhost");
}

bool cMongoEpgHandler::SetDescription(cEvent *Event, const char *Description)
{
    Event->SetDescription(DescriptionFromDatabase(Event));
    return true;
}