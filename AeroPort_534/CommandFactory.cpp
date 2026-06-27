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


std::shared_ptr<Command> CommandFactory::createCommand(const std::string& name, std::stringstream& ss) {
    if (name == "login") return std::make_shared<LoginCmd>(ss);
    if (name == "register") return std::make_shared<RegisterCmd>(ss);
    if (name == "logout") return std::make_shared<LogoutCmd>(ss);
    if (name == "view-profile") return std::make_shared<ViewProfileCmd>(ss);
    if (name == "help") return std::make_shared<HelpCmd>(ss);
    if (name == "build-runway") return std::make_shared<BuildRunwayCmd>(ss);
    if (name == "build-hangar") return std::make_shared<BuildHangarCmd>(ss);
    if (name == "register-airline") return std::make_shared<RegisterAirlineCmd>(ss);
    if (name == "schedule-flight") return std::make_shared<ScheduleFlightCmd>(ss);
    if (name == "book-ticket") return std::make_shared<BookTicketCmd>(ss);
    if (name == "list-airspace") return std::make_shared<ListAirspaceCmd>(ss);
    if (name == "list-runways") return std::make_shared<ListRunwaysCmd>(ss);
    if (name == "assign-runway") return std::make_shared<AssignRunwayCmd>(ss);
    if (name == "delay-flight") return std::make_shared<DelayFlightCmd>(ss);
    if (name == "undo") return std::make_shared<UndoCmd>(ss);
    

    return nullptr;
}