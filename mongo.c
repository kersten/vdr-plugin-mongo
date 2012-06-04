/*
 * epgtableid0.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: epgtableid0.c 1.1 2012/03/10 15:10:43 kls Exp $
 */

#include <vdr/epg.h>
#include <vdr/plugin.h>

#include <iostream>
#include "client/dbclient.h"

static const char *VERSION        = "0.0.1";
static const char *DESCRIPTION    = "EPG handler for events with table id 0x00";

// --- cTable0Handler --------------------------------------------------------

class cMongoHandler : public cEpgHandler {
private:
  bool Ignore(cEvent *Event) { return Event->TableID() == 0x00; }
public:
  virtual bool SetEventID(cEvent *Event, tEventID EventID);
  virtual bool SetStartTime(cEvent *Event, time_t StartTime);
  virtual bool SetDuration(cEvent *Event, int Duration);
  virtual bool SetTitle(cEvent *Event, const char *Title);
  virtual bool SetShortText(cEvent *Event, const char *ShortText);
  virtual bool SetDescription(cEvent *Event, const char *Description);
  virtual bool SetContents(cEvent *Event, uchar *Contents);
  virtual bool SetParentalRating(cEvent *Event, int ParentalRating);
  virtual bool SetVps(cEvent *Event, time_t Vps);
  virtual bool FixEpgBugs(cEvent *Event);
  };

bool cMongoHandler::SetEventID(cEvent *Event, tEventID EventID)
{
  return Ignore(Event);
}

bool cMongoHandler::SetStartTime(cEvent *Event, time_t StartTime)
{
  return Ignore(Event);
}

bool cMongoHandler::SetDuration(cEvent *Event, int Duration)
{
  return Ignore(Event);
}

bool cMongoHandler::SetTitle(cEvent *Event, const char *Title)
{
  return Ignore(Event);
}

bool cMongoHandler::SetShortText(cEvent *Event, const char *ShortText)
{
  return Ignore(Event);
}

bool cMongoHandler::SetDescription(cEvent *Event, const char *Description)
{
  return Ignore(Event);
}

bool cMongoHandler::SetContents(cEvent *Event, uchar *Contents)
{
  return Ignore(Event);
}

bool cMongoHandler::SetParentalRating(cEvent *Event, int ParentalRating)
{
  return Ignore(Event);
}

bool cMongoHandler::SetVps(cEvent *Event, time_t Vps)
{
  return Ignore(Event);
}

bool cMongoHandler::FixEpgBugs(cEvent *Event)
{
  return Ignore(Event);
}

// --- cPluginEpgtableid0 ----------------------------------------------------

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
