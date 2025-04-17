#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

class MainLoop {
public:
  MainLoop();
  ~MainLoop();

  virtual void initialize();
  virtual void iterationPrepare() {}
  virtual bool physicsProcess(double p_time);
  virtual void iterationEnd() {}
  virtual bool process(double p_time);
  virtual void finalize();

private:
  void processFrame();
};

#endif // MAIN_LOOP_H