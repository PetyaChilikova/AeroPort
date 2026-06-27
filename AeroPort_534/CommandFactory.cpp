#include "CommandFactory.h"
#include "LoginCmd.h"
#include "RegisterCmd.h"
#include "LogoutCmd.h"
#include "ViewProfileCmd.h"
#include "HelpCmd.h"
#include "BuildRunwayCmd.h"
#include "BuildHangarCmd.h"
#include "RegisterAirlineCmd.h"
#include "ScheduleFlightCmd.h"
#include "BookTicketCmd.h"
#include "ListAirspaceCmd.h"
#include "ListRunwaysCmd.h"
#include "AssignRunwayCmd.h"
#include "DelayFlightCmd.h"
#include "UndoCmd.h"
#include "FreeRunwayCmd.h"
#include "SendToHangarCmd.h"
#include "RetrieveFromHangarCmd.h"
#include "CloseRunwayCmd.h"
#include "ListFleetCmd.h"
#include "CancelFlightCmd.h"
#include "CloneAircraftCmd.h"

std::shared_ptr<Command> CommandFactory::createCommand(const std::string& name, std::stringstream& ss) {
    if (name == "login") return std::make_shared<LoginCmd>(ss);
    else if (name == "register") return std::make_shared<RegisterCmd>(ss);
    else if (name == "logout") return std::make_shared<LogoutCmd>(ss);
    else if (name == "view-profile") return std::make_shared<ViewProfileCmd>(ss);
    else if (name == "help") return std::make_shared<HelpCmd>(ss);
    else if (name == "build-runway") return std::make_shared<BuildRunwayCmd>(ss);
    else if (name == "build-hangar") return std::make_shared<BuildHangarCmd>(ss);
    else if (name == "register-airline") return std::make_shared<RegisterAirlineCmd>(ss);
    else if (name == "schedule-flight") return std::make_shared<ScheduleFlightCmd>(ss);
    else if (name == "book-ticket") return std::make_shared<BookTicketCmd>(ss);
    else if (name == "list-airspace") return std::make_shared<ListAirspaceCmd>(ss);
    else if (name == "list-runways") return std::make_shared<ListRunwaysCmd>(ss);
    else if (name == "assign-runway") return std::make_shared<AssignRunwayCmd>(ss);
    else if (name == "delay-flight") return std::make_shared<DelayFlightCmd>(ss);
    else if (name == "undo") return std::make_shared<UndoCmd>(ss);
    else if (name == "free-runway") return std::make_shared<FreeRunwayCmd>(ss);
    else if (name == "send-to-hangar") return std::make_shared<SendToHangarCmd>(ss);
    else if (name == "retrieve-from-hangar") return std::make_shared<RetrieveFromHangarCmd>(ss);
    else if (name == "close-runway") return std::make_shared<CloseRunwayCmd>(ss);
    else if (name == "list-fleet") return std::make_shared<ListFleetCmd>(ss);
    else if (name == "cancel-flight") return std::make_shared<CancelFlightCmd>(ss);
    else if (name == "clone-aircraft") return std::make_shared<CloneAircraftCmd>(ss);
  
    return nullptr;
}