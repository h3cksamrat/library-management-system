#include "crow.h"
#include <iostream>

class App : public crow::SimpleApp
{
  static App *app;
  App() : crow::SimpleApp()
  {
    std::cout << __FUNCTION__ << " Created" << std::endl;
  }

public:
  static App *getInstance()
  {
    if (app == nullptr)
      app = new App;
    return app;
  }
};
