#ifndef _MINOTAUR_IO_MESSAGE_H_
#define _MINOTAUR_IO_MESSAGE_H_
/**
 * @file io_message.h
 * @author Wolfhead
 */
#include <string>
#include <map>
#include "../message.h"

namespace minotaur {

class ProtocolMessage;

class IOMessage : public MessageBase {
 public:
  IOMessage() 
      : MessageBase(MessageType::kUnknownEvent), descriptor_id(0) {
  }

  IOMessage(uint8_t type_id_, uint64_t descriptor_id_, uint64_t payload_ = 0) 
      : MessageBase(type_id_), descriptor_id(descriptor_id_), payload(payload_) {
  }

  void Destroy() const;
  virtual void Dump(std::ostream& os) const;

  uint64_t descriptor_id;
  uint64_t payload;

  ProtocolMessage* GetProtocolMessage() const {
    if (type_id == MessageType::kIOMessageEvent && payload) {
      return (ProtocolMessage*)payload;
    }
    return NULL;
  }
};

class ProtocolMessage : public MessageBase {
 public:

  virtual void Dump(std::ostream& os) const;

  uint64_t descriptor_id;
  uint32_t sequence_id; 
};

class LineProtocolMessage : public ProtocolMessage {
 public:
  LineProtocolMessage(const std::string& body_)
      : body(body_) {
    type_id = MessageType::kLineProtocolMessage;
  }

  virtual void Dump(std::ostream& os) const;

  std::string body;
};

class HttpProtocolMessage : public ProtocolMessage {
 public:
  enum {
    kMethodDelete = 0,
    kMethodGet = 1,
    kMethodHead = 2,
    kMethodPost = 3,
    kMethodPut = 4,
    kHttpTypeRequest = 0,
    kHttpTypeResponse = 1,
    kHttpTypeBoth = 2,
  };

  virtual void Dump(std::ostream& os) const;

  unsigned short http_major;
  unsigned short http_minor;
  unsigned short status_code;
  unsigned short method;
  unsigned short http_type;
  bool keep_alive; 

  std::string url;
  std::map<std::string, std::string> header;
  std::string body;
};

std::ostream& operator << (std::ostream& os, const IOMessage& message);
std::ostream& operator << (std::ostream& os, const ProtocolMessage& message);
std::ostream& operator << (std::ostream& os, const LineProtocolMessage& message);
std::ostream& operator << (std::ostream& os, const HttpProtocolMessage& message);


} //namespace minotaur

#endif //_MINOTAUR_IO_MESSAGE_H_