/*
 * epgtableid0.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: epgtableid0.c 1.1 2012/03/10 15:10:43 kls Exp $
 */

#include <iostream>
#include <client/dbclient.h>

#include <vdr/epg.h>
#include <vdr/plugin.h>

static const char *VERSION        = "0.0.1";
static const char *DESCRIPTION    = trNOOP("EPG handler for mongodb backend");

// --- cTable0Handler --------------------------------------------------------

class cMongoHandler : public cEpgHandler {
private:
    bool Ignore(cEvent *Event) { return Event->TableID() == 0x00; }
    mongo::DBClientConnection c;
public:
    cMongoHandler();
    virtual bool SetEventID(cEvent *Event, tEventID EventID);
    virtual bool SetStartTime(cEvent *Event, time_t StartTime);
    virtual bool SetDuration(cEvent *Event, int Duration);
    virtual bool SetTitle(cEvent *Event, const char *Title);
    virtual bool SetShortText(cEvent *Event, const char *ShortText);
    virtual bool SetDescription(cEvent *Event, const char *Description);
    virtual bool SetContents(cEvent *Event, uchar *Contents);
    virtual bool SetParentalRating(cEvent *Event, int ParentalRating);
    virtual bool SetVps(cEvent *Event, time_t Vps);
    virtual bool HandleEvent(cEvent *Event);
};

cMongoHandler::cMongoHandler()
{
    c.connect("localhost");

    mongo::BSONObjBuilder b;
    b.genOID();
    b.append("title", "Test");
    b.append("description", "RAVE");
    mongo::BSONObj p = b.obj();

    c.insert("tutorial.persons", p);

    dsyslog("Mongo: cMongoHandler::SetDescription connected");
}

bool cMongoHandler::SetEventID(cEvent *Event, tEventID EventID)
{
    return true;
}

bool cMongoHandler::SetStartTime(cEvent *Event, time_t StartTime)
{
    return true;
}

bool cMongoHandler::SetDuration(cEvent *Event, int Duration)
{
    return true;
}

bool cMongoHandler::SetTitle(cEvent *Event, const char *Title)
{
    dsyslog("Mongo: cMongoHandler::SetDescription  %s", Event->Title());
    return true;
}

bool cMongoHandler::SetShortText(cEvent *Event, const char *ShortText)
{
    return true;
}

bool cMongoHandler::SetDescription(cEvent *Event, const char *Description)
{
    return true;
}

bool cMongoHandler::SetContents(cEvent *Event, uchar *Contents)
{
    return true;
}

bool cMongoHandler::SetParentalRating(cEvent *Event, int ParentalRating)
{
    return true;
}

bool cMongoHandler::SetVps(cEvent *Event, time_t Vps)
{
    return true;
}

bool cMongoHandler::HandleEvent(cEvent *Event)
{
    dsyslog("Mongo: cMongoHandler::HandleEvent");
    return true;
}

class cPluginMongo : public cPlugin {
public:
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return DESCRIPTION; }
  virtual bool Initialize(void);
  };

bool cPluginMongo::Initialize(void)
{
  new cMongoHandler;
  return true;
}

VDRPLUGINCREATOR(cPluginMongo); // Don't touch this!