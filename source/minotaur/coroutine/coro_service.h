#ifndef _MINOTAUR_COROUTINE_SERVICE_H_
#define _MINOTAUR_COROUTINE_SERVICE_H_
/**
 * @file coro_service.h
 * @author Wolfhead
 */

#include "coro_actor.h"

namespace ade {

class Service;

class CoroService : public CoroActor {
 public:
  CoroService(Service* service) : service_(service) {}

 protected:
  virtual void Run(); 

 private:
  Service* service_;
};

} //namespace ade

#endif //_MINOTAUR_COROUTINE_SERVICE_H_
