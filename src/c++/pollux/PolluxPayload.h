// SPDX-FileCopyrightText: 2023 Pollux authors <https://github.com/polluxio/pollux-payload/blob/main/AUTHORS>
// SPDX-License-Identifier: Apache-2.0

#ifndef __POLLUX_PAYLOAD_H_
#define __POLLUX_PAYLOAD_H_

#include <variant>

#include "ZebulonPayloadClient.h"

class PolluxPayload {
  public:
    PolluxPayload(const std::string& name): name_(name) {}
    PolluxPayload()=delete;
    PolluxPayload(const PolluxPayload&)=delete;

    enum UserOptionType { LONG, STRING };
    using UserOptionValue = std::variant<long, std::string>;
    using UserOptions = std::map<std::string, UserOptionValue>;

    std::string getName() const { return name_; }

    void setLocalID(int localID) { localID_ = localID; }
    int getLocalID() const { return localID_; }

    std::vector<int> getOtherIDs() const { return otherIDs_; }
    size_t getNumberOfPayloads() const { return otherIDs_.size()+1; }

    UserOptions getUserOptions() const { return userOptions_; }
    //returns nullptr if does not exist
    //if found: returns ptr to option
    UserOptionValue* getUserOptionValue(const std::string& name);

    bool isSynchronized() const { return control_.synchronized(); } 

    void setControl(const pollux::PolluxControl& control);

    //Following methods are accesible and can be overrided by final user
    virtual void init(ZebulonPayloadClient* client) {}
    virtual void loop(ZebulonPayloadClient* client) {}
    virtual void transmit(const pollux::PolluxMessage* message) {}

  private:
    std::string             name_         {};
    int                     localID_      {-1};
    std::vector<int>        otherIDs_     {};
    pollux::PolluxControl   control_      {};
    UserOptions             userOptions_  {};
};

#endif /* __POLLUX_PAYLOAD_H_ */
